/*******************************************************************
 * Register definitions for
 * ============================
 * BA5x_BydAHBSOC, version: 1.0
 *   peripheral
 * UART
 *   by 
 * Beyond Semiconductor
 * 
 * Created by sdtool 
 *   from sd/ba5x-byd-ahb-soc.sd.xml
 *   on 2022-11-21 15:17:43.987569
 *   using template src/templates/h/mmio.jinja
 *******************************************************************
 */

 #ifndef __regaccess_Beyond_Semiconductor_BA5x_BydAHBSOC_1_0_UART__
 #define __regaccess_Beyond_Semiconductor_BA5x_BydAHBSOC_1_0_UART__

#include "rvrac.h"
/*------------------------------------------------------------------
 * register RBR @ 0x11000000
 *   (read-only 8-bit memory mapped register)
 *   "Receiver buffer register.
This register contains the (oldest) byte received.
If FIFO is used, each new read will return the next byte.
This register is only accessible when LCR.DLAB=0."
 *------------------------------------------------------------------
 */
#define UART_RBR 0x11000000
#define UART_RBR_PTR (uint8_t *)(0x11000000)


#ifndef __ASSEMBLER__

inline uint8_t uart_read_rbr(void)
{
	return REG8(UART_RBR);
}
#endif

/*------------------------------------------------------------------
 * register THR @ 0x11000000
 *   (write-only 8-bit memory mapped register)
 *   "Transmitter holding register.
This register is only accessible when LCR.DLAB=0."
 *------------------------------------------------------------------
 */
#define UART_THR 0x11000000
#define UART_THR_PTR (uint8_t *)(0x11000000)


#ifndef __ASSEMBLER__

inline uint8_t uart_read_thr(void)
{
	return REG8(UART_THR);
}

inline void uart_write_thr(uint8_t value)
{
	REG8(UART_THR) = value;
}

inline uint8_t uart_rw_thr(uint8_t value)
{
	return rw_reg8(UART_THR_PTR, value);
}

inline uint8_t uart_set_thr(uint_csr32_t setmask)
{
	return set_reg8(UART_THR_PTR, setmask);
}

inline uint8_t uart_clear_thr(uint_csr32_t clrmask)
{
	return clear_reg8(UART_THR_PTR, clrmask);
}
#endif

/*------------------------------------------------------------------
 * register DLL @ 0x11000000
 *   (read-write 8-bit memory mapped register)
 *   "DLL (alias LSB-DL): divisor latch LSB. Defines bits [7:0] of divisor.
This register is accessible only when LCR.DLAB=1."
 *------------------------------------------------------------------
 */
#define UART_DLL 0x11000000
#define UART_DLL_PTR (uint8_t *)(0x11000000)


#ifndef __ASSEMBLER__

inline uint8_t uart_read_dll(void)
{
	return REG8(UART_DLL);
}

inline void uart_write_dll(uint8_t value)
{
	REG8(UART_DLL) = value;
}

inline uint8_t uart_rw_dll(uint8_t value)
{
	return rw_reg8(UART_DLL_PTR, value);
}

inline uint8_t uart_set_dll(uint_csr32_t setmask)
{
	return set_reg8(UART_DLL_PTR, setmask);
}

inline uint8_t uart_clear_dll(uint_csr32_t clrmask)
{
	return clear_reg8(UART_DLL_PTR, clrmask);
}
#endif

/*------------------------------------------------------------------
 * register IER @ 0x11000001
 *   (read-write 8-bit memory mapped register)
 *   "Interrupt enable register.
This register is only accessible when LCR.DLAB=0."
 *------------------------------------------------------------------
 */
#define UART_IER 0x11000001
#define UART_IER_PTR (uint8_t *)(0x11000001)

  /* Enable receiver data available interrupt.
It also enables timeout interrupts in FIFO mode */ 
  #define UART_IER_F_RDA_INT 0x00000001
  #define UART_IER_F_RDA_INT_OFFSET 0

  /* Enable transmitter holding register empty interrupt. */ 
  #define UART_IER_F_THRE_INT 0x00000002
  #define UART_IER_F_THRE_INT_OFFSET 1

  /* Enable receiver line status interrupt. */ 
  #define UART_IER_F_RLS_INT 0x00000004
  #define UART_IER_F_RLS_INT_OFFSET 2


