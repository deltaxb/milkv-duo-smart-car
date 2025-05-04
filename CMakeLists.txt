cmake_minimum_required(VERSION 3.12)
project(car C CXX)

set(TOOLCHAIN_PREFIX 
    "/mnt/e/学校课程/程序设计/大作业2/duo-examples/host-tools/gcc/riscv64-linux-musl-x86_64/bin/riscv64-unknown-linux-musl-"
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
    -I/mnt/e/学校课程/程序设计/大作业2/duo-examples/include/system
    -std=c++17
)
aux_source_directory(. all_cpp)

include_directories(
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

link_directories(
    "${CMAKE_CURRENT_SOURCE_DIR}/libs"
)

add_executable(car 
    ${all_cpp}
)

target_link_libraries(car wiringx)