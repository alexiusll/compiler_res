add_library(MathFunctions MathFunctions.cpp)

# INTERFACE: 这是一个关键字，用于指定包含目录的作用范围。
# 在这里，INTERFACE 表示这个包含目录将会传递给依赖于 MathFunctions 的其他目标，但不会应用于 MathFunctions 本身。
# ${CMAKE_CURRENT_SOURCE_DIR}: 这是一个CMake变量，表示当前CMakeLists.txt文件所在的源代码目录的路径。
# 在这里，我们将当前源代码目录添加到 MathFunctions 这个库的包含目录中。
target_include_directories(MathFunctions
                           INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
                           )

# should we use our own math functions
option(USE_MYMATH "Use tutorial provided math implementation" ON)
if (USE_MYMATH)
  target_compile_definitions(MathFunctions PRIVATE "USE_MYMATH")

  # library that just does sqrt
  add_library(SqrtLibrary STATIC
              mysqrt.cpp
              )

  target_link_libraries(SqrtLibrary PUBLIC tutorial_compiler_flags)
  target_link_libraries(MathFunctions PUBLIC SqrtLibrary)
endif()

target_link_libraries(SqrtLibrary PUBLIC tutorial_compiler_flags)
