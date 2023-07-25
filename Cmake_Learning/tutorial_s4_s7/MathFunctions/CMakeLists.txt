add_library(MathFunctions MathFunctions.cpp)

target_include_directories(MathFunctions
                           INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
                           )

option(USE_MYMATH "Use tutorial provided math implementation" ON)
if (USE_MYMATH)
  target_compile_definitions(MathFunctions PRIVATE "USE_MYMATH")

  add_library(SqrtLibrary STATIC mysqrt.cpp)

  target_link_libraries(SqrtLibrary PUBLIC tutorial_compiler_flags)

  # 该命令用于引入CheckCXXSourceCompiles模块，该模块包含了check_cxx_source_compiles()函数。
  include(CheckCXXSourceCompiles)
  # 使用check_cxx_source_compiles()函数检查目标平台是否支持<cmath>头文件中的log和exp函数。
  # HAVE_LOG：这是一个用于存储编译结果的变量名。
  # --- check_cxx_source_compiles()函数将会尝试编译...log code...的代码，并将编译结果存储在名为HAVE_LOG的变量中。
  # --- 如果目标平台支持<cmath>头文件中的log函数，则HAVE_LOG变量将会设置为TRUE；否则，设置为FALSE。
  # HAVE_EXP：这是另一个用于存储编译结果的变量名。
  # --- check_cxx_source_compiles()函数将会尝试编译...exp code...的代码，并将编译结果存储在名为HAVE_EXP的变量中。
  # --- 如果目标平台支持<cmath>头文件中的exp函数，则HAVE_EXP变量将会设置为TRUE；否则，设置为FALSE。
  check_cxx_source_compiles("
    #include <cmath>
    int main() {
      std::log(1.0);
      return 0;
    }
  " HAVE_LOG)
  check_cxx_source_compiles("
    #include <cmath>
    int main() {
      std::exp(1.0);
      return 0;
    }
  " HAVE_EXP)

  # 使用target_compile_definitions()指定 HAVE_LOG和HAVE_EXP作为PRIVATE编译定义
  if(HAVE_LOG AND HAVE_EXP)
  target_compile_definitions(SqrtLibrary
                             PRIVATE "HAVE_LOG" "HAVE_EXP"
                             )
  endif()

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
