# 用于创建一个库（Library）目标。
# 在这个命令中，MathFunctions 是库的名称，MathFunctions.cpp 和 mysqrt.cpp 是库的源代码文件。
add_library(MathFunctions MathFunctions.cpp)

# 该选项将显示在cmake-gui和 ccmake其默认值ON可由用户更改。
option(USE_MYMATH "Use tutorial provided math implementation" ON)

if (USE_MYMATH)
# 为目标设置编译定义（compile definitions）
# PRIVATE 表示这个编译定义只会应用于 MathFunctions 这个目标自身，不会传递给依赖于它的其他目标。
# "USE_MYMATH": 这是要设置的编译定义，表示定义一个名为 USE_MYMATH 的预处理变量。
  target_compile_definitions(MathFunctions PRIVATE "USE_MYMATH")
endif()

add_library(SqrtLibrary STATIC mysqrt.cpp)

target_link_libraries(MathFunctions PUBLIC SqrtLibrary)
