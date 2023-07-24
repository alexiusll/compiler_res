#include "MathFunctions.h"

#include <cmath>
#include <iostream>

#ifdef USE_MYMATH
#  include "mysqrt.h"
#endif

namespace mathfunctions
{
  double sqrt(double x)
  {
#ifdef USE_MYMATH
    printf("使用内建库: detail::mysqrt(x)");
    return detail::mysqrt(x);
#else
    printf("不使用内建库: std::sqrt(x)");
    return std::sqrt(x);
#endif
  }
}
