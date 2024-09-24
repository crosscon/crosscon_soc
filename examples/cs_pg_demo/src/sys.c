/*
 * Copyright (c) 2014-2024 Beyond Semiconductor
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the company may not be used to endorse or promote
 *    products derived from this software without specific prior written
 *    permission.
 *
 * THIS SOFTWARE IS PROVIDED BY BEYOND SEMICONDUCTOR ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL BEYOND SEMICONDUCTOR BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 * USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "csr_defs.h"
#include "uart.h"
#include "clint.h"

#include <stdio.h>
#include <stdlib.h>
#include <machine/syscall.h>
#include <errno.h>
#include <stdbool.h>

//-----------------------------------------------------------------------------
// Definitions of byd-ahb-soc demo constants
//-----------------------------------------------------------------------------

const unsigned int CPU_CLK = 25000000;            /* CPU clockrate: 25MHz */
const unsigned int MTIME_CLK = CPU_CLK;           /* mtimer ticks with same frequency as CPU clock */
const unsigned int UART_CLK_IN = CPU_CLK;         /* Input UART clock (on bydahbsoc same as CPU clockrate) */
const unsigned int UART_BAUD_RATE = 115200;       /* UART baudrate to select */

//-----------------------------------------------------------------------------

// declarations of main module interrupt handlers
void handle_external_interrupt();

//-----------------------------------------------------------------------------
// These two functions are landing location for unhandled exceptions and
// interrupts. If CPU lands here, something unexpected happened.
//-----------------------------------------------------------------------------

/**
 * Any synchronous exception not handled elsewhere ends up looping here.
 */
void unhandled_exception()
{
	volatile uint_xlen_t mepc  __attribute__((unused));
	mepc = csr_read_mepc();
	while (1);
}

/**
 * Any interrupt not handled elsewhere ends up looping here.
 */
void unhandled_interrupt()
{
	while (1);
}

//-----------------------------------------------------------------------------
// FPU needs to be initilized before instructions and registers can be used
//-----------------------------------------------------------------------------

/**
 * Puts FPU to initial state (via mstatus).
 */
void init_fpu()
{
	do {
		uint32_t f = VAL2REGFIELD(CSR_MSTATUS_F_FS_E_INITIAL, CSR_MSTATUS_F_FS);
		csr_clear_mstatus(CSR_MSTATUS_F_FS); // clear all bits of FPU state
		csr_set_mstatus(f); // set only bits specifying initial state
	} while (REGFIELD2VAL(csr_read_mstatus(), CSR_MSTATUS_F_FS) != CSR_MSTATUS_F_FS_E_INITIAL);
}

//-----------------------------------------------------------------------------
// CLINT timer support
//-----------------------------------------------------------------------------

/**
 * Reads and returns 64 bit value of CLINT mtime.
 * (Reading and composing both words takes a bit of work.)
 *
 * @return 64 bit value of timer
 */
uint64_t clint_get_time(void)
{
	uint32_t mtimehi;
	uint32_t mtime;

	do {
		// read high then low word of timer
		mtimehi = clint_read_mtimehi();
		mtime = clint_read_mtime();

		// repeat until we are certain there was not low word wrap-over while
		// registers were being read (detected by updated mtimehi value)
	} while (mtimehi != clint_read_mtimehi());

	return  (((uint64_t) mtimehi) << 32) | (uint64_t)mtime;
}

/**
 * Sets value of CLINT mtimecmp register pair.
 * (Avoiding triggering interrupts while doing this)
 *
 * @param clock 64 bit value of timecmp
 */
void clint_set_time_cmp(uint64_t clock)
{
	// set very high high word value to avoid causing random interrupts
	clint_write_mtimecmphi(0xffffffff);
	// set the low word
	clint_write_mtimecmp((uint32_t)(clock & UINT64_C(0xffffffff)));
	// set correct high word
	clint_write_mtimecmphi((uint32_t)(clock >> 32));
}

/**
 * Sets value of CLINT mtimecmp to current time + offset.
 *
 * @param clock_offset timecmp offset from current time
 */
void clint_offset_time_cmp(uint64_t clock_offset)
{
	// First of all set
	uint64_t clk = clint_get_time() + clock_offset;

	clint_set_time_cmp(clk);
}

//-----------------------------------------------------------------------------
// UART only implementation of read & write syscalls.
//-----------------------------------------------------------------------------

static bool uart_initialized = false;       /* flag for automatic UART initialization */

