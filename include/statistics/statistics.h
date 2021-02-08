/*
* Brian R Taylor
* brian.taylor@bolderflight.com
* 
* Copyright (c) 2021 Bolder Flight Systems
*/

#ifndef INCLUDE_STATISTICS_STATISTICS_H_
#define INCLUDE_STATISTICS_STATISTICS_H_

#include <cmath>
#include <type_traits>
#include "circle_buf/circle_buf.h"

namespace statistics {

/*
* Implements Welford's algorithm for streaming estimation of mean,
* variance, and standard deviation. The constructor initializes
* the class states and the Accum method accumulates new values
* into the estimator. Accessors return the mean, variance,
* and standard deviation estimates. The Clear method resets the,
* class states.
*/
template<typename T>
class Running {
 public:
  static_assert(std::is_floating_point<T>::value,
                "Only floating point types supported");
  Running() : n_(0) {}
  void Update(T x) {
    delta_ = x - m_;
    n_++;
    m_ += delta_ / static_cast<T>(n_);
    m2_ += delta_ * (x - m_);
  }
  T mean() {
    return (n_ > 0) ? m_ : static_cast<T>(0);
  }
  T var() {
    return (n_ > 1) ? m2_ / static_cast<T>((n_ - 1)) : static_cast<T>(0);
  }
  T std() {
    return std::sqrt(var());
  }
  void Clear() {
    n_ = 0;
    m_ = 0;
    m2_ = 0;
  }

 private:
  int n_;
  T m_ = 0;
  T m2_ = 0;
  T delta_;
};

/*
* Implements Welford's algorithm for a moving window estimation of mean,
* variance, and standard deviation. The constructor initializes
* the class states and the Accum method accumulates new values
* into the estimator. Accessors return the mean, variance,
* and standard deviation estimates. The Clear method resets the,
* class states.
*/
template<typename T, std::size_t N>
class MovingWindow {
 public:
  static_assert(std::is_floating_point<T>::value,
                "Only floating point types supported");
  MovingWindow() : n_(0) {}
  void Update(T x) {
    if (n_ < N) {
      Accum(x);
    } else {
      Slide(x);
    }
    buffer_.Write(x);
  }
  T mean() {
    return (n_ > 0) ? m_ : static_cast<T>(0);
  }
  T var() {
    return (n_ > 1) ? m2_ / static_cast<T>((n_ - 1)) : static_cast<T>(0);
  }
  T std() {
    return std::sqrt(var());
  }
  void Clear() {
    n_ = 0;
    m_ = 0;
    m2_ = 0;
    buffer_.Clear();
  }

 private:
  int n_;
  T m_ = 0;
  T m2_ = 0;
  T delta_, x_old_, prev_m_;
  CircularBuffer<T, N> buffer_;
  void Accum(T x) {
    delta_ = x - m_;
    n_++;
    m_ += delta_ / static_cast<T>(n_);
    m2_ += delta_ * (x - m_);
  }
  void Slide(T x) {
    x_old_ = buffer_.Read();
    prev_m_ = m_;
    m_ += (x - x_old_) / static_cast<T>(N);
    m2_ += ((x_old_ - prev_m_) + (x - m_)) * (x - x_old_);
  }
};

}  // namespace statistics

#endif  // INCLUDE_STATISTICS_STATISTICS_H_
