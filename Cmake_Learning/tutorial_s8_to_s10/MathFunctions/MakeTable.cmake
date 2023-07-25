# first we add the executable that generates the table
# 将MakeTable.cpp编译为MakeTable可执行文件，并在项目构建后得到可执行文件MakeTable，用于后续执行或测试。
add_executable(MakeTable MakeTable.cpp)
target_link_libraries(MakeTable PRIVATE tutorial_compiler_flags)

# add the command to generate the source code

# add_custom_command()是CMake的一个指令，用于定义自定义构建命令。
# OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/Table.h：
# --- 指定生成的输出文件为${CMAKE_CURRENT_BINARY_DIR}/Table.h，即${CMAKE_CURRENT_BINARY_DIR}目录下的Table.h文件。
# COMMAND MakeTable ${CMAKE_CURRENT_BINARY_DIR}/Table.h：
# --- 指定要执行的命令。在这里，MakeTable是一个可执行文件，${CMAKE_CURRENT_BINARY_DIR}/Table.h是作为该可执行文件的参数传递给它。
# --- 这表示将运行名为MakeTable的可执行文件，并生成Table.h头文件。
# DEPENDS MakeTable：指定构建命令的依赖项。
# --- 在这里，指定了MakeTable作为依赖项。这意味着在运行构建命令之前，CMake会先确保MakeTable已经构建完成或可用。

add_custom_command(
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/Table.h
  COMMAND MakeTable ${CMAKE_CURRENT_BINARY_DIR}/Table.h
  DEPENDS MakeTable
  )
