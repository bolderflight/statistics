/*
* Brian R Taylor
* brian.taylor@bolderflight.com
* 
* Copyright (c) 2019 Bolder Flight Systems
*/

#include "statistics/statistics.h"
#include "gtest/gtest.h"

/* Test the default constructor */
TEST(Welford, DefaultConstructor) {
  statistics::Welford welford;
  EXPECT_EQ(0, welford.GetMean());
  EXPECT_EQ(0, welford.GetVar());
  EXPECT_EQ(0, welford.GetStd());
}
/* Accumlate 1 sample and test */
TEST(Welford, OneSample) {
  statistics::Welford welford;
  welford.Accum(1.0f);
  EXPECT_EQ(1, welford.GetMean());
  EXPECT_EQ(0, welford.GetVar());
  EXPECT_EQ(0, welford.GetStd());
}
/* Accumlate a few samples and test */
TEST(Welford, ThreeSample) {
  statistics::Welford welford;
  welford.Accum(1);
  welford.Accum(2);
  welford.Accum(3);
  EXPECT_FLOAT_EQ(2, welford.GetMean());
  EXPECT_FLOAT_EQ(1, welford.GetVar());
  EXPECT_FLOAT_EQ(1, welford.GetStd());
}
/* Accumlate ten samples and test */
TEST(Welford, TenSample) {
  statistics::Welford welford;
  for (unsigned int i = 0; i < 10; i++) {
    welford.Accum(i);
  }
  EXPECT_FLOAT_EQ(4.5, welford.GetMean());
  EXPECT_FLOAT_EQ(9.166666666666666, welford.GetVar());
  EXPECT_FLOAT_EQ(3.027650354097492, welford.GetStd());
}
/* Test the clear method */
TEST(Welford, Clear) {
  statistics::Welford welford;
  for (unsigned int i = 0; i < 10; i++) {
    welford.Accum(i);
  }
  welford.Clear();
  welford.Accum(1);
  welford.Accum(2);
  welford.Accum(3);
  EXPECT_FLOAT_EQ(2, welford.GetMean());
  EXPECT_FLOAT_EQ(1, welford.GetVar());
  EXPECT_FLOAT_EQ(1, welford.GetStd());
}
