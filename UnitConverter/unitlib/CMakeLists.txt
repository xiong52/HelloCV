cmake_minimum_required(VERSION 3.10)
project(unitlib)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 11)

# 包含头文件目录
include_directories(include)

# 将源文件打包为静态库 (STATIC)
add_library(unitlib STATIC src/unitlib.cpp)