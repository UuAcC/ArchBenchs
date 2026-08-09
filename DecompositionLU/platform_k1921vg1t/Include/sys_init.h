/*
 *
 * sys_init header for "S1252AUTO"
 *
 * created by Terekhov M.A.
 *
 * 2024
 *
*/

// Header for copy function
//  Usage example:
//  1. declare labels for "source code start", "destination code start" as "chars"
//     with names as in linker file, e.g.:
//
//     extern char __etext[]; // copy from FLASH
//     extern char _ramfunc_start[], _ramfunc_end[]; // to SRAM
//
//  2. call function as follows:
//
//     CopyToRAM(_ramfunc_start, __etext, (size_t)(_ramfunc_end - _ramfunc_start));
//

void CopyToRAM (void* dest, void* src, uint32_t cnt);
