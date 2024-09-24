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

/**
 * Simple C startup routine to setup CRT
 *
 * This calls preinit and init arrays even if no standard lib is used.
 *
 **/

#include <stddef.h>

typedef void (*function_t)();

// These symbols are defined by the linker script.
// See .ld file
extern function_t __preinit_array_start[] __attribute__((weak)) ;
extern function_t __preinit_array_end[] __attribute__((weak));
extern function_t __init_array_start[] __attribute__((weak));
extern function_t __init_array_end[] __attribute__((weak));

extern int main();

static void _bm_init(void)
{
	size_t i, count;

	// Call constructors (can be replaced by call to _init() if standard
	// library is used)
	count = __preinit_array_end - __preinit_array_start;
	for (i = 0; i < count; ++i) {
		__preinit_array_start[i]();
	}

	count = __init_array_end - __init_array_start;
	for (i = 0; i < count; i++) {
		__init_array_start[i]();
	}
}

/**
 * Called by _enter.
 */
void _start(int hartid)
{
	// Call to _bm_init can be replaced by _init() if standard library is used,
	// or removed, if not (C) constructors are used.
	_bm_init();

	main(0, NULL, NULL);
}
