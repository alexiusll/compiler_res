﻿/*
 * @Author: linkenzone
 * @Date: 2023-07-24 15:44:55
 * @Descripttion: Do not edit
 */
#include "mysqrt.h"

#include <iostream>

namespace mathfunctions
{
  namespace detail
  {
    // a hack square root calculation using simple operations
    double mysqrt(double x)
    {
      if (x <= 0)
      {
        return 0;
      }

      double result = x;

      // 进行十次迭代
      for (int i = 0; i < 10; ++i)
      {
        if (result <= 0)
        {
          result = 0.1;
        }
        double delta = x - (result * result);
        result = result + 0.5 * delta / result;
        std::cout << "Computing sqrt of " << x << " to be " << result << std::endl;
      }
      return result;
    }
  }
}
