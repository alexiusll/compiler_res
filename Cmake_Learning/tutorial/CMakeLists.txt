
# 设置CMake版本
cmake_minimum_required(VERSION 3.10)

# 设置项目名称命令 增加版本号
project(Tutorial VERSION 21.233)

# 我们需要在CMake代码中明确指定使用正确的编译标志。
# 在CMake中启用特定C++标准的一种方法是使用CMAKE_CXX_STANDARD变量。
# 在本教程中，将CMAKE_CXX_STANDARD变量设置为11，并将CMAKE_CXX_STANDARD_REQUIRED设置为True，
# 请确保在add_executable()调用之前添加CMAKE_CXX_STANDARD声明。
set(CMAKE_CXX_STANDARD 11) # 设置所需的C++标准为C++11
set(CMAKE_CXX_STANDARD_REQUIRED True) # 强制编译器使用所需的C++标准

# configure_file 用于生成配置头文件
# 这个命令的作用是将一个输入文件TutorialConfig.h.in复制到输出文件TutorialConfig.h，
# 并在复制的过程中替换其中的占位符（placeholder）或变量。
configure_file(TutorialConfig.h.in TutorialConfig.h)

# 调用基本项目
add_executable(Tutorial tutorial.cpp)

#! 这个要放到最后
# 指定一个目标（target）的包含目录
# Tutorial 是目标的名称
# 使用PUBLIC关键字，指定这个目录对于Tutorial目标以及依赖它的其他目标都是可见的。
# "${PROJECT_BINARY_DIR}" 是一个变量，它表示项目的二进制目录，也就是构建目录
target_include_directories(Tutorial PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )