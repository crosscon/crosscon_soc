/*******************************************************************
 * CSR register definitions for
 * ============================
 * BA5x_BydAHBSOC, version: 1.0
 *   by 
 * Beyond Semiconductor
 * 
 * Created by sdtool 
 *   from sd/ba5x-byd-ahb-soc.sd.xml
 *   on 2022-11-25 14:23:57.902658
 *   using template src/templates/h/csr.jinja
 *******************************************************************
 */

 #ifndef __regaccess_Beyond_Semiconductor_BA5x_BydAHBSOC_1_0__
 #define __regaccess_Beyond_Semiconductor_BA5x_BydAHBSOC_1_0__

#include "rvrac.h"
/*------------------------------------------------------------------
 * register fflags @ 0x001
 *   (read-write 32-bit CSR mapped register)
 *   "Floating-Point Accrued Exceptions"
 *------------------------------------------------------------------
 */
#define CSR_FFLAGS 1
  // inexact 
  #define CSR_FFLAGS_F_NX 0x00000001
  #define CSR_FFLAGS_F_NX_OFFSET 0
  // underflow 
  #define CSR_FFLAGS_F_UF 0x00000002
  #define CSR_FFLAGS_F_UF_OFFSET 1
  // overflow 
  #define CSR_FFLAGS_F_OF 0x00000004
  #define CSR_FFLAGS_F_OF_OFFSET 2
  // divide by zero 
  #define CSR_FFLAGS_F_DZ 0x00000008
  #define CSR_FFLAGS_F_DZ_OFFSET 3
  // invalid operation 
  #define CSR_FFLAGS_F_NV 0x00000010
  #define CSR_FFLAGS_F_NV_OFFSET 4

#ifndef __ASSEMBLER__
static inline uint_csr32_t csr_read_fflags(void)
{
	return READ_CSRNO(CSR_FFLAGS);
}

static inline void csr_write_fflags(uint_csr32_t value)
{
	WRITE_CSRNO(CSR_FFLAGS, value);
}

static inline uint_csr32_t csr_rw_fflags(uint_csr32_t value)
{
	return RW_CSRNO(CSR_FFLAGS, value);
}

static inline uint_csr32_t csr_set_fflags(uint_csr32_t setmask)
{
	return SET_CSRNO(CSR_FFLAGS, setmask);
}

static inline uint_csr32_t csr_clear_fflags(uint_csr32_t clrmask)
{
	return CLEAR_CSRNO(CSR_FFLAGS, clrmask);
}
#endif

/*------------------------------------------------------------------
 * register frm @ 0x002
 *   (read-write 32-bit CSR mapped register)
 *   "Floating-Point Dynamic Rounding Mode"
 *------------------------------------------------------------------
 */
#define CSR_FRM 2
  // Rounding Mode 
  #define CSR_FRM_F_ROUNDING 0x00000007
  #define CSR_FRM_F_ROUNDING_OFFSET 0

    // Round to Nearest, ties to Even
    #define CSR_FRM_F_ROUNDING_E_RNE 0x0

    // Round to Zero
    #define CSR_FRM_F_ROUNDING_E_RTZ 0x1

    // Round Down (towards -infinite)
    #define CSR_FRM_F_ROUNDING_E_RD 0x2

    // Round Up (towards +infinite)
    #define CSR_FRM_F_ROUNDING_E_RUP 0x3

    // Round to Nearest, ties to Max Magnitude
    #define CSR_FRM_F_ROUNDING_E_RMM 0x4

#ifndef __ASSEMBLER__
static inline uint_csr32_t csr_read_frm(void)
{
	return READ_CSRNO(CSR_FRM);
}

static inline void csr_write_frm(uint_csr32_t value)
{
	WRITE_CSRNO(CSR_FRM, value);
}

static inline uint_csr32_t csr_rw_frm(uint_csr32_t value)
{
	return RW_CSRNO(CSR_FRM, value);
}

static inline uint_csr32_t csr_set_frm(uint_csr32_t setmask)
{
	return SET_CSRNO(CSR_FRM, setmask);
}

static inline uint_csr32_t csr_clear_frm(uint_csr32_t clrmask)
{
	return CLEAR_CSRNO(CSR_FRM, clrmask);
}
#endif

/*------------------------------------------------------------------
 * register fcsr @ 0x003
 *   (read-write 32-bit CSR mapped register)
 *   "Floating-Point Control and Status Register (frm + fflags)"
 *------------------------------------------------------------------
 */
#define CSR_FCSR 3
  // inexact 
  #define CSR_FCSR_F_NX 0x00000001
  #define CSR_FCSR_F_NX_OFFSET 0
  // underflow 
  #define CSR_FCSR_F_UF 0x00000002
  #define CSR_FCSR_F_UF_OFFSET 1
  // overflow 
  #define CSR_FCSR_F_OF 0x00000004
  #define CSR_FCSR_F_OF_OFFSET 2
  // divide by zero 
  #define CSR_FCSR_F_DZ 0x00000008
  #define CSR_FCSR_F_DZ_OFFSET 3
  // invalid operation 
  #define CSR_FCSR_F_NV 0x00000010
  #define CSR_FCSR_F_NV_OFFSET 4
  // Rounding Mode 
  #define CSR_FCSR_F_FRM 0x000000e0
  #define CSR_FCSR_F_FRM_OFFSET 5

    // Round to Nearest, ties to Even
    #define CSR_FCSR_F_FRM_E_RNE 0x0

    // Round to Zero
    #define CSR_FCSR_F_FRM_E_RTZ 0x1

    // Round Down (towards -infinite)
    #define CSR_FCSR_F_FRM_E_RD 0x2

    // Round Up (towards +infinite)
    #define CSR_FCSR_F_FRM_E_RUP 0x3

    // Round to Nearest, ties to Max Magnitude
    #define CSR_FCSR_F_FRM_E_RMM 0x4

#ifndef __ASSEMBLER__
static inline uint_csr32_t csr_read_fcsr(void)
{
	return READ_CSRNO(CSR_FCSR);
}

static inline void csr_write_fcsr(uint_csr32_t value)
{
	WRITE_CSRNO(CSR_FCSR, value);
}

static inline uint_csr32_t csr_rw_fcsr(uint_csr32_t value)
{
	return RW_CSRNO(CSR_FCSR, value);
}

static inline uint_csr32_t csr_set_fcsr(uint_csr32_t setmask)
{
	return SET_CSRNO(CSR_FCSR, setmask);
}

static inline uint_csr32_t csr_clear_fcsr(uint_csr32_t clrmask)
{
	return CLEAR_CSRNO(CSR_FCSR, clrmask);
}
#endif

/*------------------------------------------------------------------
 * register cycle @ 0xc00
 *   (read-only 32-bit CSR mapped register)
 *   "Cycle counter for RDCYCLE instruction"
 *------------------------------------------------------------------
 */
#define CSR_CYCLE 3072

#ifndef __ASSEMBLER__
static inline uint_csr32_t csr_read_cycle(void)
{
	return READ_CSRNO(CSR_CYCLE);
}
#endif

/*------------------------------------------------------------------
 * register cycleh @ 0xc80
 *   (read-only 32-bit CSR mapped register)
 *   "Upper 32 bits of cycle"
 *------------------------------------------------------------------
 */
#define CSR_CYCLEH 3200

#ifndef __ASSEMBLER__
static inline uint_csr32_t csr_read_cycleh(void)
{
	return READ_CSRNO(CSR_CYCLEH);
}
#endif

/*------------------------------------------------------------------
 * register time @ 0xc01
 *   (read-only 32-bit CSR mapped register)
 *   "Timer for RDTIME instruction"
 *------------------------------------------------------------------
 */
#define CSR_TIME 3073

#ifndef __ASSEMBLER__
static inline uint_csr32_t csr_read_time(void)
{
	return READ_CSRNO(CSR_TIME);
}
#endif

/*------------------------------------------------------------------
 * register timeh @ 0xc81
 *   (read-only 32-bit CSR mapped register)
 *   "Upper 32 bits of time"
 *------------------------------------------------------------------
 */
#define CSR_TIMEH 3201

#ifndef __ASSEMBLER__
static inline uint_csr32_t csr_read_timeh(void)
{
	return READ_CSRNO(CSR_TIMEH);
}
#endif

/*------------------------------------------------------------------
 * register instret @ 0xc02
 *   (read-only 32-bit CSR mapped register)
 *   "Instructions-retired counter for RDINSTRET instruction"
 *------------------------------------------------------------------
 */
#define CSR_INSTRET 3074

#ifndef __ASSEMBLER__
static inline uint_csr32_t csr_read_instret(void)
{
	return READ_CSRNO(CSR_INSTRET);
}
#endif

/*------------------------------------------------------------------
 * register instreth @ 0xc82
 *   (read-only 32-bit CSR mapped register)
 *   "Upper 32 bits of instret"
 *------------------------------------------------------------------
 */
#define CSR_INSTRETH 3202

#ifndef __ASSEMBLER__
static inline uint_csr32_t csr_read_instreth(void)
{
	return READ_CSRNO(CSR_INSTRETH);
}
#endif

/*------------------------------------------------------------------
 * register sstatus @ 0x100
 *   (read-write 32-bit CSR mapped register)
 *   "Supervisor status register"
 *------------------------------------------------------------------
 */
#define CSR_SSTATUS 256

#ifndef __ASSEMBLER__
static inline uint_csr32_t csr_read_sstatus(void)
{
	return READ_CSRNO(CSR_SSTATUS);
}

