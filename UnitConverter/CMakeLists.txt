cmake_minimum_required(VERSION 3.10)
project(UnitConverter)

set(CMAKE_CXX_STANDARD 11)

# 添加子目录 (进入 unitlib 目录执行其 CMakeLists.txt)
add_subdirectory(unitlib)

# 包含 unitlib 的头文件目录，以便 main.cpp 能找到 unitlib.h
include_directories(unitlib/include)

# 编译主程序
add_executable(UnitConverter src/main.cpp)

# 将 unitlib 库链接到主程序
target_link_libraries(UnitConverter unitlib)