#ifndef __ASSEMBLER__

inline uint8_t uart_read_ier(void)
{
	return REG8(UART_IER);
}

inline void uart_write_ier(uint8_t value)
{
	REG8(UART_IER) = value;
}

inline uint8_t uart_rw_ier(uint8_t value)
{
	return rw_reg8(UART_IER_PTR, value);
}

inline uint8_t uart_set_ier(uint_csr32_t setmask)
{
	return set_reg8(UART_IER_PTR, setmask);
}

inline uint8_t uart_clear_ier(uint_csr32_t clrmask)
{
	return clear_reg8(UART_IER_PTR, clrmask);
}
#endif

/*------------------------------------------------------------------
 * register DLM @ 0x11000001
 *   (read-write 8-bit memory mapped register)
 *   "DLM (alias MSB-DL): Divisor latch MSB. Defines bits [15:8] of divisor.
This register is accessible only when LCR.DLAB=1."
 *------------------------------------------------------------------
 */
#define UART_DLM 0x11000001
#define UART_DLM_PTR (uint8_t *)(0x11000001)


#ifndef __ASSEMBLER__

inline uint8_t uart_read_dlm(void)
{
	return REG8(UART_DLM);
}

inline void uart_write_dlm(uint8_t value)
{
	REG8(UART_DLM) = value;
}

inline uint8_t uart_rw_dlm(uint8_t value)
{
	return rw_reg8(UART_DLM_PTR, value);
}

inline uint8_t uart_set_dlm(uint_csr32_t setmask)
{
	return set_reg8(UART_DLM_PTR, setmask);
}

inline uint8_t uart_clear_dlm(uint_csr32_t clrmask)
{
	return clear_reg8(UART_DLM_PTR, clrmask);
}
#endif

/*------------------------------------------------------------------
 * register IIR @ 0x11000002
 *   (read-only 8-bit memory mapped register)
 *   "Interrupt identification register"
 *------------------------------------------------------------------
 */
#define UART_IIR 0x11000002
#define UART_IIR_PTR (uint8_t *)(0x11000002)

  /* Interrupt pending */ 
  #define UART_IIR_F_IP 0x00000001
  #define UART_IIR_F_IP_OFFSET 0

    // there are UART interrupts pending
    #define UART_IIR_F_IP_E_PENDING 0x0

    // no pending UART interrupts.
    #define UART_IIR_F_IP_E_NOT_PENDING 0x1

  /* pending interrupt identification */ 
  #define UART_IIR_F_PIID 0x0000000e
  #define UART_IIR_F_PIID_OFFSET 1

    // Modem status change interrupt pending
    #define UART_IIR_F_PIID_E_MSC_IP 0x0

    // Transmitter holding register empty interrupt pending.
    #define UART_IIR_F_PIID_E_THRE_IP 0x1

    // Receiver data ready interrupt pending.
    #define UART_IIR_F_PIID_E_RDR_IP 0x2

    // Line status change interrupt pending.
    #define UART_IIR_F_PIID_E_LSC_IP 0x3

    // Character timeout interrupt pending.
    #define UART_IIR_F_PIID_E_CHR_TIMEOUT_IP 0x6

  /* FIFOs enabled */ 
  #define UART_IIR_F_FE 0x000000c0
  #define UART_IIR_F_FE_OFFSET 6

    // FIFOs are disabled.
    #define UART_IIR_F_FE_E_DISABLED 0x0

    // FIFOs are enabled.
    #define UART_IIR_F_FE_E_ENABLED 0x3


#ifndef __ASSEMBLER__

inline uint8_t uart_read_iir(void)
{
	return REG8(UART_IIR);
}
#endif

/*------------------------------------------------------------------
 * register FCR @ 0x11000002
 *   (write-only 8-bit memory mapped register)
 *   "FIFO control register.
This register is used to enable/clear FIFO, set FIFO trigger level, etc.
This register is only accessible when LCR.DLAB=0."
 *------------------------------------------------------------------
 */
