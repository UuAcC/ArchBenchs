//
// @file       <ms_ipic_csr.h>
// @brief      @brief  M-mode and S-mode IPIC CSR registers and their bits
//
// Copyright by Syntacore LLC © 2019. ALL RIGHTS RESERVED. STRICTLY CONFIDENTIAL.
// Information contained in this material is confidential and proprietary to Syntacore LLC
// and its affiliates and may not be modified, copied, published, disclosed, distributed,
// displayed or exhibited, in either electronic or printed formats without written
// authorization of the Syntacore LLC. Subject to License Agreement.
//

#ifndef MS_IPIC_CSR_H
#define MS_IPIC_CSR_H

//  M-mode IPIC registers

#define M_IPIC_CISV     0xBF0 // MRO Current Interrupt Vector in Service
#define M_IPIC_CICSR    0xBF1 // MRW Current Interrupt Control Status Register
#define M_IPIC_IPR      0xBF2 // MRW Interrupt Pending Register
#define M_IPIC_ISVR     0xBF3 // MRO Interrupts in Service Register
#define M_IPIC_EOI      0xBF4 // MWO End Of Interrupt
#define M_IPIC_SOI      0xBF5 // MWO Start of Interrupt
#define M_IPIC_IDX      0xBF6 // MRW Index Register
#define M_IPIC_ICSR     0xBF7 // MRW Interrupt Control Status Register
#define M_IPIC_IER      0xBF8 // MRW Interrupt Enable Register
#define M_IPIC_IMAP     0xBF9 // MRO Interrupt Map Register

//  S-mode IPIC registers

#define S_IPIC_CISV     0x9F0 // SRO Current Interrupt Vector in Service
#define S_IPIC_SCICSR   0x9F1 // SRW Current Interrupt Control Status Register
#define S_IPIC_IPR      0x9F2 // SRW Interrupt Pending Register
#define S_IPIC_ISVR     0x9F3 // SRO Interrupts in Service Register
#define S_IPIC_SEOI     0x9F4 // SWO End Of Interrupt
#define S_IPIC_SOI      0x9F5 // SWO Start of Interrupt
#define S_IPIC_IDX      0x9F6 // SRW Index Register
#define S_IPIC_ICSR     0x9F7 // SRW Interrupt Control Status Register
#define S_IPIC_IER      0x9F8 // SRW Interrupt Enable Register
#define S_IPIC_IMAP     0x9F9 // SRO Interrupt Map Register

//  IPIC_SCICSR bits

#define IPIC_SCICSR_IP  0x00000001  // RW1C Interrupt pending
#define IPIC_SCICSR_IE  0x00000002  // RW Interrupt Enable Bit

//  IPIC_ICSR bits

#define IPIC_ICSR_IP    0x00000001  // S, RW1C Interrupt pending
#define IPIC_ICSR_IE    0x00000002  // S, RW Interrupt Enable Bit
#define IPIC_ICSR_IM    0x00000004  // M, RW Interrupt Mode
#define IPIC_ICSR_INV   0x00000008  // M, RW Line Inversion
#define IPIC_ICSR_IS    0x00000010  // M, RW In Service

#ifdef RVS_EXT
#define IPIC_ICSR_PRVC   0x00000100  // Always 1 in PRW
#define IPIC_ICSR_PRV_RW 0x00000200  // Read/Write mask for PRV: S(0)/M(1)
#define IPIC_ICSR_PRV    0x00000300  // S(01)/M(11), RW Priveledge mode
#else
#define IPIC_ICSR_PRVC   0x00000300  // Always 1 in PRW
#define IPIC_ICSR_PRV_RW 0x00000000  // Read/Write mask for PRV: S(0)/M(1)
#define IPIC_ICSR_PRV    0x00000300  // S(01)/M(11), RW Priveledge mode
#endif

#define IPIC_ICSR_LN    0x0003f000  // M, RW External IRQ Line Number

#endif
