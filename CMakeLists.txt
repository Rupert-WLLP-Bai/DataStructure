# CMakeList.txt: 顶层 CMake 项目文件，在此处执行全局配置
# 并包含子项目。
#
cmake_minimum_required (VERSION 3.8)

add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

set(CMAKE_CXX_STANDARD_REQUIRED ON)
# 指定为C++11 版本
set(CMAKE_CXX_STANDARD 11)

project (DataStructure VERSION 0.1)

# 包含子项目。
add_subdirectory ("Q01")
add_subdirectory ("Q02")
add_subdirectory ("Q03")
add_subdirectory ("Q04")
add_subdirectory ("Q05")
add_subdirectory ("Q06")
add_subdirectory ("Q07")
add_subdirectory ("Q08(origin)")
add_subdirectory ("Q08(develop)")
add_subdirectory ("Q09")
add_subdirectory ("Q10")