# Bolder Flight Systems Contributing Guide
The following guidelines set best practices for contributing to Bolder Flight Systems software repositories.

----

## On this page
{:.no_toc}

- TOC
{:toc}

----

## Steps
Software development and contribution should follow these steps:
   * Develop
   * Test 
   * Document 
   * Merge
Further detail is provided below for each step.

### Develop
Software should be developed following our [Style Guide](). 

### Style Guide
Follow the [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html). Any parameter or variable names, which contain unit specific data should be appended with an underscore and the units (i.e. accel_z_mss). Several common units are listed below; as a general rule SI units should be used.
   * _c: Celsius
   * _pa: Pascal
   * _m: meter
   * _rad: radian
   * _ut: micro-tesla
   * _s: seconds
   * _ms: milliseconds
   * _us: microseconds
   * _ms: meters/second
   * _rads: radians/s
   * _mss: meters/second/second

## External sources licensing
If you use external sources, ensure that it is licensed MIT, BSD, or a similarly permissive license. We would like to limit the amount of LGPL code in our code base and need to avoid GPL and unlicensed code.

If you are using external sources with licenses other than MIT or BSD, contact [Brian](mailto:brian.taylor@bolderflight.com) to discuss options.

## Pushing to master
Pushing directly to the master branch is dangerous - it enables changes to be made without proper testing and review. This practice also increases the risk of pushing breaking changes and having inadequate documentation. You should create a branch, make your changes, run tests, update documentation, and submit a merge request.

## Tests
All tests should pass before a pull request is issued. At a minimum, the following tests should be run:
   * Linting: 

### Linting

### Smoke

### Expected values

## Documentation

## Merge
