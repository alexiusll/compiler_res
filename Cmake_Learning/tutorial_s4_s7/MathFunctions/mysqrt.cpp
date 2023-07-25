/*
 * @Author: linkenzone
 * @Date: 2023-07-24 15:43:50
 * @Descripttion: Do not edit
 */
#include "mysqrt.h"

#include <cmath>
#include <iostream>

namespace mathfunctions
{
  namespace detail
  {
    //* 如果log和exp在系统上可用，则使用它们来计算函数中的平方根mysqrt。
    double mysqrt(double x)
    {
      if (x <= 0)
      {
        return 0;
      }

#if defined(HAVE_LOG) && defined(HAVE_EXP)
      double result = std::exp(std::log(x) * 0.5);
      std::cout << "HAVE_LOG AND HAVE_EXP" << std::endl;
      std::cout << "Computing sqrt of " << x << " to be " << result
                << " using log and exp" << std::endl;
#else
      double result = x;

      // do ten iterations
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
#endif
      return result;
    }
  }
}