#define UART_FCR 0x11000002
#define UART_FCR_PTR (uint8_t *)(0x11000002)

  /* Enable transmitter and receiver FIFOs. */ 
  #define UART_FCR_F_FIFO_ENABLE 0x00000001
  #define UART_FCR_F_FIFO_ENABLE_OFFSET 0

  /* Receiver FIFO reset. Clears all bytes in receiver FIFO and resets FIFO level to 0.
Shift register is not cleared. This bit is self-clearing. */ 
  #define UART_FCR_F_RFR 0x00000002
  #define UART_FCR_F_RFR_OFFSET 1

  /* Transmitter FIFO reset. Clears all bytes in transmitter FIFO and resets FIFO level to 0.
Shift register is not cleared. This bit is self-clearing. */ 
  #define UART_FCR_F_TFR 0x00000004
  #define UART_FCR_F_TFR_OFFSET 2

  /* This field defines receiver FIFO interrupt trigger level.
To set up trigger level FIFO needs to be enabled in FCR before trigger level can be set.
(You can not enable FIFO and select trigger level with single write.) */ 
  #define UART_FCR_F_RFTRIG 0x000000c0
  #define UART_FCR_F_RFTRIG_OFFSET 6

    // Trigger when FIFO contains at least byte.
    #define UART_FCR_F_RFTRIG_E_TL1B 0x0

    // Trigger when FIFO is at least 1/4 full.
    #define UART_FCR_F_RFTRIG_E_TL_1_4 0x1

    // Trigger when FIFO is at least 1/2 full.
    #define UART_FCR_F_RFTRIG_E_TL_1_2 0x2

    // Trigger when FIFO is at least 7/8 full.
    #define UART_FCR_F_RFTRIG_E_TL_7_8 0x3


#ifndef __ASSEMBLER__

inline uint8_t uart_read_fcr(void)
{
	return REG8(UART_FCR);
}

inline void uart_write_fcr(uint8_t value)
{
	REG8(UART_FCR) = value;
}

inline uint8_t uart_rw_fcr(uint8_t value)
{
	return rw_reg8(UART_FCR_PTR, value);
}

inline uint8_t uart_set_fcr(uint_csr32_t setmask)
{
	return set_reg8(UART_FCR_PTR, setmask);
}

inline uint8_t uart_clear_fcr(uint_csr32_t clrmask)
{
	return clear_reg8(UART_FCR_PTR, clrmask);
}
#endif

/*------------------------------------------------------------------
 * register LCR @ 0x11000003
 *   (read-write 8-bit memory mapped register)
 *   "Line Control Register "
 *------------------------------------------------------------------
 */
#define UART_LCR 0x11000003
#define UART_LCR_PTR (uint8_t *)(0x11000003)

  /* This field specified number of bits in each transmitted or received character. */ 
  #define UART_LCR_F_BITS 0x00000003
  #define UART_LCR_F_BITS_OFFSET 0

    // characters are 5 bits long
    #define UART_LCR_F_BITS_E_CHR5B 0x0

    // characters are 6 bits long
    #define UART_LCR_F_BITS_E_CHR6B 0x1

    // characters are 7 bits long
    #define UART_LCR_F_BITS_E_CHR7B 0x2

    // characters are 8 bits long
    #define UART_LCR_F_BITS_E_CHR8B 0x3

  /* This filed specifies number of stop bits transmitter or received in each serial character. */ 
  #define UART_LCR_F_STOP 0x00000004
  #define UART_LCR_F_STOP_OFFSET 2

    // Single stop bit.
    #define UART_LCR_F_STOP_E_STOP_1 0x0

    // One and half stop bit when 5 bit characters are used. 2 stop bits otherwise.
    #define UART_LCR_F_STOP_E_STOP_MORE 0x1

  /* This field defines if parity bit is generated/checked and how this is done, if enabled.. */ 
  #define UART_LCR_F_PARITY 0x00000038
  #define UART_LCR_F_PARITY_OFFSET 3

    // Parity is disabled.
    #define UART_LCR_F_PARITY_E_NO_PARITY 0x0

    // Odd number of logic ones.
    #define UART_LCR_F_PARITY_E_ODD_PARITY 0x1

    // Even number of logic ones.
    #define UART_LCR_F_PARITY_E_EVEN_PARITY 0x3

    // High parity (stick). Parity bit is always 1.
    #define UART_LCR_F_PARITY_E_HIGH_PARITY 0x5

    // Low parity (stick). Parity bit is always 0.
    #define UART_LCR_F_PARITY_E_LOW_PARITY 0x7

  /* Break control bit. */ 
  #define UART_LCR_F_BREAK 0x00000040
  #define UART_LCR_F_BREAK_OFFSET 6

    // Break signal disabled.
    #define UART_LCR_F_BREAK_E_DISABLED 0x0

    // Break signal enabled.
    #define UART_LCR_F_BREAK_E_ENABLED 0x1

  /* Divisor latch access bit. */ 
  #define UART_LCR_F_DLAB 0x00000080
  #define UART_LCR_F_DLAB_OFFSET 7

    // Data control registers (RBR, THR and IER) are accessible. Divisor latches are shadowed.
    #define UART_LCR_F_DLAB_E_DATA 0x0

    // Divisor latches (DLL and DLM) are accessible. Data registers are shadowed.
    #define UART_LCR_F_DLAB_E_DIVISOR 0x1


