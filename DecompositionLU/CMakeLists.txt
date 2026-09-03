cmake_minimum_required(VERSION 3.8)

set(project_name "LU_Benchmark")
project(${project_name})

enable_language(ASM)

file(GLOB hdrs "source/*.h*")
file(GLOB srcs "source/*.cpp")
set(PF "platform_k1921vg1t")
file(GLOB pf_srcs "${PF}/*.c")
file(GLOB pf_hdrs "${PF}/*.h")
file(GLOB pfsrc_srcs "${PF}/source/*.c")
file(GLOB pfinc_hdrs "${PF}/Include/*.h")

set_source_files_properties(${PF}/source/startup_k1921vg1t.S PROPERTIES LANGUAGE ASM)

add_executable(${project_name} 
		${srcs} 
		${hdrs} 
		${pf_srcs} 
		${pf_hdrs} 
		${pfsrc_srcs}
		${pfinc_hdrs}
		${PF}/source/startup_k1921vg1t.S
)

target_include_directories(${project_name} PRIVATE "${PF}/Include")

target_link_options(${project_name} PRIVATE
    -T${CMAKE_CURRENT_SOURCE_DIR}/${PF}/ldscripts/k1921vg1t_flash.ld
    -L${CMAKE_CURRENT_SOURCE_DIR}/${PF}/ldscripts
    -L${BSP_ROOT}
    -Wl,-Map,${project_name}.map
#---------------------#
    -Wl,--gc-sections #
#---------------------#
    -u _printf_float
    --specs=nano.specs
)

if(DEFINED PRINT_BLOCK_TIMES)
    target_compile_definitions(${project_name} PRIVATE 
        PRINT_BLOCK_TIMES=${PRINT_BLOCK_TIMES}
    )
endif()

if(DEFINED LU_BLOCK_SIZE)
    target_compile_definitions(${project_name} PRIVATE 
        LU_BLOCK_SIZE=${LU_BLOCK_SIZE}
    )
endif()

if(DEFINED TYPE)
target_compile_definitions(${project_name} PRIVATE 
        working_type=${TYPE}
    )
endif()

if(DEFINED REFERENCE_TEST)
    target_compile_definitions(${project_name} PRIVATE 
        REFERENCE_TEST=${REFERENCE_TEST}
    )
    if(${REFERENCE_TEST} STREQUAL "eigen")
        message(STATUS "Using Eigen as reference")
        target_include_directories(${project_name} PRIVATE 
            "${CMAKE_CURRENT_LIST_DIR}/eigen-5.0.0"
        )
    else()
        message(STATUS "Reference not found")
    endif()
endif()