static inline void csr_write_sstatus(uint_csr32_t value)
{
	WRITE_CSRNO(CSR_SSTATUS, value);
}

static inline uint_csr32_t csr_rw_sstatus(uint_csr32_t value)
{
	return RW_CSRNO(CSR_SSTATUS, value);
}

static inline uint_csr32_t csr_set_sstatus(uint_csr32_t setmask)
{
	return SET_CSRNO(CSR_SSTATUS, setmask);
}

static inline uint_csr32_t csr_clear_sstatus(uint_csr32_t clrmask)
{
	return CLEAR_CSRNO(CSR_SSTATUS, clrmask);
}
#endif

/*------------------------------------------------------------------
 * register sie @ 0x104
 *   (read-write 32-bit CSR mapped register)
 *   "Supervisor interrupt-enable register"
 *------------------------------------------------------------------
 */
#define CSR_SIE 260

#ifndef __ASSEMBLER__
static inline uint_csr32_t csr_read_sie(void)
{
	return READ_CSRNO(CSR_SIE);
}

static inline void csr_write_sie(uint_csr32_t value)
{
	WRITE_CSRNO(CSR_SIE, value);
}

static inline uint_csr32_t csr_rw_sie(uint_csr32_t value)
{
	return RW_CSRNO(CSR_SIE, value);
}

static inline uint_csr32_t csr_set_sie(uint_csr32_t setmask)
{
	return SET_CSRNO(CSR_SIE, setmask);
}

static inline uint_csr32_t csr_clear_sie(uint_csr32_t clrmask)
{
	return CLEAR_CSRNO(CSR_SIE, clrmask);
}
#endif

/*------------------------------------------------------------------
 * register stvec @ 0x105
 *   (read-write 32-bit CSR mapped register)
 *   "Supervisor trap handler base address"
 *------------------------------------------------------------------
 */
#define CSR_STVEC 261

#ifndef __ASSEMBLER__
static inline uint_csr32_t csr_read_stvec(void)
{
	return READ_CSRNO(CSR_STVEC);
}

static inline void csr_write_stvec(uint_csr32_t value)
{
	WRITE_CSRNO(CSR_STVEC, value);
}

static inline uint_csr32_t csr_rw_stvec(uint_csr32_t value)
{
	return RW_CSRNO(CSR_STVEC, value);
}

static inline uint_csr32_t csr_set_stvec(uint_csr32_t setmask)
{
	return SET_CSRNO(CSR_STVEC, setmask);
}

static inline uint_csr32_t csr_clear_stvec(uint_csr32_t clrmask)
{
	return CLEAR_CSRNO(CSR_STVEC, clrmask);
}
#endif

/*------------------------------------------------------------------
 * register scounteren @ 0x106
 *   (read-write 32-bit CSR mapped register)
 *   "Supervisor counter enable"
 *------------------------------------------------------------------
 */
#define CSR_SCOUNTEREN 262

#ifndef __ASSEMBLER__
static inline uint_csr32_t csr_read_scounteren(void)
{
	return READ_CSRNO(CSR_SCOUNTEREN);
}

static inline void csr_write_scounteren(uint_csr32_t value)
{
	WRITE_CSRNO(CSR_SCOUNTEREN, value);
}

static inline uint_csr32_t csr_rw_scounteren(uint_csr32_t value)
{
	return RW_CSRNO(CSR_SCOUNTEREN, value);
}

static inline uint_csr32_t csr_set_scounteren(uint_csr32_t setmask)
{
	return SET_CSRNO(CSR_SCOUNTEREN, setmask);
}

static inline uint_csr32_t csr_clear_scounteren(uint_csr32_t clrmask)
{
	return CLEAR_CSRNO(CSR_SCOUNTEREN, clrmask);
}
#endif

/*------------------------------------------------------------------
 * register sscratch @ 0x140
 *   (read-write 32-bit CSR mapped register)
 *   "Scratch register for supervisor trap handlers"
 *------------------------------------------------------------------
 */
#define CSR_SSCRATCH 320

#ifndef __ASSEMBLER__
static inline uint_csr32_t csr_read_sscratch(void)
{
	return READ_CSRNO(CSR_SSCRATCH);
}

static inline void csr_write_sscratch(uint_csr32_t value)
{
	WRITE_CSRNO(CSR_SSCRATCH, value);
}

static inline uint_csr32_t csr_rw_sscratch(uint_csr32_t value)
{
	return RW_CSRNO(CSR_SSCRATCH, value);
}

static inline uint_csr32_t csr_set_sscratch(uint_csr32_t setmask)
{
	return SET_CSRNO(CSR_SSCRATCH, setmask);
}

static inline uint_csr32_t csr_clear_sscratch(uint_csr32_t clrmask)
{
	return CLEAR_CSRNO(CSR_SSCRATCH, clrmask);
}
#endif

/*------------------------------------------------------------------
 * register sepc @ 0x141
 *   (read-write 32-bit CSR mapped register)
 *   "Supervisor exception program counter"
 *------------------------------------------------------------------
 */
#define CSR_SEPC 321

#ifndef __ASSEMBLER__
static inline uint_csr32_t csr_read_sepc(void)
{
	return READ_CSRNO(CSR_SEPC);
}

static inline void csr_write_sepc(uint_csr32_t value)
{
	WRITE_CSRNO(CSR_SEPC, value);
}

static inline uint_csr32_t csr_rw_sepc(uint_csr32_t value)
{
	return RW_CSRNO(CSR_SEPC, value);
}

static inline uint_csr32_t csr_set_sepc(uint_csr32_t setmask)
{
	return SET_CSRNO(CSR_SEPC, setmask);
}

static inline uint_csr32_t csr_clear_sepc(uint_csr32_t clrmask)
{
	return CLEAR_CSRNO(CSR_SEPC, clrmask);
}
#endif

/*------------------------------------------------------------------
 * register scause @ 0x142
 *   (read-write 32-bit CSR mapped register)
 *   "Supervisor trap cause"
 *------------------------------------------------------------------
 */
#define CSR_SCAUSE 322

#ifndef __ASSEMBLER__
static inline uint_csr32_t csr_read_scause(void)
{
	return READ_CSRNO(CSR_SCAUSE);
}

static inline void csr_write_scause(uint_csr32_t value)
{
	WRITE_CSRNO(CSR_SCAUSE, value);
}

static inline uint_csr32_t csr_rw_scause(uint_csr32_t value)
{
	return RW_CSRNO(CSR_SCAUSE, value);
}

static inline uint_csr32_t csr_set_scause(uint_csr32_t setmask)
{
	return SET_CSRNO(CSR_SCAUSE, setmask);
}

static inline uint_csr32_t csr_clear_scause(uint_csr32_t clrmask)
{
	return CLEAR_CSRNO(CSR_SCAUSE, clrmask);
}
#endif

/*------------------------------------------------------------------
 * register stval @ 0x143
 *   (read-write 32-bit CSR mapped register)
 *   "Supervisor bad address or instruction"
 *------------------------------------------------------------------
 */
#define CSR_STVAL 323

#ifndef __ASSEMBLER__
static inline uint_csr32_t csr_read_stval(void)
{
	return READ_CSRNO(CSR_STVAL);
}

static inline void csr_write_stval(uint_csr32_t value)
{
	WRITE_CSRNO(CSR_STVAL, value);
}

static inline uint_csr32_t csr_rw_stval(uint_csr32_t value)
{
	return RW_CSRNO(CSR_STVAL, value);
}

static inline uint_csr32_t csr_set_stval(uint_csr32_t setmask)
{
	return SET_CSRNO(CSR_STVAL, setmask);
}

static inline uint_csr32_t csr_clear_stval(uint_csr32_t clrmask)
{
	return CLEAR_CSRNO(CSR_STVAL, clrmask);
}
#endif

/*------------------------------------------------------------------
 * register sip @ 0x144
 *   (read-write 32-bit CSR mapped register)
 *   "Supervisor interrupt pending"
 *------------------------------------------------------------------
 */
#define CSR_SIP 324

#ifndef __ASSEMBLER__
static inline uint_csr32_t csr_read_sip(void)
{
	return READ_CSRNO(CSR_SIP);
}

static inline void csr_write_sip(uint_csr32_t value)
{
	WRITE_CSRNO(CSR_SIP, value);
}

static inline uint_csr32_t csr_rw_sip(uint_csr32_t value)
{
	return RW_CSRNO(CSR_SIP, value);
}

static inline uint_csr32_t csr_set_sip(uint_csr32_t setmask)
{
	return SET_CSRNO(CSR_SIP, setmask);
}

static inline uint_csr32_t csr_clear_sip(uint_csr32_t clrmask)
{
	return CLEAR_CSRNO(CSR_SIP, clrmask);
}
#endif

/*------------------------------------------------------------------
 * register satp @ 0x180
 *   (read-write 32-bit CSR mapped register)
 *   "Supervisor address translation and protection"
 *------------------------------------------------------------------
 */
#define CSR_SATP 384

#ifndef __ASSEMBLER__
static inline uint_csr32_t csr_read_satp(void)
{
	return READ_CSRNO(CSR_SATP);
}

static inline void csr_write_satp(uint_csr32_t value)
{
	WRITE_CSRNO(CSR_SATP, value);
}

static inline uint_csr32_t csr_rw_satp(uint_csr32_t value)
{
	return RW_CSRNO(CSR_SATP, value);
}

static inline uint_csr32_t csr_set_satp(uint_csr32_t setmask)
{
	return SET_CSRNO(CSR_SATP, setmask);
}