#ifndef __ASSEMBLER__

inline uint8_t uart_read_lcr(void)
{
	return REG8(UART_LCR);
}

inline void uart_write_lcr(uint8_t value)
{
	REG8(UART_LCR) = value;
}

inline uint8_t uart_rw_lcr(uint8_t value)
{
	return rw_reg8(UART_LCR_PTR, value);
}

inline uint8_t uart_set_lcr(uint_csr32_t setmask)
{
	return set_reg8(UART_LCR_PTR, setmask);
}

inline uint8_t uart_clear_lcr(uint_csr32_t clrmask)
{
	return clear_reg8(UART_LCR_PTR, clrmask);
}
#endif

/*------------------------------------------------------------------
 * register MCR @ 0x11000004
 *   (read-write 8-bit memory mapped register)
 *   "Modem Control Register"
 *------------------------------------------------------------------
 */
#define UART_MCR 0x11000004
#define UART_MCR_PTR (uint8_t *)(0x11000004)

  /* This bit controls the Data Terminal Ready output.  */ 
  #define UART_MCR_F_DTR 0x00000001
  #define UART_MCR_F_DTR_OFFSET 0

  /* This bit controls the Request To Send output.  */ 
  #define UART_MCR_F_RTS 0x00000002
  #define UART_MCR_F_RTS_OFFSET 1

  /* This bit controls the Output 1 auxiliary used designated output.  */ 
  #define UART_MCR_F_OUT1 0x00000004
  #define UART_MCR_F_OUT1_OFFSET 2

  /* This bit controls the Output 2 auxiliary used designated output.  */ 
  #define UART_MCR_F_OUT2 0x00000008
  #define UART_MCR_F_OUT2_OFFSET 3

  /* This bit (when set) enables loopback mode operation of UART.  */ 
  #define UART_MCR_F_LOOP 0x00000010
  #define UART_MCR_F_LOOP_OFFSET 4


#ifndef __ASSEMBLER__

inline uint8_t uart_read_mcr(void)
{
	return REG8(UART_MCR);
}

inline void uart_write_mcr(uint8_t value)
{
	REG8(UART_MCR) = value;
}

inline uint8_t uart_rw_mcr(uint8_t value)
{
	return rw_reg8(UART_MCR_PTR, value);
}

inline uint8_t uart_set_mcr(uint_csr32_t setmask)
{
	return set_reg8(UART_MCR_PTR, setmask);
}

inline uint8_t uart_clear_mcr(uint_csr32_t clrmask)
{
	return clear_reg8(UART_MCR_PTR, clrmask);
}
#endif

/*------------------------------------------------------------------
 * register LSR @ 0x11000005
 *   (read-write 8-bit memory mapped register)
 *   "Line Status Register
This register provides data transfer status.
Although this register can be written, user is supposed to only read it."
 *------------------------------------------------------------------
 */
