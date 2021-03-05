# Statistics
This library contains statistics functions and classes.
   * [License](LICENSE.md)
   * [Changelog](CHANGELOG.md)
   * [Contributing guide](CONTRIBUTING.md)

## Installation
CMake is used to build this library, which is exported as a library target called *statistics*. The header is added as:

```
#include "statistics/statistics.h"
```

The library can be also be compiled stand-alone using the CMake idiom of creating a *build* directory and then, from within that directory issuing:

```
cmake ..
make
```

This will build the library, an example executable called *stats_example*, and an executable for testing using the Google Test framework, called *stats_test*. The example executable source file is located at *examples/stats_example.cc*.

## Namespace
This library is within the namespace *bfs*.

# RunningStats
This class implements Welford's method for streaming estimation of mean, variance, and standard deviation. The class is templated to support floating point types.

## Methods

**RunningStats()** Creates a *RunningStats* object and initializes the estimator states.

```C++
bfs::RunningStats<float> stats;
```

**void Update(T x)** Accumulates data into the estimator.

```C++
for (unsigned int i = 0; i < 10; i++) {
  stats.Update((float) i);
}
```

**T mean()** Returns the current estimate of the mean of the accumulated data.

```C++
std::cout << stats.mean() << std::endl; // 4.5
```

**T var()** Returns the current estimate of the variance of the accumulated data.

```C++
std::cout << stats.var() << std::endl; // 9.1667
```

**T std()** Returns the current estimate of the standard deviation of the accumulated data.

```C++
std::cout << stats.std() << std::endl; // 3.0277
```

**void Clear()** Resets the estimator states.

```C++
stats.Clear();
```

# MovingWindowStats
This class implements a modification of Welford's method for a moving window estimation of mean, variance, and standard deviation. The class is templated to support floating point types and window sizes. Estimates are always performed looking back from the current value.

## Methods

**MovingWindowStats()** Creates a *MovingWindowStats* object and initializes the estimator states.

```C++
/* A moving window estimator operating on floats with a window size of 250 values */
bfs::MovingWindowStats<float, 250> stats;
```

**void Update(T x)** Accumulates data into the estimator, slides the window after the window is filled.

```C++
stats.Update(val);
```

**T mean()** Returns the current estimate of the mean of the windowed data.

```C++
std::cout << stats.mean() << std::endl;
```

**T var()** Returns the current estimate of the variance of the windowed data.

```C++
std::cout << stats.var() << std::endl;
```

**T std()** Returns the current estimate of the standard deviation of the windowed data.

```C++
std::cout << stats.std() << std::endl;
```

**void Clear()** Resets the estimator states.

```C++
stats.Clear();
```
