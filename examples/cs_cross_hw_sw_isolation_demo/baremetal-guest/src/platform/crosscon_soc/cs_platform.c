#include <plat.h>
#include <beyond_uart.h>
#include <crosscon_soc.h>

void uart_init(){
    UART_Init(CPU_CLK, 9600);
    //UART_Init(CPU_CLK, 19200);
    //UART_Init(CPU_CLK, 115200);
}

void uart_putc(char c)
{
    UART_PutC(c);
}

char uart_getchar(void)
{
    return UART_GetC();
}

void uart_enable_rxirq()
{
    // Currently not supported.
}

void uart_clear_rxirq()
{
    // Currently not supported.
}
