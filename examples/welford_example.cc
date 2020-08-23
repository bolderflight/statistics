/*
* Brian R Taylor
* brian.taylor@bolderflight.com
* 
* Copyright (c) 2019 Bolder Flight Systems
*/

#include "statistics/statistics.h"
#include <iostream>

int main()
{
  statistics::Welford<float> w;
  for (unsigned int i = 0; i < 10; i++) {
    w.Accum((float) i);
  }
  std::cout << "Mean: " << w.mean() << std::endl; // 4.5
  std::cout << "Variance: " << w.var() << std::endl; // 9.1667
  std::cout << "Standard Deviation: " << w.std() << std::endl; // 3.0277
  return 0;
}