static inline uint_csr32_t csr_clear_satp(uint_csr32_t clrmask)
{
	return CLEAR_CSRNO(CSR_SATP, clrmask);
}
#endif

/*------------------------------------------------------------------
 * register mvendorid @ 0xf11
 *   (read-only 32-bit CSR mapped register)
 *   "Vendor ID"
 *------------------------------------------------------------------
 */
#define CSR_MVENDORID 3857

#ifndef __ASSEMBLER__
static inline uint_csr32_t csr_read_mvendorid(void)
{
	return READ_CSRNO(CSR_MVENDORID);
}
#endif

/*------------------------------------------------------------------
 * register marchid @ 0xf12
 *   (read-only 32-bit CSR mapped register)
 *   "Architecture ID"
 *------------------------------------------------------------------
 */
#define CSR_MARCHID 3858

#ifndef __ASSEMBLER__
static inline uint_csr32_t csr_read_marchid(void)
{
	return READ_CSRNO(CSR_MARCHID);
}
#endif

/*------------------------------------------------------------------
 * register mimpid @ 0xf13
 *   (read-only 32-bit CSR mapped register)
 *   "Implementation ID"
 *------------------------------------------------------------------
 */
#define CSR_MIMPID 3859

#ifndef __ASSEMBLER__
static inline uint_csr32_t csr_read_mimpid(void)
{
	return READ_CSRNO(CSR_MIMPID);
}
#endif

/*------------------------------------------------------------------
 * register mhartid @ 0xf14
 *   (read-only 32-bit CSR mapped register)
 *   "Hardware thread ID"
 *------------------------------------------------------------------
 */
#define CSR_MHARTID 3860

#ifndef __ASSEMBLER__
static inline uint_csr32_t csr_read_mhartid(void)
{
	return READ_CSRNO(CSR_MHARTID);
}
#endif

/*------------------------------------------------------------------
 * register mstatus @ 0x300
 *   (read-write 32-bit CSR mapped register)
 *   "machine status register"
 *------------------------------------------------------------------
 */
#define CSR_MSTATUS 768
  // reserved 
  #define CSR_MSTATUS_F_WPRI0 0x00000001
  #define CSR_MSTATUS_F_WPRI0_OFFSET 0
  // supervisor mode global interrupt enable bit 
  #define CSR_MSTATUS_F_SIE 0x00000002
  #define CSR_MSTATUS_F_SIE_OFFSET 1
  // reserved 
  #define CSR_MSTATUS_F_WPRI1 0x00000004
  #define CSR_MSTATUS_F_WPRI1_OFFSET 2
  // machine mode global interrupt enable bit 
  #define CSR_MSTATUS_F_MIE 0x00000008
  #define CSR_MSTATUS_F_MIE_OFFSET 3
  // reserved 
  #define CSR_MSTATUS_F_WPRI2 0x00000010
  #define CSR_MSTATUS_F_WPRI2_OFFSET 4
  // previous supervisor interrupt enable bit 
  #define CSR_MSTATUS_F_SPIE 0x00000020
  #define CSR_MSTATUS_F_SPIE_OFFSET 5
  // non-instruction user mode memory access endianness 
  #define CSR_MSTATUS_F_UBE 0x00000040
  #define CSR_MSTATUS_F_UBE_OFFSET 6

    // little endian
    #define CSR_MSTATUS_F_UBE_E_LE 0x0

    // big endian
    #define CSR_MSTATUS_F_UBE_E_BE 0x1
  // previous machine interrupt enable bit 
  #define CSR_MSTATUS_F_MPIE 0x00000080
  #define CSR_MSTATUS_F_MPIE_OFFSET 7
  // supervisor previous privilege mode 
  #define CSR_MSTATUS_F_SPP 0x00000100
  #define CSR_MSTATUS_F_SPP_OFFSET 8

    // user/application mode
    #define CSR_MSTATUS_F_SPP_E_USER 0x0

    // supervisor mode
    #define CSR_MSTATUS_F_SPP_E_SUPERVISOR 0x1
  // vector extension state 
  #define CSR_MSTATUS_F_VS 0x00000600
  #define CSR_MSTATUS_F_VS_OFFSET 9

    // All off
    #define CSR_MSTATUS_F_VS_E_OFF 0x0

    // None dirty or clean, some on
    #define CSR_MSTATUS_F_VS_E_INITIAL 0x1

    // None dirty, some clean
    #define CSR_MSTATUS_F_VS_E_CLEAN 0x2

    // Some dirty
    #define CSR_MSTATUS_F_VS_E_DIRTY 0x3
  // machine previous privilege 
  #define CSR_MSTATUS_F_MPP 0x00001800
  #define CSR_MSTATUS_F_MPP_OFFSET 11

    // user/application mode
    #define CSR_MSTATUS_F_MPP_E_USER 0x0

    // supervisor mode
    #define CSR_MSTATUS_F_MPP_E_SUPERVISOR 0x1

    // hypervisor mode clean
    #define CSR_MSTATUS_F_MPP_E_HYPERVISOR 0x2

    // machine mode
    #define CSR_MSTATUS_F_MPP_E_MACHINE 0x3
  // floating-point unit state 
  #define CSR_MSTATUS_F_FS 0x00006000
  #define CSR_MSTATUS_F_FS_OFFSET 13

    // All off
    #define CSR_MSTATUS_F_FS_E_OFF 0x0

    // None dirty or clean, some on
    #define CSR_MSTATUS_F_FS_E_INITIAL 0x1

    // None dirty, some clean
    #define CSR_MSTATUS_F_FS_E_CLEAN 0x2

    // Some dirty
    #define CSR_MSTATUS_F_FS_E_DIRTY 0x3
  // custom user mode unit(s) state 
  #define CSR_MSTATUS_F_XS 0x00018000
  #define CSR_MSTATUS_F_XS_OFFSET 15

    // All off
    #define CSR_MSTATUS_F_XS_E_OFF 0x0

    // None dirty or clean, some on
    #define CSR_MSTATUS_F_XS_E_INITIAL 0x1

    // None dirty, some clean
    #define CSR_MSTATUS_F_XS_E_CLEAN 0x2

    // Some dirty
    #define CSR_MSTATUS_F_XS_E_DIRTY 0x3
  // modify privilege 
  #define CSR_MSTATUS_F_MPRV 0x00020000
  #define CSR_MSTATUS_F_MPRV_OFFSET 17
  // permit Supervisor User Memory access 
  #define CSR_MSTATUS_F_SUM 0x00040000
  #define CSR_MSTATUS_F_SUM_OFFSET 18
  // Make eXecutable Readable 
  #define CSR_MSTATUS_F_MXR 0x00080000
  #define CSR_MSTATUS_F_MXR_OFFSET 19
  // Trap Virtual Memory 
  #define CSR_MSTATUS_F_TVR 0x00100000
  #define CSR_MSTATUS_F_TVR_OFFSET 20
  // Timeout Wait 
  #define CSR_MSTATUS_F_TW 0x00200000
  #define CSR_MSTATUS_F_TW_OFFSET 21
  // Trap SRET 
  #define CSR_MSTATUS_F_TSR 0x00400000
  #define CSR_MSTATUS_F_TSR_OFFSET 22
  // reserved 
  #define CSR_MSTATUS_F_WPRI3 0x7f800000
  #define CSR_MSTATUS_F_WPRI3_OFFSET 23
  // summarized dirty (FS | VS | XS) 
  #define CSR_MSTATUS_F_SD 0x80000000
  #define CSR_MSTATUS_F_SD_OFFSET 31

#ifndef __ASSEMBLER__
static inline uint_csr32_t csr_read_mstatus(void)
{
	return READ_CSRNO(CSR_MSTATUS);
}

static inline void csr_write_mstatus(uint_csr32_t value)
{
	WRITE_CSRNO(CSR_MSTATUS, value);
}

static inline uint_csr32_t csr_rw_mstatus(uint_csr32_t value)
{
	return RW_CSRNO(CSR_MSTATUS, value);
}

static inline uint_csr32_t csr_set_mstatus(uint_csr32_t setmask)
{
	return SET_CSRNO(CSR_MSTATUS, setmask);
}

static inline uint_csr32_t csr_clear_mstatus(uint_csr32_t clrmask)
{
	return CLEAR_CSRNO(CSR_MSTATUS, clrmask);
}
#endif

/*------------------------------------------------------------------
 * register misa @ 0x301
 *   (read-write 32-bit CSR mapped register)
 *   "ISA and extensions"
 *------------------------------------------------------------------
 */
