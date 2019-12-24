/*
* Brian R Taylor
* brian.taylor@bolderflight.com
* 
* Copyright (c) 2019 Bolder Flight Systems
*/

#include "welford/welford.h"
#include <math.h>

Welford::Welford()
{
  n_ = 0;
}

void Welford::Accum(float x) 
{
  n_++;
  if (n_ == 1) {
    m_old_ = m_new_ = x;
    s_old_ = s_new_ = 0;
  } else {
    m_new_ = m_old_ + (x - m_old_) / ((float) n_);
    s_new_ = s_old_ + (x - m_old_) * (x - m_new_);
    m_old_ = m_new_;
    s_old_ = s_new_;
  }
}

float Welford::GetMean() 
{
  return (n_ > 0) ? m_new_ : 0.0f;
}

float Welford::GetVar() 
{
  return (n_ > 1) ? s_new_ / ((float) (n_ - 1)) : 0.0f;
}

float Welford::GetStd()
{
  return sqrtf(GetVar());
}

void Welford::Clear()
{
  n_ = 0;
}
