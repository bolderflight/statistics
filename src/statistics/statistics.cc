/*
* Brian R Taylor
* brian.taylor@bolderflight.com
* 
* Copyright (c) 2019 Bolder Flight Systems
*/

#include "statistics/statistics.h"
#include <math.h>

namespace statistics {

Welford::Welford() {
  n_ = 0;
}

void Welford::Accum(float x)  {
  n_++;
  if (n_ == 1) {
    m_old_ = m_new_ = x;
    s_old_ = s_new_ = 0;
  } else {
    m_new_ = m_old_ + (x - m_old_) / static_cast<float>(n_);
    s_new_ = s_old_ + (x - m_old_) * (x - m_new_);
    m_old_ = m_new_;
    s_old_ = s_new_;
  }
}

float Welford::mean() {
  return (n_ > 0) ? m_new_ : 0.0f;
}

float Welford::var() {
  return (n_ > 1) ? s_new_ / static_cast<float>((n_ - 1)) : 0.0f;
}

float Welford::std() {
  return sqrtf(var());
}

void Welford::Clear() {
  n_ = 0;
}

}  // namespace statistics