#define CSR_MISA 769
  // Extension A (atomic) implemented 
  #define CSR_MISA_F_A 0x00000001
  #define CSR_MISA_F_A_OFFSET 0
  // Extension B implemented. 
  #define CSR_MISA_F_B 0x00000002
  #define CSR_MISA_F_B_OFFSET 1
  // Extension C (compressed) implemented. 
  #define CSR_MISA_F_C 0x00000004
  #define CSR_MISA_F_C_OFFSET 2
  // Extension D (double-precision) implemented. 
  #define CSR_MISA_F_D 0x00000008
  #define CSR_MISA_F_D_OFFSET 3
  // RV32E base ISA 
  #define CSR_MISA_F_RV32E 0x00000010
  #define CSR_MISA_F_RV32E_OFFSET 4
  // Extension F (single-precision) implemented. 
  #define CSR_MISA_F_F 0x00000020
  #define CSR_MISA_F_F_OFFSET 5
  // Extension G implemented. 
  #define CSR_MISA_F_G 0x00000040
  #define CSR_MISA_F_G_OFFSET 6
  // Extension H (hypervisor) implemented. 
  #define CSR_MISA_F_H 0x00000080
  #define CSR_MISA_F_H_OFFSET 7
  // RV32I/64I/128I base ISA 
  #define CSR_MISA_F_RV32I_64I_128I 0x00000100
  #define CSR_MISA_F_RV32I_64I_128I_OFFSET 8
  // Extension J implemented. 
  #define CSR_MISA_F_J 0x00000200
  #define CSR_MISA_F_J_OFFSET 9
  // Extension K implemented. 
  #define CSR_MISA_F_K 0x00000400
  #define CSR_MISA_F_K_OFFSET 10
  // Extension L implemented. 
  #define CSR_MISA_F_L 0x00000800
  #define CSR_MISA_F_L_OFFSET 11
  // Extension M (integer multiply/divide) implemented. 
  #define CSR_MISA_F_M 0x00001000
  #define CSR_MISA_F_M_OFFSET 12
  // Extension N (user level interrupts) implemented. 
  #define CSR_MISA_F_N 0x00002000
  #define CSR_MISA_F_N_OFFSET 13
  // Extension O implemented. 
  #define CSR_MISA_F_O 0x00004000
  #define CSR_MISA_F_O_OFFSET 14
  // Extension P (packed SIMD) implemented. 
  #define CSR_MISA_F_P 0x00008000
  #define CSR_MISA_F_P_OFFSET 15
  // Extension Q (quad-precision) implemented. 
  #define CSR_MISA_F_Q 0x00010000
  #define CSR_MISA_F_Q_OFFSET 16
  // Extension R implemented. 
  #define CSR_MISA_F_R 0x00020000
  #define CSR_MISA_F_R_OFFSET 17
  // Extension S (supervisor mode) implemented. 
  #define CSR_MISA_F_S 0x00040000
  #define CSR_MISA_F_S_OFFSET 18
  // Extension T implemented. 
  #define CSR_MISA_F_T 0x00080000
  #define CSR_MISA_F_T_OFFSET 19
  // Extension U (user mode) implemented. 
  #define CSR_MISA_F_U 0x00100000
  #define CSR_MISA_F_U_OFFSET 20
  // Extension V (vector) implemented. 
  #define CSR_MISA_F_V 0x00200000
  #define CSR_MISA_F_V_OFFSET 21
  // Extension W implemented. 
  #define CSR_MISA_F_W 0x00400000
  #define CSR_MISA_F_W_OFFSET 22
  // Extension X (non-standard extension(s)) implemented. 
  #define CSR_MISA_F_X 0x00800000
  #define CSR_MISA_F_X_OFFSET 23
  // Extension Y implemented. 
  #define CSR_MISA_F_Y 0x01000000
  #define CSR_MISA_F_Y_OFFSET 24
  // Extension Z implemented. 
  #define CSR_MISA_F_Z 0x02000000
  #define CSR_MISA_F_Z_OFFSET 25
  // Machine XLEN 
  #define CSR_MISA_F_MXL 0xc0000000
  #define CSR_MISA_F_MXL_OFFSET 30

    // 32 bit
    #define CSR_MISA_F_MXL_E_XLEN32 0x1

    // 64 bit
    #define CSR_MISA_F_MXL_E_XLEN64 0x2

    // 128 bit
    #define CSR_MISA_F_MXL_E_XLEN128 0x3

#ifndef __ASSEMBLER__
static inline uint_csr32_t csr_read_misa(void)
{
	return READ_CSRNO(CSR_MISA);
}

static inline void csr_write_misa(uint_csr32_t value)
{
	WRITE_CSRNO(CSR_MISA, value);
}

static inline uint_csr32_t csr_rw_misa(uint_csr32_t value)
{
	return RW_CSRNO(CSR_MISA, value);
}

static inline uint_csr32_t csr_set_misa(uint_csr32_t setmask)
{
	return SET_CSRNO(CSR_MISA, setmask);
}

static inline uint_csr32_t csr_clear_misa(uint_csr32_t clrmask)
{
	return CLEAR_CSRNO(CSR_MISA, clrmask);
}
#endif

/*------------------------------------------------------------------
 * register medeleg @ 0x302
 *   (read-write 32-bit CSR mapped register)
 *   "Machine exception delegation register"
 *------------------------------------------------------------------
 */
#define CSR_MEDELEG 770
  // instruction address misaligned delegation 
  #define CSR_MEDELEG_F_IAM 0x00000001
  #define CSR_MEDELEG_F_IAM_OFFSET 0
  // instruction access fault delegation 
  #define CSR_MEDELEG_F_IAF 0x00000002
  #define CSR_MEDELEG_F_IAF_OFFSET 1
  // illegal instruction delegation 
  #define CSR_MEDELEG_F_II 0x00000004
  #define CSR_MEDELEG_F_II_OFFSET 2
  // breakpoint delegation 
  #define CSR_MEDELEG_F_BPKT 0x00000008
  #define CSR_MEDELEG_F_BPKT_OFFSET 3
  // load address misaligned delegation 
  #define CSR_MEDELEG_F_LAM 0x00000010
  #define CSR_MEDELEG_F_LAM_OFFSET 4
  // load access fault delegation 
  #define CSR_MEDELEG_F_LAF 0x00000020
  #define CSR_MEDELEG_F_LAF_OFFSET 5
  // store/AMO address misaligned delegation 
  #define CSR_MEDELEG_F_SAM 0x00000040
  #define CSR_MEDELEG_F_SAM_OFFSET 6
  // store/AMO access fault delegation 
  #define CSR_MEDELEG_F_SAF 0x00000080
  #define CSR_MEDELEG_F_SAF_OFFSET 7
  // environment call from U-mode delegation 
  #define CSR_MEDELEG_F_ECU 0x00000100
  #define CSR_MEDELEG_F_ECU_OFFSET 8
  // environment call from S-mode delegation 
  #define CSR_MEDELEG_F_ECS 0x00000200
  #define CSR_MEDELEG_F_ECS_OFFSET 9
  // environment call from M-mode delegation 
  #define CSR_MEDELEG_F_ECM 0x00000800
  #define CSR_MEDELEG_F_ECM_OFFSET 11
  // instruction page fault delegation 
  #define CSR_MEDELEG_F_IPF 0x00001000
  #define CSR_MEDELEG_F_IPF_OFFSET 12
  // load page fault delegation 
  #define CSR_MEDELEG_F_LPF 0x00002000
  #define CSR_MEDELEG_F_LPF_OFFSET 13
  // store/AMO page fault delegation 
  #define CSR_MEDELEG_F_SPF 0x00008000
  #define CSR_MEDELEG_F_SPF_OFFSET 15

#ifndef __ASSEMBLER__
static inline uint_csr32_t csr_read_medeleg(void)
{
	return READ_CSRNO(CSR_MEDELEG);
}

static inline void csr_write_medeleg(uint_csr32_t value)
{
	WRITE_CSRNO(CSR_MEDELEG, value);
}

static inline uint_csr32_t csr_rw_medeleg(uint_csr32_t value)
{
	return RW_CSRNO(CSR_MEDELEG, value);
}

static inline uint_csr32_t csr_set_medeleg(uint_csr32_t setmask)
{
	return SET_CSRNO(CSR_MEDELEG, setmask);
}

static inline uint_csr32_t csr_clear_medeleg(uint_csr32_t clrmask)
{
	return CLEAR_CSRNO(CSR_MEDELEG, clrmask);
}
#endif

/*------------------------------------------------------------------
 * register mideleg @ 0x303
 *   (read-write 32-bit CSR mapped register)
 *   "Machine interrupt delegation register"
 *------------------------------------------------------------------
 */
#define CSR_MIDELEG 771
  // supervisor level software interrupts delegation 
  #define CSR_MIDELEG_F_SSID 0x00000002
  #define CSR_MIDELEG_F_SSID_OFFSET 1
  // machine level software interrupts delegation 
  #define CSR_MIDELEG_F_MSID 0x00000008
  #define CSR_MIDELEG_F_MSID_OFFSET 3
  // supervisor level timer interrupts delegation 
  #define CSR_MIDELEG_F_STID 0x00000020
  #define CSR_MIDELEG_F_STID_OFFSET 5
  // machine level timer interrupts delegation 
  #define CSR_MIDELEG_F_MTID 0x00000080
  #define CSR_MIDELEG_F_MTID_OFFSET 7
  // supervisor level external interrupt delegation 
  #define CSR_MIDELEG_F_SEID 0x00000200
  #define CSR_MIDELEG_F_SEID_OFFSET 9
  // machine level external interrupt delegation 
  #define CSR_MIDELEG_F_MEID 0x00000800
  #define CSR_MIDELEG_F_MEID_OFFSET 11

#ifndef __ASSEMBLER__
static inline uint_csr32_t csr_read_mideleg(void)
{
	return READ_CSRNO(CSR_MIDELEG);
}

static inline void csr_write_mideleg(uint_csr32_t value)
{
	WRITE_CSRNO(CSR_MIDELEG, value);
}

static inline uint_csr32_t csr_rw_mideleg(uint_csr32_t value)
{
	return RW_CSRNO(CSR_MIDELEG, value);
}

static inline uint_csr32_t csr_set_mideleg(uint_csr32_t setmask)
{
	return SET_CSRNO(CSR_MIDELEG, setmask);
}

