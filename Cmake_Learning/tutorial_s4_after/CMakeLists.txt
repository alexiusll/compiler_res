
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
