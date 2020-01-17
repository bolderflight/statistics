# Statistics
This library contains statistics functions and classes.

## License
[Library license](LICENSE.md).

## Changelog
[Library changelog](CHANGELOG.md).

## Contributing
[Bolder Flight Systems contributing guide](CONTRIBUTING.md).

## Installation
CMake is used to build this library, which is exported as a library target called *statistics*. The header is added as:

```
#include "statistics/statistics.h"
```

Note that you'll need CMake version 3.13 or above; it is recommended to build and install CMake from source, directions are located in the [CMake GitLab repository](https://github.com/Kitware/CMake).

The library can be also be compiled stand-alone using the CMake idiom of creating a *build* directory and then, from within that directory issuing:

```
cmake ..
make
```

This will build the library, an example executable called *welford_example*, and an executable for testing using the Google Test framework, called *welford_test*. The example executable source file is located at *examples/welford_example.cc*. This code is built and tested on an AMD64 system running Linux and is likely to build on AMD64 systems running the Windows Subsystem for Linux (WSL). As an alternative, a Docker container has been [built](https://hub.docker.com/r/flybrianfly/gcc-cmake) which extends the gcc container to include CMake support and supports building this library.

## Namespace
This library is within the namespace *statistics*.

# Welford
This class implements Welford's method for streaming estimation of mean, variance, and standard deviation. 

## Methods

**Welford()** Creates a Welford object and initializes the estimator states.

```C++
statistics::Welford w;
```

**void Welford::Accum(float x)** Accumulates data into the estimator.

```C++
for (unsigned int i = 0; i < 10; i++) {
  w.Accum((float) i);
}
```

**float Welford::GetMean()** Returns the current estimate of the mean of the accumulated data.

```C++
std::cout << w.GetMean() << std::endl; // 4.5
```

**float Welford::GetVar()** Returns the current estimate of the variance of the accumulated data.

```C++
std::cout << w.GetVar() << std::endl; // 9.1667
```

**float Welford::GetStd()** Returns the current estimate of the standard deviation of the accumulated data.

```C++
std::cout << w.GetStd() << std::endl; // 3.0277
```

**void Welford::Clear()** Resets the estimator states.

```C++
w.Clear();
```