#define UART_LSR 0x11000005
#define UART_LSR_PTR (uint8_t *)(0x11000005)

  /* Data Ready.
This bit is set when incoming character has been received and is available in RBR of FIFO.
It is reset, when all data has been read from RBR of FIFO. */ 
  #define UART_LSR_F_DR 0x00000001
  #define UART_LSR_F_DR_OFFSET 0

  /* Overrun Error indicator bit.
This bit is set if next character has been received before RBR has been read or if next character has been received when FIFO was already full. */ 
  #define UART_LSR_F_OE 0x00000002
  #define UART_LSR_F_OE_OFFSET 1

  /* Parity Error Bit. It indicates current received character does not have correct even or odd parity.
Bit is cleared whenever the LSR is read. */ 
  #define UART_LSR_F_PE 0x00000004
  #define UART_LSR_F_PE_OFFSET 2

  /* Framing error bit. It indicates current received character did not have a valid stop bit.
Bit is cleared whenever the LSR is read. */ 
  #define UART_LSR_F_FE 0x00000008
  #define UART_LSR_F_FE_OFFSET 3

  /* Break Interrupt. */ 
  #define UART_LSR_F_BI 0x00000010
  #define UART_LSR_F_BI_OFFSET 4

  /* Transmitter Holding Register Empty indicator.
It indicates UART is ready to accept new character for transmission.
This bit is cleared, when at least one byte is written to transmitter FIFO. */ 
  #define UART_LSR_F_THRE 0x00000020
  #define UART_LSR_F_THRE_OFFSET 5

  /* Transmitter EMpTy indicator.
It indicates both transmitter holding register (THR) and transmitter shift register (TSR) are empty.
In FIFO mode this bit is set when FIFO and TSR are empty. */ 
  #define UART_LSR_F_TEMT 0x00000040
  #define UART_LSR_F_TEMT_OFFSET 6

  /* Error In FIFO.
In FIFO mode only this bit is set, when there is at least one parity error, framing error or break indication in the FIFO.
Bit is cleared, when LSR is read, provided there are no further errors in FIFO. */ 
  #define UART_LSR_F_EIF 0x00000080
  #define UART_LSR_F_EIF_OFFSET 7


#ifndef __ASSEMBLER__

inline uint8_t uart_read_lsr(void)
{
	return REG8(UART_LSR);
}

inline void uart_write_lsr(uint8_t value)
{
	REG8(UART_LSR) = value;
}

inline uint8_t uart_rw_lsr(uint8_t value)
{
	return rw_reg8(UART_LSR_PTR, value);
}

inline uint8_t uart_set_lsr(uint_csr32_t setmask)
{
	return set_reg8(UART_LSR_PTR, setmask);
}

inline uint8_t uart_clear_lsr(uint_csr32_t clrmask)
{
	return clear_reg8(UART_LSR_PTR, clrmask);
}
#endif

/*------------------------------------------------------------------
 * register MSR @ 0x11000006
 *   (read-write 8-bit memory mapped register)
 *   "Modem Status Register
This register provides status of the control lines from peripheral device."
 *------------------------------------------------------------------
 */
#define UART_MSR 0x11000006
#define UART_MSR_PTR (uint8_t *)(0x11000006)

  /* Delta Clear To Send.
Indicates CTS input has changed since it was last read.
Reading this field resets it's value to 0. */ 
  #define UART_MSR_F_DCTS 0x00000001
  #define UART_MSR_F_DCTS_OFFSET 0

  /* Delta Data Set Ready.
Indicates DSR input has changed since it was last read.
Reading this field resets it's value to 0. */ 
  #define UART_MSR_F_DDSR 0x00000002
  #define UART_MSR_F_DDSR_OFFSET 1

  /* Trailing Edge Ring Indicator.
This bit indicates RI input to the chip has changed from low to high state since it was last read.
Bit is cleared whenever the MSR is read. */ 
  #define UART_MSR_F_TERI 0x00000004
  #define UART_MSR_F_TERI_OFFSET 2

  /* Delta Data Carrier Detect.
This bit indicates DCD input has changed state since it was last read.
Bit is cleared whenever the MSR is read. */ 
  #define UART_MSR_F_DDCD 0x00000008
  #define UART_MSR_F_DDCD_OFFSET 3

  /* Clear To Send.
This bit is ~CTS input. In loop-back mode this bit is equivalent of MCR[RTS].
Bit is cleared whenever the MSR is read. */ 
  #define UART_MSR_F_CTS 0x00000010
  #define UART_MSR_F_CTS_OFFSET 4

  /* Clear To Send.
This bit is ~DSR input. In loop-back mode this bit is equivalent of MCR[DTR].
Bit is cleared whenever the MSR is read. */ 
  #define UART_MSR_F_DSR 0x00000020
  #define UART_MSR_F_DSR_OFFSET 5

  /* Ring Indicator.
This bit is ~RI input. In loop-back mode this bit is equivalent of MCR[OUT1].
Bit is cleared whenever the MSR is read. */ 
  #define UART_MSR_F_RI 0x00000040
  #define UART_MSR_F_RI_OFFSET 6


