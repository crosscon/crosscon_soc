#include <crosscon_soc.h>

#include <plat.h>
#include <8250_uart.h>

#include <stdint.h>
#include <stdbool.h>

#define VIRT_UART16550_INTERRUPT	10

#define VIRT_UART16550_ADDR		UART_ADDR

#define VIRT_UART_BAUDRATE		115200
#define VIRT_UART_SHIFTREG_ADDR		25000000

void uart_init(){
    uart8250_init(VIRT_UART16550_ADDR, VIRT_UART_SHIFTREG_ADDR,
			     VIRT_UART_BAUDRATE, 0, 1);
}

void uart_putc(char c)
{
    uart8250_putc(c);
}

char uart_getchar(void)
{
    return uart8250_getc();
}

void uart_enable_rxirq()
{
    uart8250_enable_rx_int();
}

void uart_clear_rxirq()
{
    uart8250_interrupt_handler(); 
}

// Set address range entry of PG in restricted address space mode.
void set_pg_rspace_entry(
    uint32_t* pg_csrs_base,
    uint8_t entry,
    uint8_t did,
    uint32_t from_addr,
    uint32_t to_addr,
    bool allow_read,
    bool allow_write)
{
    pg_csrs_base[PG_RAS_ADDR_FIRST_REG_ADDR + entry] = from_addr;
    pg_csrs_base[PG_RAS_ADDR_FIRST_REG_ADDR + entry + 1] = to_addr;
    pg_csrs_base[PG_RAS_ACC_PRM_FIRST_REG_ADDR + entry] = (uint32_t) (
        (1 << PG_RAS_ACC_PRM_REG_A_BIT) |
        (did << PG_RAS_ACC_PRM_REG_DID_LOW) |
        (allow_read << PG_RAS_ACC_PRM_REG_R_BIT) |
        (allow_write << PG_RAS_ACC_PRM_REG_W_BIT));
}

// Clear address range entry of PG in restricted address space mode.
void clear_pg_rspace_entry(uint32_t* pg_csrs_base, uint8_t entry) {
    pg_csrs_base[PG_RAS_ACC_PRM_FIRST_REG_ADDR + entry] = (uint32_t) (0 << PG_RAS_ACC_PRM_REG_A_BIT);
}
