/*
* Brian R Taylor
* brian.taylor@bolderflight.com
* 
* Copyright (c) 2021 Bolder Flight Systems Inc
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the “Software”), to
* deal in the Software without restriction, including without limitation the
* rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
* sell copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
* IN THE SOFTWARE.
*/

#include "statistics.h"
#include <iostream>

int main()
{
  bfs::RunningStats<float> w;
  for (unsigned int i = 0; i < 10; i++) {
    w.Update((float) i);
  }
  std::cout << "Mean: " << w.mean() << std::endl; // 4.5
  std::cout << "Variance: " << w.var() << std::endl; // 9.1667
  std::cout << "Standard Deviation: " << w.std() << std::endl; // 3.0277

  bfs::MovingWindowStats<float, 3> m;
  for (unsigned int i = 0; i < 10; i++) {
    m.Update((float) i);
    std::cout << m.mean() << "\t";
    std::cout << m.var() << "\t";
    std::cout << m.std() << std::endl;
  }
  return 0;
}
