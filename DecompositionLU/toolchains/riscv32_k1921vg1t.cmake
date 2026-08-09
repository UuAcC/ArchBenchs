cmake_minimum_required(VERSION 3.8)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR riscv32)

set(DEVBOARDS_FOLDER "C:/Users/Maxim/source/devboards")
set(TOOLCHAIN_PATH "${DEVBOARDS_FOLDER}/xpack-riscv-none-elf-gcc-15.2.0-1")
set(SDK_ROOT "${DEVBOARDS_FOLDER}/k1921vg1t_sdk")
set(DEVICE_ROOT "platform_k1921vg1t")
set(BSP_ROOT "${SDK_ROOT}/hardware/bsp/NIIET-DEV-K1921VG1T")

set(CMAKE_C_COMPILER "${TOOLCHAIN_PATH}/bin/riscv-none-elf-gcc.exe")
set(CMAKE_CXX_COMPILER "${TOOLCHAIN_PATH}/bin/riscv-none-elf-g++.exe")

set(BASE_MARCH "-march=rv32imafdc")
set(ADV_MARCH "${BASE_MARCH}_zicsr_zifencei")
set(MABI "-mabi=ilp32d")

set(ARCH_FLAGS "${ADV_MARCH} ${MABI}")
set(C_CXX_FLAGS "-nostartfiles ${ARCH_FLAGS} -DRETARGET -DUSE_LIBC")
# --------------------------------------------------------------------#
set(C_CXX_FLAGS "${C_CXX_FLAGS} -ffunction-sections -fdata-sections") #
# --------------------------------------------------------------------#
set(COMMON_INCLUDE_FLAGS "-I\"${DEVICE_ROOT}/Include\" -I\"${DEVICE_ROOT}/ldscripts\"")
set(ALL_INCLUDE_FLAGS "${COMMON_INCLUDE_FLAGS} -I\"${BSP_ROOT}\"")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DSYSCLK_PLL -DHSECLK_VAL=16000000 ${ALL_INCLUDE_FLAGS} -std=gnu11 ${C_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ALL_INCLUDE_FLAGS} -std=gnu++11 -fabi-version=0 ${C_CXX_FLAGS}")
set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} -x assembler-with-cpp ${COMMON_INCLUDE_FLAGS} ${ARCH_FLAGS}")

set(TARGET_LINKER_SCRIPT "${DEVICE_ROOT}/ldscripts/k1921vg1t_flash.ld")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -T\"${TARGET_LINKER_SCRIPT}\" -L\"${DEVICE_ROOT}/ldscripts\" -L\"${BSP_ROOT}\"")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Map,\"${PROJECT_NAME}.map\" -nostartfiles ${BASE_MARCH} ${MABI}")
# ------------------------------------------------------------------------#
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--gc-sections") #
# ------------------------------------------------------------------------#

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE NEVER)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

#C:
#	-DSYSCLK_PLL -DHSECLK_VAL=16000000 
#	-I"C:\Users\Maxim\source\devboards\k1921vg1t_sdk\platform\Device\K1921VG1T\Include" 
#	-I"C:\Users\Maxim\source\devboards\k1921vg1t_sdk\platform\Device\K1921VG1T\ldscripts" 
#	-I"C:\Users\Maxim\source\devboards\k1921vg1t_sdk\hardware\bsp\NIIET-DEV-K1921VG1T" 
#	-std=gnu11 
#	-nostartfiles 
#	-march=rv32imafdc_zicsr_zifencei -mabi=ilp32d

#ASM:
#	-x assembler-with-cpp 
#	-I"C:\Users\Maxim\source\devboards\k1921vg1t_sdk\platform\Device\K1921VG1T\Include" 
#	-I"C:\Users\Maxim\source\devboards\k1921vg1t_sdk\platform\Device\K1921VG1T\ldscripts" 
###############	-include"C:\Users\Maxim\source\devboards\k1921vg1t_sdk\platform\Device\K1921VG1T\Include\common_asm.h"
#	-march=rv32imafdc_zicsr_zifencei -mabi=ilp32d

#C++:
#	-I"C:\Users\Maxim\source\devboards\k1921vg1t_sdk\platform\Device\K1921VG1T\Include" 
#	-I"C:\Users\Maxim\source\devboards\k1921vg1t_sdk\platform\Device\K1921VG1T\ldscripts" 
#	-I"C:\Users\Maxim\source\devboards\k1921vg1t_sdk\hardware\bsp\NIIET-DEV-K1921VG1T" 
#	-std=gnu++11 -fabi-version=0 
#	-nostartfiles -march=rv32imafdc_zicsr_zifencei -mabi=ilp32d

#Linker:
#	-T "C:\Users\Maxim\source\devboards\k1921vg1t_sdk\platform\Device\K1921VG1T\ldscripts\k1921vg1t_flash.ld" 
#	-L"C:\Users\Maxim\source\devboards\k1921vg1t_sdk\platform\Device\K1921VG1T\ldscripts" 
#	-L"C:\Users\Maxim\source\devboards\k1921vg1t_sdk\hardware\bsp\NIIET-DEV-K1921VG1T" 
#	-Wl,-Map,"hash.map" 
#	-nostartfiles -march=rv32imafdc -mabi=ilp32d