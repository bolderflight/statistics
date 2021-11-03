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
#include "gtest/gtest.h"

/* Test the default constructor */
TEST(Running, DefaultConstructor) {
  bfs::RunningStats<float> stats;
  EXPECT_EQ(0, stats.mean());
  EXPECT_EQ(0, stats.var());
  EXPECT_EQ(0, stats.std());
}
/* Accumlate 1 sample and test */
TEST(Running, OneSample) {
  bfs::RunningStats<float> stats;
  stats.Update(1.0f);
  EXPECT_EQ(1, stats.mean());
  EXPECT_EQ(0, stats.var());
  EXPECT_EQ(0, stats.std());
}
/* Accumlate a few samples and test */
TEST(Running, ThreeSample) {
  bfs::RunningStats<float> stats;
  stats.Update(1);
  stats.Update(2);
  stats.Update(3);
  EXPECT_FLOAT_EQ(2, stats.mean());
  EXPECT_FLOAT_EQ(1, stats.var());
  EXPECT_FLOAT_EQ(1, stats.std());
}
/* Accumlate ten samples and test */
TEST(Running, TenSample) {
  bfs::RunningStats<float> stats;
  for (unsigned int i = 0; i < 10; i++) {
    stats.Update(i);
  }
  EXPECT_FLOAT_EQ(4.5, stats.mean());
  EXPECT_FLOAT_EQ(9.166666666666666, stats.var());
  EXPECT_FLOAT_EQ(3.027650354097492, stats.std());
}
/* Test the clear method */
TEST(Running, Clear) {
  bfs::RunningStats<float> stats;
  for (unsigned int i = 0; i < 10; i++) {
    stats.Update(i);
  }
  stats.Clear();
  stats.Update(1);
  stats.Update(2);
  stats.Update(3);
  EXPECT_FLOAT_EQ(2, stats.mean());
  EXPECT_FLOAT_EQ(1, stats.var());
  EXPECT_FLOAT_EQ(1, stats.std());
}
/* Test the default constructor */
TEST(MovingWindow, DefaultConstructor) {
  bfs::MovingWindowStats<float, 3> stats;
  EXPECT_EQ(0, stats.mean());
  EXPECT_EQ(0, stats.var());
  EXPECT_EQ(0, stats.std());
}
/* Accumulate some data */
TEST(MovingWindow, Samples) {
  double A[] = {
    -39.92747116088867,
    -39.94376373291016,
    -39.99928665161133,
    -40.01724624633789,
    -40.035888671875,
    -40.05497741699219,
    -40.07429122924805,
    -40.12143325805664,
    -40.14137649536133,
    -40.16115188598633
  };
  /* 
  * mean, variance, and standard deviation from Octave movmean, movvar, and
  * movstd functions with window size 3 (i.e. movmean(a, [2, 0]))
  */
  double m[] = {
    -39.92747116088867,
    -39.93561744689941,
    -39.95684051513672,
    -39.98676554361979,
    -40.01747385660807,
    -40.03603744506836,
    -40.05505243937174,
    -40.08356730143229,
    -40.11236699422201,
    -40.1413205464681
  };
  double v[] = {
    0,
    0.0001327239515377435,
    0.001417617851984594,
    0.001467503553915774,
    0.000334965826671881,
    0.0003559269098332152,
    0.0003686933244656151,
    0.001168628839271453,
    0.001186756087311854,
    0.0003943946988632282
  };
  double s[] = {
    0,
    0.01152058815936684,
    0.03765126627332199,
    0.03830800900485137,
    0.01830207164973083,
    0.01886602527914174,
    0.01920138860774437,
    0.03418521375202228,
    0.03444932636949312,
    0.01985937307326765
  };
  bfs::MovingWindowStats<double, 3> stats;
  for (int i = 0; i < 10; i++) {
    stats.Update(A[i]);
    EXPECT_FLOAT_EQ(m[i], stats.mean());
    EXPECT_FLOAT_EQ(v[i], stats.var());
    EXPECT_FLOAT_EQ(s[i], stats.std());
  }
}
/* Test clear */
TEST(MovingWindow, Clear) {
  double A[] = {
    -39.92747116088867,
    -39.94376373291016,
    -39.99928665161133,
    -40.01724624633789,
    -40.035888671875,
    -40.05497741699219,
    -40.07429122924805,
    -40.12143325805664,
    -40.14137649536133,
    -40.16115188598633
  };
  /* 
  * mean, variance, and standard deviation from Octave movmean, movvar, and
  * movstd functions with window size 3 (i.e. movmean(a, [2, 0]))
  */
  double m[] = {
    -39.92747116088867,
    -39.93561744689941,
    -39.95684051513672,
    -39.98676554361979,
    -40.01747385660807,
    -40.03603744506836,
    -40.05505243937174,
    -40.08356730143229,
    -40.11236699422201,
    -40.1413205464681
  };
  double v[] = {
    0,
    0.0001327239515377435,
    0.001417617851984594,
    0.001467503553915774,
    0.000334965826671881,
    0.0003559269098332152,
    0.0003686933244656151,
    0.001168628839271453,
    0.001186756087311854,
    0.0003943946988632282
  };
  double s[] = {
    0,
    0.01152058815936684,
    0.03765126627332199,
    0.03830800900485137,
    0.01830207164973083,
    0.01886602527914174,
    0.01920138860774437,
    0.03418521375202228,
    0.03444932636949312,
    0.01985937307326765
  };
  bfs::MovingWindowStats<double, 3> stats;
  for (int i = 0; i < 10; i++) {
    stats.Update(A[i]);
    EXPECT_FLOAT_EQ(m[i], stats.mean());
    EXPECT_FLOAT_EQ(v[i], stats.var());
    EXPECT_FLOAT_EQ(s[i], stats.std());
  }
  stats.Clear();
  for (int i = 0; i < 10; i++) {
    stats.Update(A[i]);
    EXPECT_FLOAT_EQ(m[i], stats.mean());
    EXPECT_FLOAT_EQ(v[i], stats.var());
    EXPECT_FLOAT_EQ(s[i], stats.std());
  }
}
