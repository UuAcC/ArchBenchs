#include <sys/time.h>
#include <stdint.h>
#include "mtimer.h"

static uint64_t base_ticks = 0;

int _gettimeofday(struct timeval* tv, void* tz) {
    (void)tz;
    if (tv) {
        uint64_t now_ticks = mtimer_get_raw_time();
        if (base_ticks == 0) {
            base_ticks = now_ticks;
        }
        uint64_t delta_ticks = now_ticks - base_ticks;
        uint64_t us = (delta_ticks * 1000000ULL) / MTIME_FREQ_HZ;
        tv->tv_sec = us / 1000000ULL;
        tv->tv_usec = us % 1000000ULL;
    }
    return 0;
}