#ifndef __ASSEMBLER__

inline uint8_t uart_read_msr(void)
{
	return REG8(UART_MSR);
}

inline void uart_write_msr(uint8_t value)
{
	REG8(UART_MSR) = value;
}

inline uint8_t uart_rw_msr(uint8_t value)
{
	return rw_reg8(UART_MSR_PTR, value);
}

inline uint8_t uart_set_msr(uint_csr32_t setmask)
{
	return set_reg8(UART_MSR_PTR, setmask);
}

inline uint8_t uart_clear_msr(uint_csr32_t clrmask)
{
	return clear_reg8(UART_MSR_PTR, clrmask);
}
#endif

/*------------------------------------------------------------------
 * register SCR @ 0x11000007
 *   (read-write 8-bit memory mapped register)
 *   "SCRatchpad register.
This register does not control UART operation. It can be used by programmer as temporary buffer."
 *------------------------------------------------------------------
 */
#define UART_SCR 0x11000007
#define UART_SCR_PTR (uint8_t *)(0x11000007)


#ifndef __ASSEMBLER__

inline uint8_t uart_read_scr(void)
{
	return REG8(UART_SCR);
}

inline void uart_write_scr(uint8_t value)
{
	REG8(UART_SCR) = value;
}

inline uint8_t uart_rw_scr(uint8_t value)
{
	return rw_reg8(UART_SCR_PTR, value);
}

inline uint8_t uart_set_scr(uint_csr32_t setmask)
{
	return set_reg8(UART_SCR_PTR, setmask);
}

inline uint8_t uart_clear_scr(uint_csr32_t clrmask)
{
	return clear_reg8(UART_SCR_PTR, clrmask);
}
#endif

/*------------------------------------------------------------------
 * register DDLL @ 0x11000008
 *   (read-only 8-bit memory mapped register)
 *   "DLL (alias LSB-DL): divisor latch LSB. Defines bits [7:0] of divisor.
This is DLL read only copy of register mirrored to directly accessible address (no DLAB manipulation required).
It's value is always equal to DLL."
 *------------------------------------------------------------------
 */
#define UART_DDLL 0x11000008
#define UART_DDLL_PTR (uint8_t *)(0x11000008)


#ifndef __ASSEMBLER__

inline uint8_t uart_read_ddll(void)
{
	return REG8(UART_DDLL);
}
#endif

/*------------------------------------------------------------------
 * register DDLM @ 0x11000009
 *   (read-only 8-bit memory mapped register)
 *   "DLM (alias MSB-DL): divisor latch MSB. Defines bits [15:8] of divisor.
This is DLM read only copy of register mirrored to directly accessible address (no DLAB manipulation required).
It's value is always equal to DLM."
 *------------------------------------------------------------------
 */
#define UART_DDLM 0x11000009
#define UART_DDLM_PTR (uint8_t *)(0x11000009)


#ifndef __ASSEMBLER__

inline uint8_t uart_read_ddlm(void)
{
	return REG8(UART_DDLM);
}
#endif

/*------------------------------------------------------------------
 * register TxFFL @ 0x1100000a
 *   (read-write 8-bit memory mapped register)
 *   "Transmitter FIFO fill level"
 *------------------------------------------------------------------
 */
#define UART_TXFFL 0x1100000a
#define UART_TXFFL_PTR (uint8_t *)(0x1100000a)


#ifndef __ASSEMBLER__

inline uint8_t uart_read_txffl(void)
{
	return REG8(UART_TXFFL);
}

inline void uart_write_txffl(uint8_t value)
{
	REG8(UART_TXFFL) = value;
}

inline uint8_t uart_rw_txffl(uint8_t value)
{
	return rw_reg8(UART_TXFFL_PTR, value);
}

inline uint8_t uart_set_txffl(uint_csr32_t setmask)
{
	return set_reg8(UART_TXFFL_PTR, setmask);
}

inline uint8_t uart_clear_txffl(uint_csr32_t clrmask)
{
	return clear_reg8(UART_TXFFL_PTR, clrmask);
}
#endif