static inline uint_csr32_t csr_clear_mideleg(uint_csr32_t clrmask)
{
	return CLEAR_CSRNO(CSR_MIDELEG, clrmask);
}
#endif

/*------------------------------------------------------------------
 * register mie @ 0x304
 *   (read-write 32-bit CSR mapped register)
 *   "Machine interrupt-enable register"
 *------------------------------------------------------------------
 */
#define CSR_MIE 772
  // supervisor level software interrupts enable 
  #define CSR_MIE_F_SSIE 0x00000002
  #define CSR_MIE_F_SSIE_OFFSET 1
  // machine level software interrupts enable 
  #define CSR_MIE_F_MSIE 0x00000008
  #define CSR_MIE_F_MSIE_OFFSET 3
  // supervisor level timer interrupts enable 
  #define CSR_MIE_F_STIE 0x00000020
  #define CSR_MIE_F_STIE_OFFSET 5
  // machine level timer interrupts enable 
  #define CSR_MIE_F_MTIE 0x00000080
  #define CSR_MIE_F_MTIE_OFFSET 7
  // supervisor level external interrupt enable 
  #define CSR_MIE_F_SEIE 0x00000200
  #define CSR_MIE_F_SEIE_OFFSET 9
  // machine level external interrupt enable 
  #define CSR_MIE_F_MEIE 0x00000800
  #define CSR_MIE_F_MEIE_OFFSET 11

#ifndef __ASSEMBLER__
static inline uint_csr32_t csr_read_mie(void)
{
	return READ_CSRNO(CSR_MIE);
}

static inline void csr_write_mie(uint_csr32_t value)
{
	WRITE_CSRNO(CSR_MIE, value);
}

static inline uint_csr32_t csr_rw_mie(uint_csr32_t value)
{
	return RW_CSRNO(CSR_MIE, value);
}

static inline uint_csr32_t csr_set_mie(uint_csr32_t setmask)
{
	return SET_CSRNO(CSR_MIE, setmask);
}

static inline uint_csr32_t csr_clear_mie(uint_csr32_t clrmask)
{
	return CLEAR_CSRNO(CSR_MIE, clrmask);
}
#endif

/*------------------------------------------------------------------
 * register mtvec @ 0x305
 *   (read-write 32-bit CSR mapped register)
 *   "Machine trap handler base address"
 *------------------------------------------------------------------
 */
#define CSR_MTVEC 773
  // machine trap mode 
  #define CSR_MTVEC_F_MODE 0x00000003
  #define CSR_MTVEC_F_MODE_OFFSET 0

    // All exceptions set pc to BASE
    #define CSR_MTVEC_F_MODE_E_DIRECT 0x0

    // Asynchronous interrupts set pc to BASE + 4*cause
    #define CSR_MTVEC_F_MODE_E_VECTORED 0x1
  // machine trap base address (top 30 bits, 2 low bits are always 0) 
  #define CSR_MTVEC_F_BASE 0xfffffffc
  #define CSR_MTVEC_F_BASE_OFFSET 2

#ifndef __ASSEMBLER__
static inline uint_csr32_t csr_read_mtvec(void)
{
	return READ_CSRNO(CSR_MTVEC);
}

static inline void csr_write_mtvec(uint_csr32_t value)
{
	WRITE_CSRNO(CSR_MTVEC, value);
}

static inline uint_csr32_t csr_rw_mtvec(uint_csr32_t value)
{
	return RW_CSRNO(CSR_MTVEC, value);
}

static inline uint_csr32_t csr_set_mtvec(uint_csr32_t setmask)
{
	return SET_CSRNO(CSR_MTVEC, setmask);
}

static inline uint_csr32_t csr_clear_mtvec(uint_csr32_t clrmask)
{
	return CLEAR_CSRNO(CSR_MTVEC, clrmask);
}
#endif

/*------------------------------------------------------------------
 * register mcounteren @ 0x306
 *   (read-write 32-bit CSR mapped register)
 *   "Machine counter enable"
 *------------------------------------------------------------------
 */
#define CSR_MCOUNTEREN 774
  // allow cycle access in S and U modes 
  #define CSR_MCOUNTEREN_F_CY 0x00000001
  #define CSR_MCOUNTEREN_F_CY_OFFSET 0
  // allow time access in S and U modes 
  #define CSR_MCOUNTEREN_F_TM 0x00000002
  #define CSR_MCOUNTEREN_F_TM_OFFSET 1
  // allow instret access in S and U modes 
  #define CSR_MCOUNTEREN_F_IR 0x00000004
  #define CSR_MCOUNTEREN_F_IR_OFFSET 2
  // allow hpmcounter3 access in S and U modes 
  #define CSR_MCOUNTEREN_F_HPM3 0x00000008
  #define CSR_MCOUNTEREN_F_HPM3_OFFSET 3
  // allow hpmcounter4 access in S and U modes 
  #define CSR_MCOUNTEREN_F_HPM4 0x00000010
  #define CSR_MCOUNTEREN_F_HPM4_OFFSET 4

#ifndef __ASSEMBLER__
static inline uint_csr32_t csr_read_mcounteren(void)
{
	return READ_CSRNO(CSR_MCOUNTEREN);
}

static inline void csr_write_mcounteren(uint_csr32_t value)
{
	WRITE_CSRNO(CSR_MCOUNTEREN, value);
}

static inline uint_csr32_t csr_rw_mcounteren(uint_csr32_t value)
{
	return RW_CSRNO(CSR_MCOUNTEREN, value);
}

static inline uint_csr32_t csr_set_mcounteren(uint_csr32_t setmask)
{
	return SET_CSRNO(CSR_MCOUNTEREN, setmask);
}

static inline uint_csr32_t csr_clear_mcounteren(uint_csr32_t clrmask)
{
	return CLEAR_CSRNO(CSR_MCOUNTEREN, clrmask);
}
#endif

/*------------------------------------------------------------------
 * register mscratch @ 0x340
 *   (read-write 32-bit CSR mapped register)
 *   "Scratch register for machine trap handlers"
 *------------------------------------------------------------------
 */
#define CSR_MSCRATCH 832

#ifndef __ASSEMBLER__
static inline uint_csr32_t csr_read_mscratch(void)
{
	return READ_CSRNO(CSR_MSCRATCH);
}

static inline void csr_write_mscratch(uint_csr32_t value)
{
	WRITE_CSRNO(CSR_MSCRATCH, value);
}

static inline uint_csr32_t csr_rw_mscratch(uint_csr32_t value)
{
	return RW_CSRNO(CSR_MSCRATCH, value);
}

static inline uint_csr32_t csr_set_mscratch(uint_csr32_t setmask)
{
	return SET_CSRNO(CSR_MSCRATCH, setmask);
}

static inline uint_csr32_t csr_clear_mscratch(uint_csr32_t clrmask)
{
	return CLEAR_CSRNO(CSR_MSCRATCH, clrmask);
}
#endif

/*------------------------------------------------------------------
 * register mepc @ 0x341
 *   (read-write 32-bit CSR mapped register)
 *   "Machine exception program counter"
 *------------------------------------------------------------------
 */
#define CSR_MEPC 833

#ifndef __ASSEMBLER__
static inline uint_csr32_t csr_read_mepc(void)
{
	return READ_CSRNO(CSR_MEPC);
}

static inline void csr_write_mepc(uint_csr32_t value)
{
	WRITE_CSRNO(CSR_MEPC, value);
}

static inline uint_csr32_t csr_rw_mepc(uint_csr32_t value)
{
	return RW_CSRNO(CSR_MEPC, value);
}

static inline uint_csr32_t csr_set_mepc(uint_csr32_t setmask)
{
	return SET_CSRNO(CSR_MEPC, setmask);
}

static inline uint_csr32_t csr_clear_mepc(uint_csr32_t clrmask)
{
	return CLEAR_CSRNO(CSR_MEPC, clrmask);
}
#endif

/*------------------------------------------------------------------
 * register mcause @ 0x342
 *   (read-write 32-bit CSR mapped register)
 *   "Machine trap cause"
 *------------------------------------------------------------------
 */
#define CSR_MCAUSE 834
  // Machine trap cause 
  #define CSR_MCAUSE_F_CAUSE 0xffffffff
  #define CSR_MCAUSE_F_CAUSE_OFFSET 0

    // instruction address misaligned
    #define CSR_MCAUSE_F_CAUSE_E_IAM 0x0

    // instruction access fault
    #define CSR_MCAUSE_F_CAUSE_E_IAF 0x1

    // illegal instruction
    #define CSR_MCAUSE_F_CAUSE_E_II 0x2

    // breakpoint
    #define CSR_MCAUSE_F_CAUSE_E_BKPT 0x3

    // load address misaligned
    #define CSR_MCAUSE_F_CAUSE_E_LAM 0x4

    // load access fault
    #define CSR_MCAUSE_F_CAUSE_E_LAF 0x5

    // store/AMO address misaligned
    #define CSR_MCAUSE_F_CAUSE_E_SAM 0x6

    // store/AMO access fault
    #define CSR_MCAUSE_F_CAUSE_E_SAF 0x7

    // environment call from U-mode
    #define CSR_MCAUSE_F_CAUSE_E_ECU 0x8

    // environment call from S-mode
    #define CSR_MCAUSE_F_CAUSE_E_ECS 0x9

    // environment call from M-mode
    #define CSR_MCAUSE_F_CAUSE_E_ECM 0xb

    // instruction page fault
    #define CSR_MCAUSE_F_CAUSE_E_IPF 0xc

    // load page fault
    #define CSR_MCAUSE_F_CAUSE_E_LPF 0xd

    // store/AMO page fault
    #define CSR_MCAUSE_F_CAUSE_E_SPF 0xf

    // supervisor software interrupt
    #define CSR_MCAUSE_F_CAUSE_E_SSI 0x80000001

    // machine software interrupt
    #define CSR_MCAUSE_F_CAUSE_E_MSI 0x80000003

    // supervisor timer interrupt
    #define CSR_MCAUSE_F_CAUSE_E_STI 0x80000005

    // machine timer interrupt
    #define CSR_MCAUSE_F_CAUSE_E_MTI 0x80000007

    // supervisor external interrupt
    #define CSR_MCAUSE_F_CAUSE_E_SEI 0x80000009

    // machine external interrupt
    #define CSR_MCAUSE_F_CAUSE_E_MEI 0x8000000b

