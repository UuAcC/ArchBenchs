/// @file
/// @brief IPI defs and inline funcs
///
/// Syntacore SCR* framework
///
/// @copyright Syntacore, 2015-2016. All rights reserved.
///
/// @author mn-sc
///

#ifndef SCR_IPI_H
#define SCR_IPI_H

#define SCR_CSR_IPI_MADDR   (0xBD8)
#define SCR_CSR_IPI_MSTATUS (0xBD9)
#define SCR_CSR_IPI_MRDATA  (0xBDA)
#define SCR_CSR_IPI_MWDATA  (0xBDB)

#define SCR_IPI_SRC_BITS (1)
#define SCR_IPI_SRC_MASK (1)

#ifndef __ASSEMBLER__
#include "arch.h"

static inline unsigned ipi_selfaddr(void)
{
    return read_csr(SCR_CSR_IPI_MADDR);
}

static inline void ipi_send_nowait(unsigned dst, unsigned long val)
{
    write_csr(SCR_CSR_IPI_MADDR, dst);
    write_csr(SCR_CSR_IPI_MWDATA, val);
}
#endif  // __ASSEMBLER__

#endif  // SCR_IPI_H
