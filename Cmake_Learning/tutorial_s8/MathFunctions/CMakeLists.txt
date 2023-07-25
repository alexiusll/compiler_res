add_library(MathFunctions MathFunctions.cpp)

target_include_directories(MathFunctions
                           INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
                           )

option(USE_MYMATH "Use tutorial provided math implementation" ON)
if (USE_MYMATH)
  target_compile_definitions(MathFunctions PRIVATE "USE_MYMATH")

  # generate Table.h
  include(MakeTable.cmake)

  # library that just does sqrt
  add_library(SqrtLibrary STATIC
              mysqrt.cpp
              ${CMAKE_CURRENT_BINARY_DIR}/Table.h
              )

  # state that we depend on our binary dir to find Table.h
  target_include_directories(SqrtLibrary PRIVATE
                            ${CMAKE_CURRENT_BINARY_DIR}
                            )

  target_link_libraries(SqrtLibrary PUBLIC tutorial_compiler_flags)
  target_link_libraries(MathFunctions PRIVATE SqrtLibrary)
endif()

target_link_libraries(MathFunctions PUBLIC tutorial_compiler_flags)

# 增加安装指令
# 定义变量 installable_libs，并将其初始化为包含 MathFunctions 和 tutorial_compiler_flags 这两个目标的列表。
set(installable_libs MathFunctions tutorial_compiler_flags)
# 检查是否存在名为SqrtLibrary的目标。如果存在该目标，则会进入if语句块中执行其中的代码。
if(TARGET SqrtLibrary)
  # 将SqrtLibrary添加到installable_libs列表中。
  list(APPEND installable_libs SqrtLibrary)
endif()

# install命令用于安装 installable_libs 列表中的目标到指定目录（这里是 mylib 目录）。
# ${installable_libs}将会被展开成列表中的目标名称，并且这些目标会被安装到lib目录中。
install(TARGETS ${installable_libs} DESTINATION ${PROJECT_BINARY_DIR}/install/mylib)

# 通过这段代码，MathFunctions.h 头文件将会被安装到指定的 include 目录中。
install(FILES MathFunctions.h DESTINATION ${PROJECT_BINARY_DIR}/install/include)