/**
 * Initializes UART.
 */
void UART_Init(void)
{
	int divisor;

	/* Reset receiver and transmitter, enable fifo... */
	uart_write_fcr(VAL2REGFIELD(1, UART_FCR_F_FIFO_ENABLE) |
	               VAL2REGFIELD(1, UART_FCR_F_RFR) |
	               VAL2REGFIELD(1, UART_FCR_F_TFR) |
	               VAL2REGFIELD(UART_FCR_F_RFTRIG_E_TL_7_8, UART_FCR_F_RFTRIG));

	/* Disable all interrupts */
	uart_write_ier(0x00);

	/* Calculate and set baud rate */
	divisor = UART_CLK_IN / (16 * UART_BAUD_RATE);
	uart_write_lcr(UART_LCR_F_DLAB);
	uart_write_dll(divisor & 0x000000ff);
	uart_write_dlm((divisor >> 8) & 0x000000ff);

	/* Set 8 bit char, 1 stop bit, no parity */
	uart_write_lcr(VAL2REGFIELD(UART_LCR_F_BITS_E_CHR8B, UART_LCR_F_BITS) |
	               VAL2REGFIELD(UART_LCR_F_STOP_E_STOP_1, UART_LCR_F_STOP) |
	               VAL2REGFIELD(UART_LCR_F_PARITY_E_NO_PARITY, UART_LCR_F_PARITY));

	uart_initialized = true;
}

/**
 * Waits for transmitter hold register to empty.
 * When it is empty, we can write more data.
 */
static void UART_WaitForTHRE(void)
{
	unsigned char lsr;
	do {
		lsr = uart_read_lsr();
	} while (REGFIELD2VAL(lsr, UART_LSR_F_THRE) == 0);
}

/**
 * Waits until "receiver data ready" is set.
 * (Which means we can read character.)
 */
static void UART_WaitForData()
{
	unsigned char lsr;
	do {
		lsr = uart_read_lsr();
	} while ((lsr & UART_LSR_F_DR) == 0);
}

/**
 * Puts single character to UART.
 * Waits until UART is ready to receive next character.
 *
 * @param c [in] character to send to UART
 */
static void UART_PutC(char c)
{
	if (!uart_initialized) UART_Init(); // make sure uart has been initialized

	UART_WaitForTHRE();
	uart_write_thr(c);
}

/**
 * Gets single character for UART.
 * (Waits until one is available)
 *
 * @return returns character received
 */
static char UART_GetC(void)
{
	if (!uart_initialized) UART_Init(); // make sure uart has been initialized

	UART_WaitForData();
	return uart_read_rbr();
}

/**
 * Sends len characters to UART.
 *
 * @param fd ignored, everything goes to UART
 * @param buf [in] pointer to data)
 * @param len [in] number of characters to write
 * @return number of characters written (always len)
 */
int UART_write(int fd, char *buf, int len)
{
	for (int i = 0; i < len; i++) {
		UART_PutC(*(buf + i));
		if (*(buf + i) == '\n') {
			UART_PutC('\r');
		}
	}
	return len;
}

/**
 * Reads up to buflen characters from uart.
 * Returns when enter CR or LF is received.
 *
 * @param fd ignored, UART is always input
 * @param buf [ptr in, data out] pointer to buffer to store data to
 * @param buflen [in] length of buffer in bytes
 * @return number of characters read
 */
int UART_read(int fd, char *buf, int buflen)
{
	int i;

	for (i = 0; i < buflen; i++) {
		*(buf + i) = UART_GetC();
		if ((*(buf + i) == '\n') || (*(buf + i) == '\r')) {
			i++;
			break;
		}
	}
	return i;
}

//-----------------------------------------------------------------------------
// heap (malloc...) support
//-----------------------------------------------------------------------------

extern char __heap_start; // external symbol defined in linker script
extern char __heap_end;   // and another one

static char* brk(char *newbrk)
{
	static char *heap_ptr = NULL;

	if (!heap_ptr) {
		heap_ptr = &__heap_start;
	}
	if (!newbrk) {
		newbrk = &__heap_start;
	}

	if ((intptr_t)newbrk >= (intptr_t)&__heap_start && (intptr_t)newbrk < (intptr_t)&__heap_end) {
		// valid heap extension within heap space
		return newbrk;
	} else {
		// outside heap space
		return ((char*)-ENOMEM);
	}
}

//-----------------------------------------------------------------------------
// syscall (ecall) handler
//-----------------------------------------------------------------------------

