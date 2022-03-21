/*
* Brian R Taylor
* brian.taylor@bolderflight.com
* 
* Copyright (c) 2022 Bolder Flight Systems Inc
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

#ifndef STATISTICS_SRC_STATISTICS_H_
#define STATISTICS_SRC_STATISTICS_H_

/* Arduino IDE built */
#if defined(ARDUINO)
#include <Arduino.h>
#endif
#include <cstddef>
#include <cstdint>
#include <cmath>
#include <type_traits>
#include "circle_buf.h"  // NOLINT

namespace bfs {
/*
* Implements Welford's algorithm for streaming estimation of mean,
* variance, and standard deviation. The constructor initializes
* the class states and the Accum method accumulates new values
* into the estimator. Accessors return the mean, variance,
* and standard deviation estimates. The Clear method resets the,
* class states.
*/
template<typename T>
class RunningStats {
 public:
  static_assert(std::is_floating_point<T>::value,
                "Only floating point types supported");
  RunningStats() : n_(0) {}
  void Update(const T x) {
    delta_ = x - m_;
    n_++;
    m_ += delta_ / static_cast<T>(n_);
    m2_ += delta_ * (x - m_);
  }
  inline T mean() const {
    return (n_ > 0) ? m_ : static_cast<T>(0);
  }
  inline T var() const {
    return (n_ > 1) ? m2_ / static_cast<T>((n_ - 1)) : static_cast<T>(0);
  }
  inline T std() const {
    return std::sqrt(var());
  }
  void Clear() {
    n_ = 0;
    m_ = 0;
    m2_ = 0;
  }

 private:
  std::size_t n_;
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
class MovingWindowStats {
 public:
  static_assert(std::is_floating_point<T>::value,
                "Only floating point types supported");
  MovingWindowStats() : n_(0) {}
  void Update(const T x) {
    if (n_ < N) {
      Accum(x);
    } else {
      Slide(x);
    }
    buffer_.Write(x);
  }
  inline T mean() const {
    return (n_ > 0) ? m_ : static_cast<T>(0);
  }
  inline T var() const {
    return (n_ > 1) ? m2_ / static_cast<T>((n_ - 1)) : static_cast<T>(0);
  }
  inline T std() const {
    return std::sqrt(var());
  }
  void Clear() {
    n_ = 0;
    m_ = 0;
    m2_ = 0;
    buffer_.Clear();
  }

 private:
  std::size_t n_;
  T m_ = 0;
  T m2_ = 0;
  T delta_, x_old_, prev_m_;
  CircleBuf<T, N> buffer_;
  void Accum(const T x) {
    delta_ = x - m_;
    n_++;
    m_ += delta_ / static_cast<T>(n_);
    m2_ += delta_ * (x - m_);
  }
  void Slide(const T x) {
    x_old_ = buffer_.Read();
    prev_m_ = m_;
    m_ += (x - x_old_) / static_cast<T>(N);
    m2_ += ((x_old_ - prev_m_) + (x - m_)) * (x - x_old_);
  }
};

}  // namespace bfs

#endif  // SRC_STATISTICS_H_