/*------------------------------------------------------------------
 * register RxFFL @ 0x1100000b
 *   (read-write 8-bit memory mapped register)
 *   "Receiver FIFO fill level"
 *------------------------------------------------------------------
 */
#define UART_RXFFL 0x1100000b
#define UART_RXFFL_PTR (uint8_t *)(0x1100000b)


#ifndef __ASSEMBLER__

inline uint8_t uart_read_rxffl(void)
{
	return REG8(UART_RXFFL);
}

inline void uart_write_rxffl(uint8_t value)
{
	REG8(UART_RXFFL) = value;
}

inline uint8_t uart_rw_rxffl(uint8_t value)
{
	return rw_reg8(UART_RXFFL_PTR, value);
}

inline uint8_t uart_set_rxffl(uint_csr32_t setmask)
{
	return set_reg8(UART_RXFFL_PTR, setmask);
}

inline uint8_t uart_clear_rxffl(uint_csr32_t clrmask)
{
	return clear_reg8(UART_RXFFL_PTR, clrmask);
}
#endif

/*------------------------------------------------------------------
 * register rev0 @ 0x1100000c
 *   (read-only 8-bit memory mapped register)
 *   "bits 0:7 of UART revision"
 *------------------------------------------------------------------
 */
#define UART_REV0 0x1100000c
#define UART_REV0_PTR (uint8_t *)(0x1100000c)


#ifndef __ASSEMBLER__

inline uint8_t uart_read_rev0(void)
{
	return REG8(UART_REV0);
}
#endif

/*------------------------------------------------------------------
 * register rev1 @ 0x1100000d
 *   (read-only 8-bit memory mapped register)
 *   "bits 8:15 of UART revision"
 *------------------------------------------------------------------
 */
#define UART_REV1 0x1100000d
#define UART_REV1_PTR (uint8_t *)(0x1100000d)


#ifndef __ASSEMBLER__

inline uint8_t uart_read_rev1(void)
{
	return REG8(UART_REV1);
}
#endif

/*------------------------------------------------------------------
 * register rev2 @ 0x1100000e
 *   (read-only 8-bit memory mapped register)
 *   "bits 16:23 of UART revision"
 *------------------------------------------------------------------
 */
#define UART_REV2 0x1100000e
#define UART_REV2_PTR (uint8_t *)(0x1100000e)


#ifndef __ASSEMBLER__

inline uint8_t uart_read_rev2(void)
{
	return REG8(UART_REV2);
}
#endif

/*------------------------------------------------------------------
 * register rev3 @ 0x1100000f
 *   (read-only 8-bit memory mapped register)
 *   "bits 24:31 of UART revision"
 *------------------------------------------------------------------
 */
#define UART_REV3 0x1100000f
#define UART_REV3_PTR (uint8_t *)(0x1100000f)


#ifndef __ASSEMBLER__

inline uint8_t uart_read_rev3(void)
{
	return REG8(UART_REV3);
}
#endif

/*------------------------------------------------------------------
 * register CLKDIVP_L @ 0x11000010
 *   (read-write 8-bit memory mapped register)
 *   "bits P[0:7] of P/Q divider numerator.
Baud rate is generated by firstly dividing a CLK signal by ratio of [CLKDIVQ/CLKDIVP], 
then by [DLM,DLL] and finally by 16.
It is required that CLKDIVQ>=CLKDIVP."
 *------------------------------------------------------------------
 */
#define UART_CLKDIVP_L 0x11000010
#define UART_CLKDIVP_L_PTR (uint8_t *)(0x11000010)


#ifndef __ASSEMBLER__

inline uint8_t uart_read_clkdivp_l(void)
{
	return REG8(UART_CLKDIVP_L);
}

inline void uart_write_clkdivp_l(uint8_t value)
{
	REG8(UART_CLKDIVP_L) = value;
}

inline uint8_t uart_rw_clkdivp_l(uint8_t value)
{
	return rw_reg8(UART_CLKDIVP_L_PTR, value);
}

inline uint8_t uart_set_clkdivp_l(uint_csr32_t setmask)
{
	return set_reg8(UART_CLKDIVP_L_PTR, setmask);
}

inline uint8_t uart_clear_clkdivp_l(uint_csr32_t clrmask)
{
	return clear_reg8(UART_CLKDIVP_L_PTR, clrmask);
}
#endif

/*------------------------------------------------------------------
 * register CLKDIVP_M @ 0x11000011
 *   (read-write 8-bit memory mapped register)
 *   "bits P[15:8] of P/Q divider numerator
Baud rate is generated by firstly dividing a CLK signal by ratio of [CLKDIVQ/CLKDIVP], 
then by [DLM,DLL] and finally by 16.
It is required that CLKDIVQ>=CLKDIVP."
 *------------------------------------------------------------------
 */
#define UART_CLKDIVP_M 0x11000011
#define UART_CLKDIVP_M_PTR (uint8_t *)(0x11000011)


#ifndef __ASSEMBLER__

inline uint8_t uart_read_clkdivp_m(void)
{
	return REG8(UART_CLKDIVP_M);
}

inline void uart_write_clkdivp_m(uint8_t value)
{
	REG8(UART_CLKDIVP_M) = value;
}

inline uint8_t uart_rw_clkdivp_m(uint8_t value)
{
	return rw_reg8(UART_CLKDIVP_M_PTR, value);
}

inline uint8_t uart_set_clkdivp_m(uint_csr32_t setmask)
{
	return set_reg8(UART_CLKDIVP_M_PTR, setmask);
}

inline uint8_t uart_clear_clkdivp_m(uint_csr32_t clrmask)
{
	return clear_reg8(UART_CLKDIVP_M_PTR, clrmask);
}
#endif

/*------------------------------------------------------------------
 * register CLKDIVQ_L @ 0x11000012
 *   (read-write 8-bit memory mapped register)
 *   "bits Q[0:7] of P/Q divider denominator
Baud rate is generated by firstly dividing a CLK signal by ratio of [CLKDIVQ/CLKDIVP], 
then by [DLM,DLL] and finally by 16.
It is required that CLKDIVQ>=CLKDIVP."
 *------------------------------------------------------------------
 */
#define UART_CLKDIVQ_L 0x11000012
#define UART_CLKDIVQ_L_PTR (uint8_t *)(0x11000012)


#ifndef __ASSEMBLER__

inline uint8_t uart_read_clkdivq_l(void)
{
	return REG8(UART_CLKDIVQ_L);
}

inline void uart_write_clkdivq_l(uint8_t value)
{
	REG8(UART_CLKDIVQ_L) = value;
}

inline uint8_t uart_rw_clkdivq_l(uint8_t value)
{
	return rw_reg8(UART_CLKDIVQ_L_PTR, value);
}

inline uint8_t uart_set_clkdivq_l(uint_csr32_t setmask)
{
	return set_reg8(UART_CLKDIVQ_L_PTR, setmask);
}

inline uint8_t uart_clear_clkdivq_l(uint_csr32_t clrmask)
{
	return clear_reg8(UART_CLKDIVQ_L_PTR, clrmask);
}
#endif

/*------------------------------------------------------------------
 * register CLKDIVQ_M @ 0x11000013
 *   (read-write 8-bit memory mapped register)
 *   "bits Q[15:8] of P/Q divider denominator
Baud rate is generated by firstly dividing a CLK signal by ratio of [CLKDIVQ/CLKDIVP], 
then by [DLM,DLL] and finally by 16.
It is required that CLKDIVQ>=CLKDIVP."
 *------------------------------------------------------------------
 */
#define UART_CLKDIVQ_M 0x11000013
#define UART_CLKDIVQ_M_PTR (uint8_t *)(0x11000013)


#ifndef __ASSEMBLER__

inline uint8_t uart_read_clkdivq_m(void)
{
	return REG8(UART_CLKDIVQ_M);
}

inline void uart_write_clkdivq_m(uint8_t value)
{
	REG8(UART_CLKDIVQ_M) = value;
}

inline uint8_t uart_rw_clkdivq_m(uint8_t value)
{
	return rw_reg8(UART_CLKDIVQ_M_PTR, value);
}

inline uint8_t uart_set_clkdivq_m(uint_csr32_t setmask)
{
	return set_reg8(UART_CLKDIVQ_M_PTR, setmask);
}

inline uint8_t uart_clear_clkdivq_m(uint_csr32_t clrmask)
{
	return clear_reg8(UART_CLKDIVQ_M_PTR, clrmask);
}
#endif


#endif // __regaccess_Beyond_Semiconductor_BA5x_BydAHBSOC_1_0_UART__
