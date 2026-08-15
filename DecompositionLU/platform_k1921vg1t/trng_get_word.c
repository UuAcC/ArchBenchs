#include "K1921VG1T.h"
#include <stdint.h>

uint32_t trng_get_word(void) {
    TRNG->CR |= TRNG_CR_START_Msk;
    while (TRNG->FIFOLEV_bit.VAL == 0) { }
    return TRNG->FIFO[0].FIFO;  // или TRNG->FIFO[0].FIFO_bit.VAL
}