#ifndef __ASSEMBLER__
static inline uint_csr32_t csr_read_mcause(void)
{
	return READ_CSRNO(CSR_MCAUSE);
}

static inline void csr_write_mcause(uint_csr32_t value)
{
	WRITE_CSRNO(CSR_MCAUSE, value);
}

static inline uint_csr32_t csr_rw_mcause(uint_csr32_t value)
{
	return RW_CSRNO(CSR_MCAUSE, value);
}

static inline uint_csr32_t csr_set_mcause(uint_csr32_t setmask)
{
	return SET_CSRNO(CSR_MCAUSE, setmask);
}

static inline uint_csr32_t csr_clear_mcause(uint_csr32_t clrmask)
{
	return CLEAR_CSRNO(CSR_MCAUSE, clrmask);
}
#endif

/*------------------------------------------------------------------
 * register mtval @ 0x343
 *   (read-write 32-bit CSR mapped register)
 *   "Machine bad address or instruction"
 *------------------------------------------------------------------
 */
#define CSR_MTVAL 835

#ifndef __ASSEMBLER__
static inline uint_csr32_t csr_read_mtval(void)
{
	return READ_CSRNO(CSR_MTVAL);
}

static inline void csr_write_mtval(uint_csr32_t value)
{
	WRITE_CSRNO(CSR_MTVAL, value);
}

static inline uint_csr32_t csr_rw_mtval(uint_csr32_t value)
{
	return RW_CSRNO(CSR_MTVAL, value);
}

static inline uint_csr32_t csr_set_mtval(uint_csr32_t setmask)
{
	return SET_CSRNO(CSR_MTVAL, setmask);
}

static inline uint_csr32_t csr_clear_mtval(uint_csr32_t clrmask)
{
	return CLEAR_CSRNO(CSR_MTVAL, clrmask);
}
#endif

/*------------------------------------------------------------------
 * register mip @ 0x344
 *   (read-write 32-bit CSR mapped register)
 *   "Machine interrupt-pending register"
 *------------------------------------------------------------------
 */
#define CSR_MIP 836
  // supervisor level software interrupts pending 
  #define CSR_MIP_F_SSIP 0x00000002
  #define CSR_MIP_F_SSIP_OFFSET 1
  // machine level software interrupts pending 
  #define CSR_MIP_F_MSIP 0x00000008
  #define CSR_MIP_F_MSIP_OFFSET 3
  // supervisor level timer interrupts pending 
  #define CSR_MIP_F_STIP 0x00000020
  #define CSR_MIP_F_STIP_OFFSET 5
  // machine level timer interrupts pending 
  #define CSR_MIP_F_MTIP 0x00000080
  #define CSR_MIP_F_MTIP_OFFSET 7
  // supervisor level external interrupt pending 
  #define CSR_MIP_F_SEIP 0x00000200
  #define CSR_MIP_F_SEIP_OFFSET 9
  // machine level external interrupt pending 
  #define CSR_MIP_F_MEIP 0x00000800
  #define CSR_MIP_F_MEIP_OFFSET 11

#ifndef __ASSEMBLER__
static inline uint_csr32_t csr_read_mip(void)
{
	return READ_CSRNO(CSR_MIP);
}

static inline void csr_write_mip(uint_csr32_t value)
{
	WRITE_CSRNO(CSR_MIP, value);
}

static inline uint_csr32_t csr_rw_mip(uint_csr32_t value)
{
	return RW_CSRNO(CSR_MIP, value);
}

static inline uint_csr32_t csr_set_mip(uint_csr32_t setmask)
{
	return SET_CSRNO(CSR_MIP, setmask);
}

static inline uint_csr32_t csr_clear_mip(uint_csr32_t clrmask)
{
	return CLEAR_CSRNO(CSR_MIP, clrmask);
}
#endif

/*------------------------------------------------------------------
 * register mcycle @ 0xb00
 *   (read-write 32-bit CSR mapped register)
 *   "Machine cycle number"
 *------------------------------------------------------------------
 */
#define CSR_MCYCLE 2816

#ifndef __ASSEMBLER__
static inline uint_csr32_t csr_read_mcycle(void)
{
	return READ_CSRNO(CSR_MCYCLE);
}

static inline void csr_write_mcycle(uint_csr32_t value)
{
	WRITE_CSRNO(CSR_MCYCLE, value);
}

static inline uint_csr32_t csr_rw_mcycle(uint_csr32_t value)
{
	return RW_CSRNO(CSR_MCYCLE, value);
}

static inline uint_csr32_t csr_set_mcycle(uint_csr32_t setmask)
{
	return SET_CSRNO(CSR_MCYCLE, setmask);
}

static inline uint_csr32_t csr_clear_mcycle(uint_csr32_t clrmask)
{
	return CLEAR_CSRNO(CSR_MCYCLE, clrmask);
}
#endif

/*------------------------------------------------------------------
 * register mcycleh @ 0xb80
 *   (read-write 32-bit CSR mapped register)
 *   "Upper 32-bits of machine cycle number"
 *------------------------------------------------------------------
 */
#define CSR_MCYCLEH 2944

#ifndef __ASSEMBLER__
static inline uint_csr32_t csr_read_mcycleh(void)
{
	return READ_CSRNO(CSR_MCYCLEH);
}

static inline void csr_write_mcycleh(uint_csr32_t value)
{
	WRITE_CSRNO(CSR_MCYCLEH, value);
}

static inline uint_csr32_t csr_rw_mcycleh(uint_csr32_t value)
{
	return RW_CSRNO(CSR_MCYCLEH, value);
}

static inline uint_csr32_t csr_set_mcycleh(uint_csr32_t setmask)
{
	return SET_CSRNO(CSR_MCYCLEH, setmask);
}

static inline uint_csr32_t csr_clear_mcycleh(uint_csr32_t clrmask)
{
	return CLEAR_CSRNO(CSR_MCYCLEH, clrmask);
}
#endif

/*------------------------------------------------------------------
 * register minstret @ 0xb02
 *   (read-write 32-bit CSR mapped register)
 *   "Machine instructions-retired counter"
 *------------------------------------------------------------------
 */
#define CSR_MINSTRET 2818

#ifndef __ASSEMBLER__
static inline uint_csr32_t csr_read_minstret(void)
{
	return READ_CSRNO(CSR_MINSTRET);
}

static inline void csr_write_minstret(uint_csr32_t value)
{
	WRITE_CSRNO(CSR_MINSTRET, value);
}

static inline uint_csr32_t csr_rw_minstret(uint_csr32_t value)
{
	return RW_CSRNO(CSR_MINSTRET, value);
}

static inline uint_csr32_t csr_set_minstret(uint_csr32_t setmask)
{
	return SET_CSRNO(CSR_MINSTRET, setmask);
}

static inline uint_csr32_t csr_clear_minstret(uint_csr32_t clrmask)
{
	return CLEAR_CSRNO(CSR_MINSTRET, clrmask);
}
#endif

/*------------------------------------------------------------------
 * register minstreth @ 0xb82
 *   (read-write 32-bit CSR mapped register)
 *   "Upper 32-bits of machine instructions-retired counter"
 *------------------------------------------------------------------
 */
#define CSR_MINSTRETH 2946

#ifndef __ASSEMBLER__
static inline uint_csr32_t csr_read_minstreth(void)
{
	return READ_CSRNO(CSR_MINSTRETH);
}

static inline void csr_write_minstreth(uint_csr32_t value)
{
	WRITE_CSRNO(CSR_MINSTRETH, value);
}

static inline uint_csr32_t csr_rw_minstreth(uint_csr32_t value)
{
	return RW_CSRNO(CSR_MINSTRETH, value);
}

static inline uint_csr32_t csr_set_minstreth(uint_csr32_t setmask)
{
	return SET_CSRNO(CSR_MINSTRETH, setmask);
}

static inline uint_csr32_t csr_clear_minstreth(uint_csr32_t clrmask)
{
	return CLEAR_CSRNO(CSR_MINSTRETH, clrmask);
}
#endif

/*------------------------------------------------------------------
 * register dcsr @ 0x7b0
 *   (read-write 32-bit CSR mapped register)
 *   "Debug control and status register"
 *------------------------------------------------------------------
 */