/**
 * Assembly part of exception handler for syscalls will keep a0-a6 registers
 * which are according to ABI transferred to arguments a0-a6.
 * Assembly part for ecall handler does not restore a0, as its modified
 * value must be kept to successfully return result.
 *
 * @param a0 [in] first syscall argument
 * @param a1 [in] second syscall argument
 * @param a2 [in] ...
 * @param a3
 * @param a4
 * @param a5
 * @param a6
 * @param syscall_id [in] syscall number
 * @return result
 */
uint_xlen_t __syscall_handler(uint_xlen_t a0, uint_xlen_t a1,
                              uint_xlen_t a2, uint_xlen_t a3,
                              uint_xlen_t a4, uint_xlen_t a5,
                              uint_xlen_t a6,
                              uint_xlen_t syscall_id)
{
	long result = 0;

	// By default, mret returns execution back to ecall instruction that
	// triggered this syscall. That would cause inifinite loop, so we
	// update mepc to return to instruction just after that one.
	csr_write_mepc(csr_read_mepc() + 4);

	switch (syscall_id) {
	case SYS_write:
		result = UART_write(a0, (char*)a1, a2);
		break;
	case SYS_read:
		result = UART_read(a0, (char*)a1, a2);
		break;
	case SYS_brk:
		result = (long)brk((char*)a0);
		break;
	default:
		result = -ENOSYS;
	}

	return result;
}

//-----------------------------------------------------------------------------
// trap handler (syscalls are handled by function above)
//-----------------------------------------------------------------------------

/**
 * Main C level trap handler. Non-vectored implementation.
 * Context is saved and restored in assembly part, so we don't use
 * attribute interrupt here.
 *
 * Assembly part is required to properly align trap handler even with
 * size optimization. It is also required by non-vectored implementation
 * to support input and output parameters required by syscalls.
 *
 * Syscalls can are not routed through here as assembly handler needs
 * different epilogue for them anyway.
 * They go directly to __syscall_handler in module sys.c.
 *
 * All other kinds of interrupts and exceptions are routed through here.
 */
void __trap_handler()
{
	uint_xlen_t mcause = csr_read_mcause();
	switch (mcause) {
		// -----------
		// TRAPS:
		// -----------
		case CSR_MCAUSE_F_CAUSE_E_ECM:   // environment call from M-mode
			unhandled_exception();       // we should never arrive here as ecalls are handled separately
			break;
		case CSR_MCAUSE_F_CAUSE_E_IAM:   // instruction address misaligned
		case CSR_MCAUSE_F_CAUSE_E_IAF:   // instruction access fault
		case CSR_MCAUSE_F_CAUSE_E_II:    // illegal instruction
		case CSR_MCAUSE_F_CAUSE_E_BKPT:  // breakpoint
		case CSR_MCAUSE_F_CAUSE_E_LAM:   // load address misaligned
		case CSR_MCAUSE_F_CAUSE_E_LAF:   // load access fault
		case CSR_MCAUSE_F_CAUSE_E_SAM:   // store/AMO address misaligned
		case CSR_MCAUSE_F_CAUSE_E_SAF:   // store/AMO access fault
		case CSR_MCAUSE_F_CAUSE_E_ECU:   // environment call from U-mode
		case CSR_MCAUSE_F_CAUSE_E_ECS:   // environment call from S-mode
		case CSR_MCAUSE_F_CAUSE_E_IPF:   // instruction page fault
		case CSR_MCAUSE_F_CAUSE_E_LPF:   // load page fault
		case CSR_MCAUSE_F_CAUSE_E_SPF:   // store/AMO page fault
			unhandled_exception();
			break;

		// -----------
		// INTERRUPTS:
		// -----------
		case CSR_MCAUSE_F_CAUSE_E_MTI:   // machine timer interrupt
		case CSR_MCAUSE_F_CAUSE_E_SSI:   // supervisor software interrupt
		case CSR_MCAUSE_F_CAUSE_E_MSI:   // machine software interrupt
		case CSR_MCAUSE_F_CAUSE_E_STI:   // supervisor timer interrupt
		case CSR_MCAUSE_F_CAUSE_E_SEI:   // supervisor external interrupt
		case CSR_MCAUSE_F_CAUSE_E_MEI:   // machine external interrupt
			handle_external_interrupt();
			break;

		default:
			while (1); // should not end up here (unexpected mcause?!)
			break;
	}
}

