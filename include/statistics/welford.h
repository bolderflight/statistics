/*
* Brian R Taylor
* brian.taylor@bolderflight.com
* 
* Copyright (c) 2020 Bolder Flight Systems
*/

#ifndef INCLUDE_STATISTICS_WELFORD_H_
#define INCLUDE_STATISTICS_WELFORD_H_

#include <cmath>
#include <type_traits>

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
class Welford {
 public:
  static_assert(std::is_floating_point<T>::value, "Only floating point types supported");
  Welford() : n_(0) {}
  void Accum(T x) {
    n_++;
    if (n_ == 1) {
      m_old_ = m_new_ = x;
      s_old_ = s_new_ = 0;
    } else {
      m_new_ = m_old_ + (x - m_old_) / static_cast<T>(n_);
      s_new_ = s_old_ + (x - m_old_) * (x - m_new_);
      m_old_ = m_new_;
      s_old_ = s_new_;
    }
  }
  float mean() {
    return (n_ > 0) ? m_new_ : static_cast<T>(0);
  }
  float var() {
    return (n_ > 1) ? s_new_ / static_cast<T>((n_ - 1)) : static_cast<T>(0);
  }
  float std() {
    return std::sqrt(var());
  }
  void Clear() {
    n_ = 0;
  }

 private:
  int n_;
  T m_old_, m_new_, s_old_, s_new_;
};

}  // namespace statistics

#endif  // INCLUDE_STATISTICS_WELFORD_H_
