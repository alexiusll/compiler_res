cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(Tutorial VERSION 1.0)

# add_library 用于创建一个库（Library）目标。在这里，我们创建了一个特殊的库目标，名为 tutorial_compiler_flags。
# 使用 INTERFACE 关键字来指定这个目标的作用范围。INTERFACE 表示这个库目标只会应用于依赖它的其他目标，而不会应用于它本身。
add_library(tutorial_compiler_flags INTERFACE)
# target_compile_features 用于为目标设置编译特性（Compile Features）。
# 在这里，我们将编译特性 cxx_std_11 设置为 tutorial_compiler_flags 目标。
# cxx_std_11 表示将C++标准设置为C++11标准，这将影响在编译时使用C++11标准的特性和语法。
target_compile_features(tutorial_compiler_flags INTERFACE cxx_std_11)

# 综合来看，这两行代码的作用是创建一个特殊的库目标 tutorial_compiler_flags，并为这个目标设置编译特性，将C++标准设置为C++11。
# 这个目标通常用于在项目中统一设置编译选项和C++标准，然后通过链接到其他目标，使得这些目标也遵循相同的编译规则和标准。
# 这样可以确保整个项目中的所有目标都使用相同的编译特性和C++标准，从而增强项目的一致性和可移植性。

# configure a header file to pass some of the CMake settings
# to the source code
configure_file(TutorialConfig.h.in TutorialConfig.h)

# add the MathFunctions library
add_subdirectory(MathFunctions)
# list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/MathFunctions")

# add the executable
add_executable(Tutorial tutorial.cpp)

target_link_libraries(Tutorial PUBLIC MathFunctions tutorial_compiler_flags)

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
target_include_directories(Tutorial PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           # ${EXTRA_INCLUDES}
                           )
