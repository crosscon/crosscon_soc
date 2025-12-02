#include <rvrac.h>
#include <beyond_uart.h>
#include <plat.h>

uint8_t uart_read_rbr(void)
{
	return REG8(UART_RBR);
}

uint8_t uart_read_thr(void)
{
	return REG8(UART_THR);
}

void uart_write_thr(uint8_t value)
{
	REG8(UART_THR) = value;
}

uint8_t uart_rw_thr(uint8_t value)
{
	return rw_reg8(UART_THR_PTR, value);
}

uint8_t uart_set_thr(uint_csr32_t setmask)
{
	return set_reg8(UART_THR_PTR, setmask);
}

uint8_t uart_clear_thr(uint_csr32_t clrmask)
{
	return clear_reg8(UART_THR_PTR, clrmask);
}

uint8_t uart_read_dll(void)
{
	return REG8(UART_DLL);
}

void uart_write_dll(uint8_t value)
{
	REG8(UART_DLL) = value;
}

uint8_t uart_rw_dll(uint8_t value)
{
	return rw_reg8(UART_DLL_PTR, value);
}

uint8_t uart_set_dll(uint_csr32_t setmask)
{
	return set_reg8(UART_DLL_PTR, setmask);
}

uint8_t uart_clear_dll(uint_csr32_t clrmask)
{
	return clear_reg8(UART_DLL_PTR, clrmask);
}

uint8_t uart_read_ier(void)
{
	return REG8(UART_IER);
}

void uart_write_ier(uint8_t value)
{
	REG8(UART_IER) = value;
}

uint8_t uart_rw_ier(uint8_t value)
{
	return rw_reg8(UART_IER_PTR, value);
}

uint8_t uart_set_ier(uint_csr32_t setmask)
{
	return set_reg8(UART_IER_PTR, setmask);
}

uint8_t uart_clear_ier(uint_csr32_t clrmask)
{
	return clear_reg8(UART_IER_PTR, clrmask);
}

uint8_t uart_read_dlm(void)
{
	return REG8(UART_DLM);
}

void uart_write_dlm(uint8_t value)
{
	REG8(UART_DLM) = value;
}

uint8_t uart_rw_dlm(uint8_t value)
{
	return rw_reg8(UART_DLM_PTR, value);
}

uint8_t uart_set_dlm(uint_csr32_t setmask)
{
	return set_reg8(UART_DLM_PTR, setmask);
}

uint8_t uart_clear_dlm(uint_csr32_t clrmask)
{
	return clear_reg8(UART_DLM_PTR, clrmask);
}

uint8_t uart_read_iir(void)
{
	return REG8(UART_IIR);
}

uint8_t uart_read_fcr(void)
{
	return REG8(UART_FCR);
}

void uart_write_fcr(uint8_t value)
{
	REG8(UART_FCR) = value;
}

uint8_t uart_rw_fcr(uint8_t value)
{
	return rw_reg8(UART_FCR_PTR, value);
}

uint8_t uart_set_fcr(uint_csr32_t setmask)
{
	return set_reg8(UART_FCR_PTR, setmask);
}

uint8_t uart_clear_fcr(uint_csr32_t clrmask)
{
	return clear_reg8(UART_FCR_PTR, clrmask);
}

uint8_t uart_read_lcr(void)
{
	return REG8(UART_LCR);
}

void uart_write_lcr(uint8_t value)
{
	REG8(UART_LCR) = value;
}

uint8_t uart_rw_lcr(uint8_t value)
{
	return rw_reg8(UART_LCR_PTR, value);
}

uint8_t uart_set_lcr(uint_csr32_t setmask)
{
	return set_reg8(UART_LCR_PTR, setmask);
}

uint8_t uart_clear_lcr(uint_csr32_t clrmask)
{
	return clear_reg8(UART_LCR_PTR, clrmask);
}

uint8_t uart_read_mcr(void)
{
	return REG8(UART_MCR);
}

void uart_write_mcr(uint8_t value)
{
	REG8(UART_MCR) = value;
}

uint8_t uart_rw_mcr(uint8_t value)
{
	return rw_reg8(UART_MCR_PTR, value);
}

uint8_t uart_set_mcr(uint_csr32_t setmask)
{
	return set_reg8(UART_MCR_PTR, setmask);
}

uint8_t uart_clear_mcr(uint_csr32_t clrmask)
{
	return clear_reg8(UART_MCR_PTR, clrmask);
}

uint8_t uart_read_lsr(void)
{
	return REG8(UART_LSR);
}

void uart_write_lsr(uint8_t value)
{
	REG8(UART_LSR) = value;
}

uint8_t uart_rw_lsr(uint8_t value)
{
	return rw_reg8(UART_LSR_PTR, value);
}

uint8_t uart_set_lsr(uint_csr32_t setmask)
{
	return set_reg8(UART_LSR_PTR, setmask);
}

uint8_t uart_clear_lsr(uint_csr32_t clrmask)
{
	return clear_reg8(UART_LSR_PTR, clrmask);
}

uint8_t uart_read_msr(void)
{
	return REG8(UART_MSR);
}

void uart_write_msr(uint8_t value)
{
	REG8(UART_MSR) = value;
}

uint8_t uart_rw_msr(uint8_t value)
{
	return rw_reg8(UART_MSR_PTR, value);
}

uint8_t uart_set_msr(uint_csr32_t setmask)
{
	return set_reg8(UART_MSR_PTR, setmask);
}

uint8_t uart_clear_msr(uint_csr32_t clrmask)
{
	return clear_reg8(UART_MSR_PTR, clrmask);
}

uint8_t uart_read_scr(void)
{
	return REG8(UART_SCR);
}

void uart_write_scr(uint8_t value)
{
	REG8(UART_SCR) = value;
}

uint8_t uart_rw_scr(uint8_t value)
{
	return rw_reg8(UART_SCR_PTR, value);
}

uint8_t uart_set_scr(uint_csr32_t setmask)
{
	return set_reg8(UART_SCR_PTR, setmask);
}

uint8_t uart_clear_scr(uint_csr32_t clrmask)
{
	return clear_reg8(UART_SCR_PTR, clrmask);
}

uint8_t uart_read_ddll(void)
{
	return REG8(UART_DDLL);
}

uint8_t uart_read_ddlm(void)
{
	return REG8(UART_DDLM);
}

uint8_t uart_read_txffl(void)
{
	return REG8(UART_TXFFL);
}

void uart_write_txffl(uint8_t value)
{
	REG8(UART_TXFFL) = value;
}

uint8_t uart_rw_txffl(uint8_t value)
{
	return rw_reg8(UART_TXFFL_PTR, value);
}

uint8_t uart_set_txffl(uint_csr32_t setmask)
{
	return set_reg8(UART_TXFFL_PTR, setmask);
}

uint8_t uart_clear_txffl(uint_csr32_t clrmask)
{
	return clear_reg8(UART_TXFFL_PTR, clrmask);
}

uint8_t uart_read_rxffl(void)
{
	return REG8(UART_RXFFL);
}

void uart_write_rxffl(uint8_t value)
{
	REG8(UART_RXFFL) = value;
}

uint8_t uart_rw_rxffl(uint8_t value)
{
	return rw_reg8(UART_RXFFL_PTR, value);
}

uint8_t uart_set_rxffl(uint_csr32_t setmask)
{
	return set_reg8(UART_RXFFL_PTR, setmask);
}

uint8_t uart_clear_rxffl(uint_csr32_t clrmask)
{
	return clear_reg8(UART_RXFFL_PTR, clrmask);
}

uint8_t uart_read_rev0(void)
{
	return REG8(UART_REV0);
}

uint8_t uart_read_rev1(void)
{
	return REG8(UART_REV1);
}

uint8_t uart_read_rev2(void)
{
	return REG8(UART_REV2);
}

uint8_t uart_read_rev3(void)
{
	return REG8(UART_REV3);
}

uint8_t uart_read_clkdivp_l(void)
{
	return REG8(UART_CLKDIVP_L);
}

void uart_write_clkdivp_l(uint8_t value)
{
	REG8(UART_CLKDIVP_L) = value;
}

uint8_t uart_rw_clkdivp_l(uint8_t value)
{
	return rw_reg8(UART_CLKDIVP_L_PTR, value);
}