#define CSR_DCSR 1968
  // privilege mode before debug mode was entered 
  #define CSR_DCSR_F_PRV 0x00000003
  #define CSR_DCSR_F_PRV_OFFSET 0

    // user/application mode
    #define CSR_DCSR_F_PRV_E_USER 0x0

    // supervisor mode
    #define CSR_DCSR_F_PRV_E_SUPERVISOR 0x1

    // machine mode
    #define CSR_DCSR_F_PRV_E_MACHINE 0x3
  // when set and not in debug mode, the hart will only execute single instruction  and then enter debug mode 
  #define CSR_DCSR_F_STEP 0x00000004
  #define CSR_DCSR_F_STEP_OFFSET 2
  // When set, there is a Non-Maskable-Interrupt (NMI) pending for the hart. 
  #define CSR_DCSR_F_NMIP 0x00000008
  #define CSR_DCSR_F_NMIP_OFFSET 3
  // 0: ignore mprv in mstatus in debug mode; 1: mprv in mstatus takes effect in debug mode 
  #define CSR_DCSR_F_MPRVEN 0x00000010
  #define CSR_DCSR_F_MPRVEN_OFFSET 4
  // Explains why Debug Mode was entered. 
  #define CSR_DCSR_F_CAUSE 0x000001c0
  #define CSR_DCSR_F_CAUSE_OFFSET 6

    // an ebreak instruction was executed (priority 3)
    #define CSR_DCSR_F_CAUSE_E_EBREAK 0x1

    // the trigger module caused a breakpoint exception (priority 4, highest)
    #define CSR_DCSR_F_CAUSE_E_TRIGGER 0x2

    // the debugger requested entry to Debug Mode using haltreq (priority 1)
    #define CSR_DCSR_F_CAUSE_E_HALTREQ 0x3

    // the hart single stepped because step was set (priority 0, lowest)
    #define CSR_DCSR_F_CAUSE_E_STEP 0x4

    // The hart halted directly out of reset due to resethaltreq. (priority 2)
    #define CSR_DCSR_F_CAUSE_E_RESETHALTREQ 0x5
  // when 1, don't increment any hart-local timers while in debug mode 
  #define CSR_DCSR_F_STOPTIME 0x00000200
  #define CSR_DCSR_F_STOPTIME_OFFSET 9
  // when 1, don't increment any counters while in debug mode 
  #define CSR_DCSR_F_STOPCOUNT 0x00000400
  #define CSR_DCSR_F_STOPCOUNT_OFFSET 10
  // when 0, interrupts are disabled while single stepping 
  #define CSR_DCSR_F_STEPIE 0x00000800
  #define CSR_DCSR_F_STEPIE_OFFSET 11
  // when 0, ebreak instructions in U-mode behave as described in privileged spec, when 1, ebreak in U-mode enters debug mode 
  #define CSR_DCSR_F_EBREAKU 0x00001000
  #define CSR_DCSR_F_EBREAKU_OFFSET 12
  // when 0, ebreak instructions in S-mode behave as described in privileged spec, when 1, ebreak in S-mode enters debug mode 
  #define CSR_DCSR_F_EBREAKS 0x00002000
  #define CSR_DCSR_F_EBREAKS_OFFSET 13
  // when 0, ebreak instructions in M-mode behave as described in privileged spec, when 1, ebreak in M-mode enters debug mode 
  #define CSR_DCSR_F_EBREAKM 0x00008000
  #define CSR_DCSR_F_EBREAKM_OFFSET 15
  // debug specification version 
  #define CSR_DCSR_F_XDEBUGVER 0x1fe00000
  #define CSR_DCSR_F_XDEBUGVER_OFFSET 21

#ifndef __ASSEMBLER__
static inline uint_csr32_t csr_read_dcsr(void)
{
	return READ_CSRNO(CSR_DCSR);
}

static inline void csr_write_dcsr(uint_csr32_t value)
{
	WRITE_CSRNO(CSR_DCSR, value);
}

static inline uint_csr32_t csr_rw_dcsr(uint_csr32_t value)
{
	return RW_CSRNO(CSR_DCSR, value);
}

static inline uint_csr32_t csr_set_dcsr(uint_csr32_t setmask)
{
	return SET_CSRNO(CSR_DCSR, setmask);
}

static inline uint_csr32_t csr_clear_dcsr(uint_csr32_t clrmask)
{
	return CLEAR_CSRNO(CSR_DCSR, clrmask);
}
#endif

/*------------------------------------------------------------------
 * register dpc @ 0x7b1
 *   (read-write 32-bit CSR mapped register)
 *   "Debug PC"
 *------------------------------------------------------------------
 */
#define CSR_DPC 1969

#ifndef __ASSEMBLER__
static inline uint_csr32_t csr_read_dpc(void)
{
	return READ_CSRNO(CSR_DPC);
}

static inline void csr_write_dpc(uint_csr32_t value)
{
	WRITE_CSRNO(CSR_DPC, value);
}

static inline uint_csr32_t csr_rw_dpc(uint_csr32_t value)
{
	return RW_CSRNO(CSR_DPC, value);
}

static inline uint_csr32_t csr_set_dpc(uint_csr32_t setmask)
{
	return SET_CSRNO(CSR_DPC, setmask);
}

static inline uint_csr32_t csr_clear_dpc(uint_csr32_t clrmask)
{
	return CLEAR_CSRNO(CSR_DPC, clrmask);
}
#endif

/*------------------------------------------------------------------
 * register dscratch0 @ 0x7b2
 *   (read-write 32-bit CSR mapped register)
 *   "Debug scratch register 0"
 *------------------------------------------------------------------
 */
#define CSR_DSCRATCH0 1970

#ifndef __ASSEMBLER__
static inline uint_csr32_t csr_read_dscratch0(void)
{
	return READ_CSRNO(CSR_DSCRATCH0);
}

static inline void csr_write_dscratch0(uint_csr32_t value)
{
	WRITE_CSRNO(CSR_DSCRATCH0, value);
}

static inline uint_csr32_t csr_rw_dscratch0(uint_csr32_t value)
{
	return RW_CSRNO(CSR_DSCRATCH0, value);
}

static inline uint_csr32_t csr_set_dscratch0(uint_csr32_t setmask)
{
	return SET_CSRNO(CSR_DSCRATCH0, setmask);
}

static inline uint_csr32_t csr_clear_dscratch0(uint_csr32_t clrmask)
{
	return CLEAR_CSRNO(CSR_DSCRATCH0, clrmask);
}
#endif

/*------------------------------------------------------------------
 * register dscratch1 @ 0x7b3
 *   (read-write 32-bit CSR mapped register)
 *   "Debug scratch register 1"
 *------------------------------------------------------------------
 */
#define CSR_DSCRATCH1 1971

#ifndef __ASSEMBLER__
static inline uint_csr32_t csr_read_dscratch1(void)
{
	return READ_CSRNO(CSR_DSCRATCH1);
}

static inline void csr_write_dscratch1(uint_csr32_t value)
{
	WRITE_CSRNO(CSR_DSCRATCH1, value);
}

static inline uint_csr32_t csr_rw_dscratch1(uint_csr32_t value)
{
	return RW_CSRNO(CSR_DSCRATCH1, value);
}

static inline uint_csr32_t csr_set_dscratch1(uint_csr32_t setmask)
{
	return SET_CSRNO(CSR_DSCRATCH1, setmask);
}

static inline uint_csr32_t csr_clear_dscratch1(uint_csr32_t clrmask)
{
	return CLEAR_CSRNO(CSR_DSCRATCH1, clrmask);
}
#endif

/*------------------------------------------------------------------
 * register PICMR0 @ 0x7f0
 *   (read-write 32-bit CSR mapped register)
 *   "PICMR registers are used to to mask or unmask 32 programmable interrupt sources.
Interrupt sources with corresponding bit set are enabled. Interrupt sources with corresponding bit cleared is disabled (masked).
Bit 0 represents lowest interrupt number in a group."
 *------------------------------------------------------------------
 */
#define CSR_PICMR0 2032

#ifndef __ASSEMBLER__
static inline uint_csr32_t csr_read_picmr0(void)
{
	return READ_CSRNO(CSR_PICMR0);
}

static inline void csr_write_picmr0(uint_csr32_t value)
{
	WRITE_CSRNO(CSR_PICMR0, value);
}

static inline uint_csr32_t csr_rw_picmr0(uint_csr32_t value)
{
	return RW_CSRNO(CSR_PICMR0, value);
}

static inline uint_csr32_t csr_set_picmr0(uint_csr32_t setmask)
{
	return SET_CSRNO(CSR_PICMR0, setmask);
}

static inline uint_csr32_t csr_clear_picmr0(uint_csr32_t clrmask)
{
	return CLEAR_CSRNO(CSR_PICMR0, clrmask);
}
#endif

/*------------------------------------------------------------------
 * register PICMR1 @ 0x7f1
 *   (read-write 32-bit CSR mapped register)
 *   "PICMR registers are used to to mask or unmask 32 programmable interrupt sources.
Interrupt sources with corresponding bit set are enabled. Interrupt sources with corresponding bit cleared is disabled (masked).
Bit 0 represents lowest interrupt number in a group."
 *------------------------------------------------------------------
 */
#define CSR_PICMR1 2033

#ifndef __ASSEMBLER__
static inline uint_csr32_t csr_read_picmr1(void)
{
	return READ_CSRNO(CSR_PICMR1);
}

static inline void csr_write_picmr1(uint_csr32_t value)
{
	WRITE_CSRNO(CSR_PICMR1, value);
}

static inline uint_csr32_t csr_rw_picmr1(uint_csr32_t value)
{
	return RW_CSRNO(CSR_PICMR1, value);
}

static inline uint_csr32_t csr_set_picmr1(uint_csr32_t setmask)
{
	return SET_CSRNO(CSR_PICMR1, setmask);
}

static inline uint_csr32_t csr_clear_picmr1(uint_csr32_t clrmask)
{
	return CLEAR_CSRNO(CSR_PICMR1, clrmask);
}
#endif

