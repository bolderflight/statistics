/*
* Brian R Taylor
* brian.taylor@bolderflight.com
* 
* Copyright (c) 2020 Bolder Flight Systems
*/

#include "statistics/statistics.h"
#include <iostream>

int main()
{
  statistics::Running<float> w;
  for (unsigned int i = 0; i < 10; i++) {
    w.Update((float) i);
  }
  std::cout << "Mean: " << w.mean() << std::endl; // 4.5
  std::cout << "Variance: " << w.var() << std::endl; // 9.1667
  std::cout << "Standard Deviation: " << w.std() << std::endl; // 3.0277

  statistics::MovingWindow<float, 3> m;
  for (unsigned int i = 0; i < 10; i++) {
    m.Update((float) i);
    std::cout << m.mean() << "\t";
    std::cout << m.var() << "\t";
    std::cout << m.std() << std::endl;
  }
  return 0;
}
