#include "K1921VG1T.h"
#include <stdint.h>

void trng_init(void) {
    RCU->CGCFGAPB0_bit.TRNGEN = 1;      // Подача тактового сигнала
    RCU->RSTDISAPB0_bit.TRNGEN = 1;     // Вывод из сброса
    TRNG->CR |= TRNG_CR_START_Msk;      // Старт работы
}

uint32_t trng_get_word(void) {
    while (TRNG->FIFOLEV_bit.VAL == 0) { }
    return TRNG->FIFO[0].FIFO;  // или TRNG->FIFO[0].FIFO_bit.VAL
}