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
  statistics::Welford<float> welford;
  EXPECT_EQ(0, welford.mean());
  EXPECT_EQ(0, welford.var());
  EXPECT_EQ(0, welford.std());
}
/* Accumlate 1 sample and test */
TEST(Welford, OneSample) {
  statistics::Welford<float> welford;
  welford.Accum(1.0f);
  EXPECT_EQ(1, welford.mean());
  EXPECT_EQ(0, welford.var());
  EXPECT_EQ(0, welford.std());
}
/* Accumlate a few samples and test */
TEST(Welford, ThreeSample) {
  statistics::Welford<float> welford;
  welford.Accum(1);
  welford.Accum(2);
  welford.Accum(3);
  EXPECT_FLOAT_EQ(2, welford.mean());
  EXPECT_FLOAT_EQ(1, welford.var());
  EXPECT_FLOAT_EQ(1, welford.std());
}
/* Accumlate ten samples and test */
TEST(Welford, TenSample) {
  statistics::Welford<float> welford;
  for (unsigned int i = 0; i < 10; i++) {
    welford.Accum(i);
  }
  EXPECT_FLOAT_EQ(4.5, welford.mean());
  EXPECT_FLOAT_EQ(9.166666666666666, welford.var());
  EXPECT_FLOAT_EQ(3.027650354097492, welford.std());
}
/* Test the clear method */
TEST(Welford, Clear) {
  statistics::Welford<float> welford;
  for (unsigned int i = 0; i < 10; i++) {
    welford.Accum(i);
  }
  welford.Clear();
  welford.Accum(1);
  welford.Accum(2);
  welford.Accum(3);
  EXPECT_FLOAT_EQ(2, welford.mean());
  EXPECT_FLOAT_EQ(1, welford.var());
  EXPECT_FLOAT_EQ(1, welford.std());
}
