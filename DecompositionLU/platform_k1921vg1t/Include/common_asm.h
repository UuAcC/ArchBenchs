// @file <common_asm.h>
// @brief common defs
//
// Copyright by Syntacore LLC © 2019. ALL RIGHTS RESERVED. STRICTLY CONFIDENTIAL.
// Information contained in this material is confidential and proprietary to Syntacore LLC
// and its affiliates and may not be modified, copied, published, disclosed, distributed,
// displayed or exhibited, in either electronic or printed formats without written
// authorization of the Syntacore LLC. Subject to License Agreement.
//

#ifndef __COMMON__ASM__H
#define __COMMON__ASM__H

.macro zero_int_reg regn
mv   x\regn, zero
.endm

.macro zero_int_regs reg_first, reg_last
.set regn, \reg_first
.rept \reg_last - \reg_first + 1
zero_int_reg %(regn)
.set regn, regn+1
.endr
.endm

.macro zero_f_reg regn
fmv.s.x   f\regn, x0
.endm

.macro zero_f_regs reg_first, reg_last
.set regn, \reg_first
.rept \reg_last - \reg_first + 1
zero_f_reg %(regn)
.set regn, regn+1
.endr
.endm

#endif // #ifndef __COMMON__ASM__H
