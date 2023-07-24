/*
 * @Author: linkenzone
 * @Date: 2023-07-19 14:11:02
 * @Descripttion: 
 * A simple program that computes the square root of a number
 */

//! 需要非常注意，在vs下编译UTF-8编码的C++文件时，如果注释有中文
//! 会发生诡异的报错，可以把编码改为 UTF-8 with BOW 再编译

//* ===== 指令 =====

//* 在 build 文件夹下执行
//* 构建项目: cmake ..
//* 编译: cmake --build .

//* ================

//* 新增头文件
#include "TutorialConfig.h"

#include <cmath>
// #include <cstdlib> Remove this line
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
  if (argc < 2) {
    // report version
    std::cout << argv[0] << " Version " << Tutorial_VERSION_MAJOR << "."
              << Tutorial_VERSION_MINOR << std::endl;
    std::cout << "Usage: " << argv[0] << " number" << std::endl;
    return 1;
  }

  // convert input to double
  //! const double inputValue = atof(argv[1]);
  const double inputValue = std::stod(argv[1]); //* C++ 11

  // calculate square root
  const double outputValue = sqrt(inputValue);
  std::cout << "The square root of " << inputValue << " is " << outputValue
            << std::endl;
  return 0;
}