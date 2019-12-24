# Welford
This class implements Welford's method for streaming estimation of mean, variance, and standard deviation. 

## Installation
CMake is used to build this library, which is exported as a library target called *welford*. The header is added as:

```
#include "welford/welford.h"
```

The library can be also be compiled stand-alone using the CMake idiom of creating a *build* directory and then, from within that directory issuing:

```
cmake ..
make
```

This will build the library, an example executable called *welford_example*, and an executable for testing using the Google Test framework, called *welford_test*. The example executable source file is located at *examples/welford_example.cc*.

## Methods

**Welford()** Creates a Welford object and initializes the estimator states.

```C++
Welford w;
```

**Accum(float x)** Accumulates data into the estimator.

```C++
for (unsigned int i = 0; i < 10; i++) {
  w.Accum((float) i);
}
```

**float GetMean()** Returns the current estimate of the mean of the accumulated data.

```C++
std::cout << w.GetMean() << std::endl; // 4.5
```

**float GetVar()** Returns the current estimate of the variance of the accumulated data.

```C++
std::cout << w.GetVar() << std::endl; // 9.1667
```

**float GetStd()** Returns the current estimate of the standard deviation of the accumulated data.

```C++
std::cout << w.GetStd() << std::endl; // 3.0277
```

**void Clear()** Resets the estimator states.

```C++
w.Clear();
```
