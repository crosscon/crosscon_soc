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

#ifndef SYS_H_
#define SYS_H_

#include <stdint.h>

extern const unsigned int CPU_CLK;             /* CPU clockrate: 25MHz */
extern const unsigned int MTIME_CLK;           /* mtimer ticks with same frequency as CPU clock */
extern const unsigned int UART_CLK_IN;         /* Input UART clock (on bydahbsoc same as CPU clockrate) */
extern const unsigned int UART_BAUD_RATE;      /* UART baudrate to select */

/**
 * Any synchronous exception not handled elsewhere ends up looping here.
 */
void unhandled_exception();

/**
 * Any interrupt not handled elsewhere ends up looping here.
 */
void unhandled_interrupt();

void init_fpu();

/**
 * ecall trap handler function
 */
long __syscall_handler(long _a0, long _a1, long _a2, long _a3, long _a4, long _a5, long _a6, long syscall_id);

/**
 * handler for all non-ecall traps
 */
void __trap_handler(void);

/**
 *
 * @return
 */
uint64_t clint_get_time(void);
void clint_set_time_cmp(uint64_t clock);
void clint_offset_time_cmp(uint64_t clock_offset);

#endif /* SYS_H_ */
