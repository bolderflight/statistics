/*
* Brian R Taylor
* brian.taylor@bolderflight.com
* 
* Copyright (c) 2019 Bolder Flight Systems
*/

#include "welford/welford.h"
#include <iostream>

int main()
{
  Welford w;
  for (unsigned int i = 0; i < 10; i++) {
    w.Accum((float) i);
  }
  std::cout << "Mean: " << w.GetMean() << std::endl; // 4.5
  std::cout << "Variance: " << w.GetVar() << std::endl; // 9.1667
  std::cout << "Standard Deviation: " << w.GetStd() << std::endl; // 3.0277
  return 0;
}