uint8_t uart_set_clkdivp_l(uint_csr32_t setmask)
{
	return set_reg8(UART_CLKDIVP_L_PTR, setmask);
}

uint8_t uart_clear_clkdivp_l(uint_csr32_t clrmask)
{
	return clear_reg8(UART_CLKDIVP_L_PTR, clrmask);
}

uint8_t uart_read_clkdivp_m(void)
{
	return REG8(UART_CLKDIVP_M);
}

void uart_write_clkdivp_m(uint8_t value)
{
	REG8(UART_CLKDIVP_M) = value;
}

uint8_t uart_rw_clkdivp_m(uint8_t value)
{
	return rw_reg8(UART_CLKDIVP_M_PTR, value);
}

uint8_t uart_set_clkdivp_m(uint_csr32_t setmask)
{
	return set_reg8(UART_CLKDIVP_M_PTR, setmask);
}

uint8_t uart_clear_clkdivp_m(uint_csr32_t clrmask)
{
	return clear_reg8(UART_CLKDIVP_M_PTR, clrmask);
}

uint8_t uart_read_clkdivq_l(void)
{
	return REG8(UART_CLKDIVQ_L);
}

void uart_write_clkdivq_l(uint8_t value)
{
	REG8(UART_CLKDIVQ_L) = value;
}

uint8_t uart_rw_clkdivq_l(uint8_t value)
{
	return rw_reg8(UART_CLKDIVQ_L_PTR, value);
}

uint8_t uart_set_clkdivq_l(uint_csr32_t setmask)
{
	return set_reg8(UART_CLKDIVQ_L_PTR, setmask);
}

uint8_t uart_clear_clkdivq_l(uint_csr32_t clrmask)
{
	return clear_reg8(UART_CLKDIVQ_L_PTR, clrmask);
}

uint8_t uart_read_clkdivq_m(void)
{
	return REG8(UART_CLKDIVQ_M);
}

void uart_write_clkdivq_m(uint8_t value)
{
	REG8(UART_CLKDIVQ_M) = value;
}

uint8_t uart_rw_clkdivq_m(uint8_t value)
{
	return rw_reg8(UART_CLKDIVQ_M_PTR, value);
}

uint8_t uart_set_clkdivq_m(uint_csr32_t setmask)
{
	return set_reg8(UART_CLKDIVQ_M_PTR, setmask);
}

uint8_t uart_clear_clkdivq_m(uint_csr32_t clrmask)
{
	return clear_reg8(UART_CLKDIVQ_M_PTR, clrmask);
}

const unsigned int UART_CLK_IN = CPU_CLK;         /* Input UART clock (on bydahbsoc same as CPU clockrate) */

void UART_Init(unsigned int uart_clk_in, unsigned int uart_boud_rate)
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
	divisor = uart_clk_in / (16 * uart_boud_rate);
	uart_write_lcr(UART_LCR_F_DLAB);
	uart_write_dll(divisor & 0x000000ff);
	uart_write_dlm((divisor >> 8) & 0x000000ff);

	/* Set 8 bit char, 1 stop bit, no parity */
	uart_write_lcr(VAL2REGFIELD(UART_LCR_F_BITS_E_CHR8B, UART_LCR_F_BITS) |
	               VAL2REGFIELD(UART_LCR_F_STOP_E_STOP_1, UART_LCR_F_STOP) |
	               VAL2REGFIELD(UART_LCR_F_PARITY_E_NO_PARITY, UART_LCR_F_PARITY));
}

void UART_WaitForTHRE(void)
{
	unsigned char lsr;
	do {
		lsr = uart_read_lsr();
	} while (REGFIELD2VAL(lsr, UART_LSR_F_THRE) == 0);
}

void UART_WaitForData()
{
	unsigned char lsr;
	do {
		lsr = uart_read_lsr();
	} while ((lsr & UART_LSR_F_DR) == 0);
}

void UART_PutC(char c)
{
	UART_WaitForTHRE();
	uart_write_thr(c);
}

char UART_GetC(void)
{
	UART_WaitForData();
	return uart_read_rbr();
}

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
