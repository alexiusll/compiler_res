/*
 * @Author: linkenzone
 * @Date: 2023-07-24 15:43:50
 * @Descripttion: Do not edit
 */

#include "MathFunctions.h"

#include <cmath>
#include <iostream>

#ifdef USE_MYMATH
#  include "mysqrt.h"
#endif

namespace mathfunctions {
double sqrt(double x)
{
// which square root function should we use?
#ifdef USE_MYMATH
  printf("使用内建库: detail::mysqrt(x)\n");
  return detail::mysqrt(x);
#else
  printf("不使用内建库: std::sqrt(x)\n");
  return std::sqrt(x);
#endif
}
}
