# Changelog

## v4.0.2
- Updated to CircleBuf v4.0.1

## v4.0.1
- Updated preprocessor directives to more easily define when Arduino IDE is used
- Updated README to better detail the Arduino support

## v4.0.0
- Updated directory structure to support Arduino in addition to CMake builds
- Added an Arduino example
- Updated README

## v3.0.1
- Updated counter from *int* to *std::size_t*

## v3.0.0
- Updated namespace to *bfs*
- Changed *Running* to *RunningStats* and *MovingWindow* to *MovingWindowStats*

## v2.0.1
- Updated contributing
- Updated circle_buf dependency to pull from our GitHub repo
- Added line length limits to CI/CD and modified statistics.h to meet those limits

## v2.0.0
- Renamed class *Welford* to *Running* to more closely align with the GSL nomenclature
- Added a *MovingWindow* class, which computes mean, var, and std on a moving window of data
- Updated readme, examples, and tests

## v1.0.2
- Updated contributing

## v1.0.1
- Updated license to MIT

## v1.0.0
- Initial baseline
