/*
 * @Author: linkenzone
 * @Date: 2023-07-25 13:37:14
 * @Descripttion: Do not edit
 */
#pragma once

//* 在Windows平台上，__declspec(dllexport)是用于导出动态链接库中的符号（函数、类、变量等）的修饰符。
//* 它告诉编译器将符号导出到动态链接库中，以便其他应用程序可以使用。
//* 因此，如果在Windows平台上编译，并且定义了EXPORTING_MYMATH宏，
//* DECLSPEC将被定义为__declspec(dllexport)，表示这个符号将被导出。

//* 在Windows平台上，__declspec(dllimport)是用于导入动态链接库中的符号的修饰符。
//* 它告诉编译器这个符号将从其他地方（通常是动态链接库）导入，而不是在当前编译单元中定义。
//* 因此，如果在Windows平台上编译，但没有定义EXPORTING_MYMATH宏，
//* DECLSPEC将被定义为__declspec(dllimport)，表示这个符号将被导入。

#if defined(_WIN32)
#  if defined(EXPORTING_MYMATH)
#    define DECLSPEC __declspec(dllexport)
#  else
#    define DECLSPEC __declspec(dllimport)
#  endif
#else // non windows
#  define DECLSPEC
#endif

namespace mathfunctions
{
    double DECLSPEC sqrt(double x);
}