/*------------------------------------------------------------------
 * register PICSR0 @ 0x7f2
 *   (read-only 32-bit CSR mapped register)
 *   "PICSR registers are used to determine the status of each PIC interrupt input.
PIC only supports level-triggered interrupts where bits in PICSR simply reflect level of unmasked interrupt inputs."
 *------------------------------------------------------------------
 */
#define CSR_PICSR0 2034

#ifndef __ASSEMBLER__
static inline uint_csr32_t csr_read_picsr0(void)
{
	return READ_CSRNO(CSR_PICSR0);
}
#endif

/*------------------------------------------------------------------
 * register PICSR1 @ 0x7f3
 *   (read-only 32-bit CSR mapped register)
 *   "PICSR registers are used to determine the status of each PIC interrupt input.
PIC only supports level-triggered interrupts where bits in PICSR simply reflect level of unmasked interrupt inputs."
 *------------------------------------------------------------------
 */
#define CSR_PICSR1 2035

#ifndef __ASSEMBLER__
static inline uint_csr32_t csr_read_picsr1(void)
{
	return READ_CSRNO(CSR_PICSR1);
}
#endif

/*------------------------------------------------------------------
 * register PICTR0 @ 0x7f4
 *   (write-only 32-bit CSR mapped register)
 *   "PICTR registers are used to internally trigger any of PIC interrupts.
The state of the PICTRs are or-ed with the state of PIC interrupt inputs."
 *------------------------------------------------------------------
 */
#define CSR_PICTR0 2036

#ifndef __ASSEMBLER__
static inline uint_csr32_t csr_read_pictr0(void)
{
	return READ_CSRNO(CSR_PICTR0);
}

static inline void csr_write_pictr0(uint_csr32_t value)
{
	WRITE_CSRNO(CSR_PICTR0, value);
}

static inline uint_csr32_t csr_rw_pictr0(uint_csr32_t value)
{
	return RW_CSRNO(CSR_PICTR0, value);
}

static inline uint_csr32_t csr_set_pictr0(uint_csr32_t setmask)
{
	return SET_CSRNO(CSR_PICTR0, setmask);
}

static inline uint_csr32_t csr_clear_pictr0(uint_csr32_t clrmask)
{
	return CLEAR_CSRNO(CSR_PICTR0, clrmask);
}
#endif

/*------------------------------------------------------------------
 * register PICTR1 @ 0x7f5
 *   (write-only 32-bit CSR mapped register)
 *   "PICTR registers are used to internally trigger any of PIC interrupts.
The state of the PICTRs are or-ed with the state of PIC interrupt inputs."
 *------------------------------------------------------------------
 */
#define CSR_PICTR1 2037

#ifndef __ASSEMBLER__
static inline uint_csr32_t csr_read_pictr1(void)
{
	return READ_CSRNO(CSR_PICTR1);
}

static inline void csr_write_pictr1(uint_csr32_t value)
{
	WRITE_CSRNO(CSR_PICTR1, value);
}

static inline uint_csr32_t csr_rw_pictr1(uint_csr32_t value)
{
	return RW_CSRNO(CSR_PICTR1, value);
}

static inline uint_csr32_t csr_set_pictr1(uint_csr32_t setmask)
{
	return SET_CSRNO(CSR_PICTR1, setmask);
}

static inline uint_csr32_t csr_clear_pictr1(uint_csr32_t clrmask)
{
	return CLEAR_CSRNO(CSR_PICTR1, clrmask);
}
#endif

/*------------------------------------------------------------------
 * register VICMR0 @ 0x7f6
 *   (read-write 32-bit CSR mapped register)
 *   "VICMR registers are used to to mask or unmask 32 programmable interrupt sources.
Interrupt sources with corresponding bits set are enabled. Interrupt sources with bit corresponding bits cleared are disabled (masked).
Bit 0 represents lowest interrupt number in a group."
 *------------------------------------------------------------------
 */
#define CSR_VICMR0 2038

#ifndef __ASSEMBLER__
static inline uint_csr32_t csr_read_vicmr0(void)
{
	return READ_CSRNO(CSR_VICMR0);
}

static inline void csr_write_vicmr0(uint_csr32_t value)
{
	WRITE_CSRNO(CSR_VICMR0, value);
}

static inline uint_csr32_t csr_rw_vicmr0(uint_csr32_t value)
{
	return RW_CSRNO(CSR_VICMR0, value);
}

static inline uint_csr32_t csr_set_vicmr0(uint_csr32_t setmask)
{
	return SET_CSRNO(CSR_VICMR0, setmask);
}

static inline uint_csr32_t csr_clear_vicmr0(uint_csr32_t clrmask)
{
	return CLEAR_CSRNO(CSR_VICMR0, clrmask);
}
#endif

/*------------------------------------------------------------------
 * register VICMR1 @ 0x7f7
 *   (read-write 32-bit CSR mapped register)
 *   "VICMR registers are used to to mask or unmask 32 programmable interrupt sources.
Interrupt sources with corresponding bits set are enabled. Interrupt sources with bit corresponding bits cleared are disabled (masked).
Bit 0 represents lowest interrupt number in a group."
 *------------------------------------------------------------------
 */
#define CSR_VICMR1 2039

#ifndef __ASSEMBLER__
static inline uint_csr32_t csr_read_vicmr1(void)
{
	return READ_CSRNO(CSR_VICMR1);
}

static inline void csr_write_vicmr1(uint_csr32_t value)
{
	WRITE_CSRNO(CSR_VICMR1, value);
}

static inline uint_csr32_t csr_rw_vicmr1(uint_csr32_t value)
{
	return RW_CSRNO(CSR_VICMR1, value);
}

static inline uint_csr32_t csr_set_vicmr1(uint_csr32_t setmask)
{
	return SET_CSRNO(CSR_VICMR1, setmask);
}

static inline uint_csr32_t csr_clear_vicmr1(uint_csr32_t clrmask)
{
	return CLEAR_CSRNO(CSR_VICMR1, clrmask);
}
#endif

/*------------------------------------------------------------------
 * register VICSR0 @ 0x7f8
 *   (read-only 32-bit CSR mapped register)
 *   "VICSR registers are used to determine the status of each VIC interrupt input.
VIC only supports level-triggered interrupts where bits in VICSR simply reflect level of unmasked interrupt inputs."
 *------------------------------------------------------------------
 */
#define CSR_VICSR0 2040

#ifndef __ASSEMBLER__
static inline uint_csr32_t csr_read_vicsr0(void)
{
	return READ_CSRNO(CSR_VICSR0);
}
#endif

/*------------------------------------------------------------------
 * register VICSR1 @ 0x7f9
 *   (read-only 32-bit CSR mapped register)
 *   "VICSR registers are used to determine the status of each VIC interrupt input.
VIC only supports level-triggered interrupts where bits in VICSR simply reflect level of unmasked interrupt inputs."
 *------------------------------------------------------------------
 */
#define CSR_VICSR1 2041

#ifndef __ASSEMBLER__
static inline uint_csr32_t csr_read_vicsr1(void)
{
	return READ_CSRNO(CSR_VICSR1);
}
#endif

/*------------------------------------------------------------------
 * register VICTR0 @ 0x7fa
 *   (read-write 32-bit CSR mapped register)
 *   "VICTR registers are used to internally trigger any of VIC interrupts. The state of the VICTRs are or-ed with the state of VIC interrupt inputs."
 *------------------------------------------------------------------
 */
#define CSR_VICTR0 2042

#ifndef __ASSEMBLER__
static inline uint_csr32_t csr_read_victr0(void)
{
	return READ_CSRNO(CSR_VICTR0);
}

static inline void csr_write_victr0(uint_csr32_t value)
{
	WRITE_CSRNO(CSR_VICTR0, value);
}

static inline uint_csr32_t csr_rw_victr0(uint_csr32_t value)
{
	return RW_CSRNO(CSR_VICTR0, value);
}

static inline uint_csr32_t csr_set_victr0(uint_csr32_t setmask)
{
	return SET_CSRNO(CSR_VICTR0, setmask);
}

static inline uint_csr32_t csr_clear_victr0(uint_csr32_t clrmask)
{
	return CLEAR_CSRNO(CSR_VICTR0, clrmask);
}
#endif

/*------------------------------------------------------------------
 * register VICTR1 @ 0x7fb
 *   (read-write 32-bit CSR mapped register)
 *   "VICTR registers are used to internally trigger any of VIC interrupts. The state of the VICTRs are or-ed with the state of VIC interrupt inputs."
 *------------------------------------------------------------------
 */
#define CSR_VICTR1 2043

#ifndef __ASSEMBLER__
static inline uint_csr32_t csr_read_victr1(void)
{
	return READ_CSRNO(CSR_VICTR1);
}

static inline void csr_write_victr1(uint_csr32_t value)
{
	WRITE_CSRNO(CSR_VICTR1, value);
}

static inline uint_csr32_t csr_rw_victr1(uint_csr32_t value)
{
	return RW_CSRNO(CSR_VICTR1, value);
}

static inline uint_csr32_t csr_set_victr1(uint_csr32_t setmask)
{
	return SET_CSRNO(CSR_VICTR1, setmask);
}

static inline uint_csr32_t csr_clear_victr1(uint_csr32_t clrmask)
{
	return CLEAR_CSRNO(CSR_VICTR1, clrmask);
}
#endif


#endif // __regaccess_Beyond_Semiconductor_BA5x_BydAHBSOC_1_0__