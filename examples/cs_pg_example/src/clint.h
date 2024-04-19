/*******************************************************************
 * Register definitions for
 * ============================
 * BA5x_BydAHBSOC, version: 1.0
 *   peripheral
 * CLINT
 *   by 
 * Beyond Semiconductor
 * 
 * Created by sdtool 
 *   from sd/ba5x-byd-ahb-soc.sd.xml
 *   on 2022-11-21 15:17:43.987569
 *   using template src/templates/h/mmio.jinja
 *******************************************************************
 */

 #ifndef __regaccess_Beyond_Semiconductor_BA5x_BydAHBSOC_1_0_CLINT__
 #define __regaccess_Beyond_Semiconductor_BA5x_BydAHBSOC_1_0_CLINT__

#include "rvrac.h"
/*------------------------------------------------------------------
 * register msip @ 0x2000000
 *   (read-write 32-bit memory mapped register)
 *   "machine mode software interrupt"
 *------------------------------------------------------------------
 */
#define CLINT_MSIP 0x02000000
#define CLINT_MSIP_PTR (uint32_t *)(0x02000000)

  /* software interrupt */ 
  #define CLINT_MSIP_F_MSIP 0x00000001
  #define CLINT_MSIP_F_MSIP_OFFSET 0


#ifndef __ASSEMBLER__

static inline uint32_t clint_read_msip(void)
{
	return REG32(CLINT_MSIP);
}

static inline void clint_write_msip(uint32_t value)
{
	REG32(CLINT_MSIP) = value;
}

static inline uint32_t clint_rw_msip(uint32_t value)
{
	return rw_reg32(CLINT_MSIP_PTR, value);
}

static inline uint32_t clint_set_msip(uint_csr32_t setmask)
{
	return set_reg32(CLINT_MSIP_PTR, setmask);
}

static inline uint32_t clint_clear_msip(uint_csr32_t clrmask)
{
	return clear_reg32(CLINT_MSIP_PTR, clrmask);
}
#endif

/*------------------------------------------------------------------
 * register mtimecmp @ 0x2004000
 *   (read-write 32-bit memory mapped register)
 *   "timer compare register (low)"
 *------------------------------------------------------------------
 */
#define CLINT_MTIMECMP 0x02004000
#define CLINT_MTIMECMP_PTR (uint32_t *)(0x02004000)


#ifndef __ASSEMBLER__

static inline uint32_t clint_read_mtimecmp(void)
{
	return REG32(CLINT_MTIMECMP);
}

static inline void clint_write_mtimecmp(uint32_t value)
{
	REG32(CLINT_MTIMECMP) = value;
}

static inline uint32_t clint_rw_mtimecmp(uint32_t value)
{
	return rw_reg32(CLINT_MTIMECMP_PTR, value);
}

static inline uint32_t clint_set_mtimecmp(uint_csr32_t setmask)
{
	return set_reg32(CLINT_MTIMECMP_PTR, setmask);
}

static inline uint32_t clint_clear_mtimecmp(uint_csr32_t clrmask)
{
	return clear_reg32(CLINT_MTIMECMP_PTR, clrmask);
}
#endif

/*------------------------------------------------------------------
 * register mtimecmphi @ 0x2004004
 *   (read-write 32-bit memory mapped register)
 *   "timer compare register (high)"
 *------------------------------------------------------------------
 */
#define CLINT_MTIMECMPHI 0x02004004
#define CLINT_MTIMECMPHI_PTR (uint32_t *)(0x02004004)


#ifndef __ASSEMBLER__

static inline uint32_t clint_read_mtimecmphi(void)
{
	return REG32(CLINT_MTIMECMPHI);
}

static inline void clint_write_mtimecmphi(uint32_t value)
{
	REG32(CLINT_MTIMECMPHI) = value;
}

static inline uint32_t clint_rw_mtimecmphi(uint32_t value)
{
	return rw_reg32(CLINT_MTIMECMPHI_PTR, value);
}

static inline uint32_t clint_set_mtimecmphi(uint_csr32_t setmask)
{
	return set_reg32(CLINT_MTIMECMPHI_PTR, setmask);
}

static inline uint32_t clint_clear_mtimecmphi(uint_csr32_t clrmask)
{
	return clear_reg32(CLINT_MTIMECMPHI_PTR, clrmask);
}
#endif

/*------------------------------------------------------------------
 * register mtime @ 0x200bff8
 *   (read-write 32-bit memory mapped register)
 *   "timer register (low)"
 *------------------------------------------------------------------
 */
#define CLINT_MTIME 0x0200bff8
#define CLINT_MTIME_PTR (uint32_t *)(0x0200bff8)


#ifndef __ASSEMBLER__

static inline uint32_t clint_read_mtime(void)
{
	return REG32(CLINT_MTIME);
}

static inline void clint_write_mtime(uint32_t value)
{
	REG32(CLINT_MTIME) = value;
}

static inline uint32_t clint_rw_mtime(uint32_t value)
{
	return rw_reg32(CLINT_MTIME_PTR, value);
}

static inline uint32_t clint_set_mtime(uint_csr32_t setmask)
{
	return set_reg32(CLINT_MTIME_PTR, setmask);
}

static inline uint32_t clint_clear_mtime(uint_csr32_t clrmask)
{
	return clear_reg32(CLINT_MTIME_PTR, clrmask);
}
#endif

/*------------------------------------------------------------------
 * register mtimehi @ 0x200bffc
 *   (read-write 32-bit memory mapped register)
 *   "timer register (high)"
 *------------------------------------------------------------------
 */
#define CLINT_MTIMEHI 0x0200bffc
#define CLINT_MTIMEHI_PTR (uint32_t *)(0x0200bffc)


#ifndef __ASSEMBLER__

static inline uint32_t clint_read_mtimehi(void)
{
	return REG32(CLINT_MTIMEHI);
}

static inline void clint_write_mtimehi(uint32_t value)
{
	REG32(CLINT_MTIMEHI) = value;
}

static inline uint32_t clint_rw_mtimehi(uint32_t value)
{
	return rw_reg32(CLINT_MTIMEHI_PTR, value);
}

static inline uint32_t clint_set_mtimehi(uint_csr32_t setmask)
{
	return set_reg32(CLINT_MTIMEHI_PTR, setmask);
}

static inline uint32_t clint_clear_mtimehi(uint_csr32_t clrmask)
{
	return clear_reg32(CLINT_MTIMEHI_PTR, clrmask);
}
#endif


#endif // __regaccess_Beyond_Semiconductor_BA5x_BydAHBSOC_1_0_CLINT__
