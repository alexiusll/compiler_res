
# cmake_minimum_required()至少需要 CMake 版本3.15
cmake_minimum_required(VERSION 3.15)

project(Tutorial VERSION 2.33)

add_library(tutorial_compiler_flags INTERFACE)
target_compile_features(tutorial_compiler_flags INTERFACE cxx_std_17)

# 条件生成表达式$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>
# 用于确定当前编译环境是否为CXX（C++编译器）且属于ARMClang、AppleClang、Clang、GNU或LCC之一。
# 如果条件满足，则变量gcc_like_cxx被设置为true，否则设置为false。
set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>")

# 条件生成表达式$<COMPILE_LANG_AND_ID:CXX,MSVC>
# 用于确定当前编译环境是否为CXX（C++编译器）且为MSVC（Microsoft Visual C++编译器）。
# 如果条件满足，则变量msvc_cxx被设置为true，否则设置为false。
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")

# target_compile_options() 用于设置目标的编译选项
# 使用INTERFACE关键字，表示这些选项将传递给依赖 tutorial_compiler_flags 的其他目标
# "-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused": 这是GCC-like编译器的一组编译选项。
# --- "其中-Wall表示开启所有警告，-Wextra表示开启额外的警告，-Wshadow表示开启对变量隐藏的警告，
# --- "-Wformat=2表示开启严格格式化字符串检查，-Wunused表示开启未使用变量的警告。
# "-W3": 这是MSVC编译器的编译选项，表示开启所有警告（Warning Level 3）。
# 条件表达式
# --- 如果使用的是GCC-like编译器，那么开启一组警告选项；
# --- 如果使用的是MSVC编译器，那么开启所有警告（Warning Level 3）。
# BUILD_INTERFACE
# --- $<BUILD_INTERFACE:...> 中的BUILD_INTERFACE表示在构建目标时（编译目标时）使用这些选项。
target_compile_options(tutorial_compiler_flags INTERFACE
  "$<${gcc_like_cxx}:$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused>>"
  "$<${msvc_cxx}:$<BUILD_INTERFACE:-W4>>"   # 体现在 vs中的 警告等级 选项
)

configure_file(TutorialConfig.h.in TutorialConfig.h)

add_subdirectory(MathFunctions)

add_executable(Tutorial tutorial.cpp)

# （这里感觉 tutorial_compiler_flags 是可以删除的）
# target_link_libraries(Tutorial PUBLIC MathFunctions tutorial_compiler_flags)
target_link_libraries(Tutorial PUBLIC MathFunctions)

target_include_directories(Tutorial PUBLIC "${PROJECT_BINARY_DIR}")

# Tutorial 目标将会被安装到指定的 bin 目录中。
# 这样，在项目安装后，用户可以在该目录中找到并运行生成的可执行文件或使用库文件。
install(TARGETS Tutorial DESTINATION bin)

# TutorialConfig.h 头文件（通常是由 CMake 生成的配置头文件）将会被安装到指定的 include 目录中。
install(FILES "${PROJECT_BINARY_DIR}/TutorialConfig.h" DESTINATION include)

# enable_testing()函数用于启用项目的测试功能。
# enable_testing()

# 替换为这个
include(CTest)

# add_test 是CMake的一个命令，用于添加一个测试。
# NAME Runs：这里设置了测试的名称为"Runs"。
# COMMAND Tutorial 25：这是要运行的测试命令。在这里，测试命令为"Tutorial 25"，
# 表示运行名为"Tutorial"的可执行文件，并将"25"作为该可执行文件的参数。
add_test(NAME Runs COMMAND Tutorial 25)


add_test(NAME Usage COMMAND Tutorial)
# set_tests_properties是CMake的一个命令，用于设置测试的属性。
# Usage：这里指定要设置属性的测试名称，即"Usage"。
# PROPERTIES PASS_REGULAR_EXPRESSION "Usage:.*number"：这是要设置的测试属性。
# 在这里，通过PASS_REGULAR_EXPRESSION属性设置了一个正则表达式，用于检查测试的输出结果是否包含指定的字符串模式。
# 正则表达式"Usage:.*number"表示测试输出应包含"Usage:"和"number"之间的任意字符。
set_tests_properties(Usage
  PROPERTIES PASS_REGULAR_EXPRESSION "Usage:.*number"
  )

add_test(NAME StandardUse COMMAND Tutorial 4)
set_tests_properties(StandardUse
  PROPERTIES PASS_REGULAR_EXPRESSION "4 is 2"
  )

# 这是一个CMake函数的定义。function关键字指定了函数的开始，endfunction关键字指定了函数的结束。
# 函数名为do_test，它有三个参数：target、arg和result，
# 分别表示测试的目标（通常是可执行文件的名称）、测试的参数和预期的测试结果。
function(do_test target arg result)
add_test(NAME Comp${arg} COMMAND ${target} ${arg})
set_tests_properties(Comp${arg}
  PROPERTIES PASS_REGULAR_EXPRESSION ${result}
  )
endfunction()

do_test(Tutorial 4 "4 is 2")
do_test(Tutorial 9 "9 is 3")
do_test(Tutorial 5 "5 is 2.236")
do_test(Tutorial 7 "7 is 2.645")
do_test(Tutorial 25 "25 is 5")
do_test(Tutorial -25 "-25 is (-nan|nan|0)")
do_test(Tutorial 0.0001 "0.0001 is 0.01")

# 接下来假设我们想要将我们的项目分发给其他人以便他们可以使用它。我们希望在各种平台上提供二进制和源代码发行版。
# 首先引入 InstallRequiredSystemLibraries。该模块将包括当前平台项目所需的任何运行时库。
include(InstallRequiredSystemLibraries)
# 这行代码设置了项目的授权许可文件。
# 它指定了授权许可文件的路径为${CMAKE_CURRENT_SOURCE_DIR}/License.txt，这个文件将包含在生成的安装包中，供用户查阅项目的授权许可信息。
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
# 这两行代码设置了项目的版本号。${Tutorial_VERSION_MAJOR}和${Tutorial_VERSION_MINOR}是之前定义的变量，
# 用于指定项目的主版本号和次版本号。这些版本号将被用于生成安装包的文件名和版本标识。
set(CPACK_PACKAGE_VERSION_MAJOR "${Tutorial_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${Tutorial_VERSION_MINOR}")
# 这行代码设置了项目的源码打包生成器。在这里，指定了使用TGZ格式（tar.gz）来打包源代码。
set(CPACK_SOURCE_GENERATOR "TGZ")
# 这行代码包含了CPack模块，启用CPack打包功能。
# CPack是CMake的一个模块，用于根据配置的打包选项生成安装包。通过包含CPack模块，我们可以使用CPack的打包功能来生成项目的安装包。
include(CPack)