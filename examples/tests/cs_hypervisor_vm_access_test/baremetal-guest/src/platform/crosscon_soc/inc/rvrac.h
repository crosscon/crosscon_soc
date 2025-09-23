/**
 * Generic CSR & memory mapped register access macros & functions
 *   for risc-v.
 */

#ifndef _BEYOND_RVRAC_H_
#define _BEYOND_RVRAC_H_

#ifndef __ASSEMBLER__
#include <stdint.h>
#endif

#if __riscv_xlen==32

#ifndef __ASSEMBLER__
typedef uint32_t uint_xlen_t;
typedef uint32_t uint_csr32_t;
#endif

#else

// this header only supports RV32
#error "unsupported XLEN"

#endif

// ============================================================================
// Generic helper macros & functions
// ============================================================================

/**
 * Masks out other bits of register value "val" except those belonging to
 * filed "fld".
 *   @param val retister value
 *   @param fld field name
 * 
 * example: MASKREGFIELD(x, CSR_MSTATUS_F_VS)
 *   the above will zero out all bits extept VS
 */
#define MASKREGFIELD(val, fld) ((val) & (fld))

/**
 * Shifts value from bit positions [n:0] to its position within register 
 * and masks away bits that are not part of chosen field.
 *   @param val value to shif
 *   @param fld name of field
 * 
 * example: VAL2REGFIELD(CSR_MSTATUS_F_VS_E_INITIAL, CSR_MSTATUS_F_VS)
 */
#define VAL2REGFIELD(val, fld) MASKREGFIELD((val << fld##_OFFSET), (fld))

/**
 * Shifts register field to bit positions [n:0] and masks away bits that
 * are not part of chosen field.
 *   @param val 
 */
#define REGFIELD2VAL(val, fld) (MASKREGFIELD(val, fld) >> fld##_OFFSET)

//watchdog_timer_MODE_F_ENABLE

// ============================================================================
// CSR registers
// ============================================================================

/**
 * Returns value of CSR register #csrno
 */
#define READ_CSRNO(csrno) ({ \
	uint_csr32_t __rv; \
	asm volatile ("csrr %0 , %1" : "=r"(__rv) : "n"(csrno)); \
	__rv; \
})

/**
 * Returns value of CSR register named "csr"
 */
#define READ_CSR(csr) ({ \
	uint_csr32_t __rv; \
	asm volatile ("csrr %0 ," #csr : "=r"(__rv)); \
	__rv; \
})

/**
 * Sets value of CSR register #csrno to value val.
 */
#define WRITE_CSRNO(csrno, val) ({ \
	asm volatile ("csrw %0, %1" :: "I"(csrno), "rK"(val)); \
})

/**
 * Sets value of CSR register named "csr" to value val.
 */
#define WRITE_CSR(csr, val) ({ \
  asm volatile ("csrw " #csr ", 0" :: "rK"(val)); \
})

/**
 * Sets value of CSR register #csrno to value val and
 * returns previous value of same CSR register.
 */
#define RW_CSRNO(csrno, val) ({ \
	uint_csr32_t __rv; \
	asm volatile ("csrrw %0, %1, %2" : "=r"(__rv) : "I"(csrno), "rK"(val)); \
	__rv; \
})

/**
 * Sets value of CSR register "csr" to value val and
 * returns previous value of same CSR register.
 */
#define RW_CSR(csr, val) ({ \
	uint_csr32_t __rv; \
	asm volatile ("csrrw %0, " #csr ", %1" : "=r"(__rv) : "rK"(val)); \
	__rv; \
})

/**
 * Sets all bits that are set in "setmask" to 1 in CSR register #csrno.
 * Return previous value of same CSR register.
 */
#define SET_CSRNO(csrno, setmask) ({ \
	uint_csr32_t __rv; \
	asm volatile ("csrrs %0, %1, %2" : "=r"(__rv) : "I"(csrno), "rK"(setmask)); \
	__rv; \
})

/**
 * Sets all bits that are set in "setmask" to 1 in CSR register "csr".
 * Return previous value of same CSR register.
 */
#define SET_CSR(csr, setmask) ({ \
	uint_csr32_t __rv; \
	asm volatile ("csrrs %0, " #csr ", %1" : "=r"(__rv) : "rK"(setmask)); \
	__rv; \
})

/**
 * Clears all bits that are set in "setmask" to 1 in CSR register #csrno.
 * Return previous value of same CSR register.
 */
#define CLEAR_CSRNO(csrno, clrmask) ({ \
	uint_csr32_t __rv; \
	asm volatile ("csrrc %0, %1, %2" : "=r"(__rv) : "I"(csrno), "rK"(clrmask)); \
	__rv; \
})

