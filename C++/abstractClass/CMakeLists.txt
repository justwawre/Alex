cmake_minimum_required(VERSION 3.8)
project(logA)
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall ${CMAKE_CXX_FLAGS} -O3 -ftest-coverage -fprofile-arcs")

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_SRCS)

# 指定生成目标
add_executable(class_test ${DIR_SRCS})


