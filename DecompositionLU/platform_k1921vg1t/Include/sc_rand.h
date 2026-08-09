#ifndef __SC__RAND__H
#define __SC__RAND__H

#include <stdint.h>

typedef struct Xor128_data {
    uint32_t x;
    uint32_t y;
    uint32_t z;
    uint32_t w;
} Xor128_data;

static Xor128_data xor128data = {
    .x = 123456798,
    .y = 362436069,
    .z = 521288629,
    .w = 88675123,
};

static uint32_t xor128(Xor128_data *ptr)
{
    uint32_t t;
    t = ptr->x ^ (ptr->x << 11);
    ptr->x = ptr->y;
    ptr->y = ptr->z;
    ptr->z = ptr->w;
    return ptr->w = ptr->w ^ (ptr->w >> 19) ^ (t ^ (t >> 8));
}

static void xor128_seed(Xor128_data *ptr, uint32_t seed)
{
    ptr->x = seed;
}

static inline unsigned sc_rand(void)
{
    return xor128(&xor128data);
}

static inline void sc_srand(unsigned seed)
{
    xor128_seed(&xor128data, seed);
}

static inline unsigned sc_rand_local(Xor128_data *ptr)
{
    return xor128(ptr);
}

static inline void sc_srand_local(Xor128_data *ptr, unsigned seed)
{
    xor128_seed(ptr, seed);
}

#endif // #ifndef __SC__RAND__H
