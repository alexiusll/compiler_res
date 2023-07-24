
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

# 向当前项目添加一个子目录。在这个命令中，MathFunctions 是要添加的子目录的名称
# 通过执行 add_subdirectory(MathFunctions)，CMake将会在当前项目中引入 MathFunctions 子目录，
# 并在 MathFunctions 子目录中执行相应的 CMakeLists.txt 文件。
add_subdirectory(MathFunctions)

# configure_file 用于生成配置头文件
# 这个命令的作用是将一个输入文件TutorialConfig.h.in复制到输出文件TutorialConfig.h，
# 并在复制的过程中替换其中的占位符（placeholder）或变量。
configure_file(TutorialConfig.h.in TutorialConfig.h)

# 调用基本项目
add_executable(Tutorial tutorial.cpp)

# 将一个库（或目标）链接到另一个目标。
# 在这个命令中，Tutorial 是目标的名称，表示一个由 add_executable() 或 add_library() 命令创建的可执行文件或库。
# MathFunctions 是要链接的库的名称，这里 MathFunctions 是由 add_library() 命令创建的库。
target_link_libraries(Tutorial PUBLIC MathFunctions)

# 包含新的目录
target_include_directories(Tutorial PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/MathFunctions"
                          )

#! 这个要放到最后
# 指定一个目标（target）的包含目录
# Tutorial 是目标的名称
# 使用PUBLIC关键字，指定这个目录对于Tutorial目标以及依赖它的其他目标都是可见的。
# "${PROJECT_BINARY_DIR}" 是一个变量，它表示项目的二进制目录，也就是构建目录
target_include_directories(Tutorial PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )