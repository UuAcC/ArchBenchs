/// @file
/// @brief platform init funcs

#include <sys/errno.h>
#include <string.h>
#include <unistd.h>

#include "memasm.h"

extern char _tdata_start[], _tdata_end[], _tbss_start[], _tbss_end[];

extern const uint8_t __data_source_start;
extern uint8_t __data_target_start;
extern uint8_t __data_target_end;

extern const uint8_t __sdata_source_start;
extern uint8_t __sdata_target_start;
extern uint8_t __sdata_target_end;

extern void plf_init_relocate(void) __attribute__((weak));

extern char __bss_start[], __bss_end[];
extern char _ramfunc_start[], _ramfunc_end[];
extern char __etext[];

void __init plf_init_noreloc(void) {
    // Do nothing
}

void CopyToRAM (void* dest, void* src, uint32_t cnt) {
    uint32_t *source_pointer;
    uint32_t *destination_pointer;
    uint32_t i;
    uint32_t words_count;

    source_pointer = (uint32_t *)src;
    destination_pointer = (uint32_t *)dest;
	words_count = cnt >> 2;

    for (i = 0; i < words_count; i++) {
        *destination_pointer = *source_pointer;
        destination_pointer++;
        source_pointer++;
    }
}

void __init plf_init_generic(void) {
    // do relocations
    //plf_init_relocate();
    // init TLS
    //register void *tp asm ("tp");
    //plf_init_tls(tp);
    // init BSS
    memset(__bss_start, 0, (size_t)(__bss_end - __bss_start));
    memcpy((void*)&__data_target_start,
           (const void*)&__data_source_start,
           (&__data_target_end - &__data_target_start));

    memcpy((void*)&__sdata_target_start,
              (const void*)&__sdata_source_start,
              (&__sdata_target_end - &__sdata_target_start));
    //memcpy(_ramfunc_start, __etext, (size_t)(_ramfunc_end - _ramfunc_start));
    CopyToRAM(_ramfunc_start, __etext, (size_t)(_ramfunc_end - _ramfunc_start));
    // enable/init caches
    //plf_l2cache_init();
    //plf_l1cache_init();
    // enable/init MPU
    //mpu_init();
    // init peripheries
    //con_init();
    //rtc_init();
    //leds_init();
    // init smp
    //plf_smp_init();
}

void plf_init(void) __attribute__((weak, alias("plf_init_generic")));