/**
 * Clears all bits that are set in "setmask" to 1 in CSR register "csr".
 * Return previous value of same CSR register.
 */
#define CLEAR_CSR(csr, clrmask) ({ \
	uint_csr32_t __rv; \
	asm volatile ("csrrc %0, " #csr ", %1" : "=r"(__rv) : "rK"(clrmask)); \
	__rv; \
})

// ============================================================================
// Memory mapped registers
// ============================================================================

/* Register access macros */

#define REG8(addr) *((volatile uint8_t *)(addr))
#define REG16(addr) *((volatile uint16_t *)(addr))
#define REG32(addr) *((volatile uint32_t *)(addr))
#define REG64(addr) *((volatile uint64_t *)(addr))

#ifndef __ASSEMBLER__

/**
 * Access functions follow this naming pattern:
 *
 *   peripheral_read_registername()
 *     This function reads and returns value of register.
 *   peripheral_write_registername(value)
 *     This function writes new value to a register.
 *   peripheral_rw_registername(value)
 *     Writes new value to register and returns previous value. Implementation
 *     might be atomic or not (see comments below)
 *   peripheral_set_registername(omask)
 *     Reads value of register, ors it with omask and writes or-ed value back.
 *     (Effectively sets bits set in omask. Might be atomic.)
 *   peripheral_clear_registername(cmask)
 *     Reads value of register, ands it with ~cmask and writes and-ed value back.
 *     (Effectively clears bits set in omask. Might be atomic.)
 */

#if __riscv_atomic

/*
 * Atomic rw/set/clear implementations are only available for 32-bit registers
 * and only if atomic instruction set is supported on target.
 * In all other cases rw/set/clear functions are not atomic.
 */
__attribute__((unused))
static inline uint32_t rw_reg32(uint32_t *mad, uint32_t nv)
{
	uint32_t result;
	asm volatile ("amoswap.w %0, %2, %1" : "=r"(result), "+A"(*mad) : "r" (nv));
	return result;
}

__attribute__((unused))
static inline uint32_t set_reg32(uint32_t *mad, uint32_t omask)
{
	uint32_t result;
	asm volatile ("amoor.w %0, %2, %1" : "=r"(result), "+A"(*mad) : "r" (omask));
	return result;
}

__attribute__((unused))
static inline uint32_t clear_reg32(uint32_t *mad, uint32_t amask)
{
	uint32_t result;
	asm volatile ("amoand.w %0, %2, %1" : "=r"(result), "+A"(*mad) : "r" (~amask));
	return result;
}
#else

// non-atomic 32-bit rw/set/clear

__attribute__((unused))
static inline uint32_t rw_reg32(uint32_t *mad, uint32_t nv)
{
	uint32_t result;
	result = REG32(mad);
	REG32(mad) = nv;
	return result;
}

__attribute__((unused))
static inline uint32_t set_reg32(uint32_t *mad, uint32_t omask)
{
	uint32_t result;
	result = REG32(mad);
	REG32(mad) = (result | omask);
	return result;
}

__attribute__((unused))
static inline uint32_t clear_reg32(uint32_t *mad, uint32_t amask)
{
	uint32_t result;
	result = REG32(mad);
	REG32(mad) = (result & ~amask);
	return result;
}

#endif

__attribute__((unused))
static inline uint16_t rw_reg16(uint16_t *mad, uint16_t nv)
{
	uint16_t result;
	result = REG16(mad);
	REG16(mad) = nv;
	return result;
}

__attribute__((unused))
static inline uint16_t set_reg16(uint16_t *mad, uint16_t omask)
{
	uint16_t result;
	result = REG16(mad);
	REG16(mad) = (result | omask);
	return result;
}

__attribute__((unused))
static inline uint16_t clear_reg16(uint16_t *mad, uint16_t amask)
{
	uint16_t result;
	result = REG16(mad);
	REG16(mad) = (result & ~amask);
	return result;
}

__attribute__((unused))
static inline uint8_t rw_reg8(uint8_t *mad, uint8_t nv)
{
	uint8_t result;
	result = REG8(mad);
	REG8(mad) = nv;
	return result;
}

__attribute__((unused))
static inline uint8_t set_reg8(uint8_t *mad, uint8_t omask)
{
	uint8_t result;
	result = REG8(mad);
	REG8(mad) = (result | omask);
	return result;
}

__attribute__((unused))
static inline uint8_t clear_reg8(uint8_t *mad, uint8_t amask)
{
	uint8_t result;
	result = REG8(mad);
	REG8(mad) = (result & ~amask);
	return result;
}

#endif

#endif /* _BEYOND_RVRAC_H_ */