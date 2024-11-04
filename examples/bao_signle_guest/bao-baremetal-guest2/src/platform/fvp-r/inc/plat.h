#ifndef PLAT_H
#define PLAT_H

#define PLAT_MEM_BASE 0x0
#define PLAT_MEM_SIZE 0x8000000

#define PLAT_GENERIC_TIMER_CNTCTL_BASE  (0xaa430000ull)

#define PLAT_GICD_BASE_ADDR (0xAF000000)
#define PLAT_GICR_BASE_ADDR (0xAF100000)

#define PLAT_UART_ADDR  0x9C0A0000
#define UART_IRQ_ID 38

#endif
