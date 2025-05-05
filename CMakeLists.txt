cmake_minimum_required(VERSION 3.12)
project(car C CXX)

set(TOOLCHAIN_PREFIX 
    "/mnt/e/学校课程/程序设计/大作业2/duo-examples/host-tools/gcc/riscv64-linux-musl-x86_64/bin/riscv64-unknown-linux-musl-"
)

set (CMAKE_SYSROOT "/mnt/e/学校课程/程序设计/大作业2/duo-examples/host-tools/gcc/riscv64-linux-musl-x86_64/bin/../sysroot")
set (CMAKE_CXX_FLAGS "--sysroot=${CMAKE_SYSROOT}")
set (CMAKE_C_FLAGS "--sysroot=${CMAKE_SYSROOT}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--dynamic-linker=/lib/ld-musl-riscv64v0p7_xthead.so.1")


add_link_options(

)

# 设置编译器路径
set(CMAKE_C_COMPILER   "${TOOLCHAIN_PREFIX}gcc")
set(CMAKE_CXX_COMPILER "${TOOLCHAIN_PREFIX}g++")

message(STATUS "C Compiler: ${CMAKE_C_COMPILER}")
message(STATUS "CXX Compiler: ${CMAKE_CXX_COMPILER}")

add_compile_options(
    -mcpu=c906fdv 
    -march=rv64imafdcv0p7xthead 
    -mcmodel=medany 
    -mabi=lp64d 
    -O3 
    -DNDEBUG
    -D_LARGEFILE_SOURCE
    -D_LARGEFILE64_SOURCE
    -D_FILE_OFFSET_BITS=64
    -std=c++17
)
aux_source_directory(. all_cpp)

include_directories(
    "/mnt/e/学校课程/程序设计/大作业2/duo-examples/include/system"    
    # "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

link_directories(
    "/mnt/e/学校课程/程序设计/大作业2/duo-examples/libs/system/musl_riscv64"
    # "${CMAKE_CURRENT_SOURCE_DIR}/libs"
)

add_executable(car 
    ${all_cpp}
)

target_link_libraries(car wiringx)