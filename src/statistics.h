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

#ifndef SRC_STATISTICS_H_
#define SRC_STATISTICS_H_

/* Arduino IDE built */
#if defined(ARDUINO) && !defined(__CMAKE__)
/* Arduino AVR board */
#if defined(__AVR__)
#include <Arduino.h>
/* Arduino ARM board */
#else
#include <Arduino.h>
#include <cmath>
#include <type_traits>
#define __TYPE_TRAITS__
#define __STD_SQRT__
#endif
/* Built by CMake or used in another build system */
#else
#include <stdint.h>
#include <cmath>
#include <type_traits>
#define __TYPE_TRAITS__
#define __STD_SQRT__
#endif
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
  #if defined(__TYPE_TRAITS__)
  static_assert(std::is_floating_point<T>::value,
                "Only floating point types supported");
  #endif
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
    #if defined(__STD_SQRT__)
    return std::sqrt(var());
    #else
    return Sqrt_(var());
    #endif
  }
  void Clear() {
    n_ = 0;
    m_ = 0;
    m2_ = 0;
  }

 private:
  size_t n_;
  T m_ = 0;
  T m2_ = 0;
  T delta_;
  /* Define our own std::sqrt, if not available */
  #if !defined(__STD_SQRT__)
  inline float Sqrt_(float val) const {return sqrtf(val);}
  inline double Sqrt_(double val) const {return sqrt(val);}
  inline long double Sqrt_(long double val) const {return sqrtl(val);}
  #endif
};

/*
* Implements Welford's algorithm for a moving window estimation of mean,
* variance, and standard deviation. The constructor initializes
* the class states and the Accum method accumulates new values
* into the estimator. Accessors return the mean, variance,
* and standard deviation estimates. The Clear method resets the,
* class states.
*/
template<typename T, size_t N>
class MovingWindowStats {
 public:
  #if defined(__TYPE_TRAITS__)
  static_assert(std::is_floating_point<T>::value,
                "Only floating point types supported");
  #endif
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
    #if defined(__STD_SQRT__)
    return std::sqrt(var());
    #else
    return Sqrt_(var());
    #endif
  }
  void Clear() {
    n_ = 0;
    m_ = 0;
    m2_ = 0;
    buffer_.Clear();
  }

 private:
  size_t n_;
  T m_ = 0;
  T m2_ = 0;
  T delta_, x_old_, prev_m_;
  CircularBuffer<T, N> buffer_;
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
  /* Define our own std::sqrt, if not available */
  #if !defined(__STD_SQRT__)
  inline float Sqrt_(float val) const {return sqrtf(val);}
  inline double Sqrt_(double val) const {return sqrt(val);}
  inline long double Sqrt_(long double val) const {return sqrtl(val);}
  #endif
};

}  // namespace bfs

#endif  // SRC_STATISTICS_H_
