/*
* Brian R Taylor
* brian.taylor@bolderflight.com
* 
* Copyright (c) 2019 Bolder Flight Systems
*/

#ifndef STATISTICS_H
#define STATISTICS_H

#include <stdlib.h>

/*
* A collection of statistics related functions and classes
*/

namespace statistics {

/*
* Implements Welford's algorithm for streaming estimation of mean,
* variance, and standard deviation. The constructor initializes
* the class states and the Accum method accumulates new values
* into the estimator. Get accessors return the mean, variance,
* and standard deviation estimates. The Clear method resets the,
* class states.
*/
class Welford {
  public:
    Welford();
    void Accum(float x);
    float GetMean();
    float GetVar();
    float GetStd();
    void Clear();
  private:
    unsigned int n_;
    float m_old_, m_new_, s_old_, s_new_;
};

} // statistics

#endif
