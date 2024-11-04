#ifndef PLAT_H
#define PLAT_H

#define PLAT_MEM_BASE 0x60000
#define PLAT_MEM_SIZE 0x0ffff

#define PLAT_TIMER_FREQ (25000000ull) //25 MHz

#define PLAT_UART_ADDR (0x10700000)
#define UART_IRQ_ID (10)

#define CPU_EXT_SSTC 1

#endif
