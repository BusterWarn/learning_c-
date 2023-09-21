# Mock the Clock to Test the Bear

How can we stub or stub a `std::chrono` clock? One approach involves using preprocessor directives, such as `#ifdef UNITTEST`.

```c++
// In the source code
std::chrono::time_point<std::chrono::steady_clock> getTimeNow()
#ifndef UNITTEST
{
  return std::chrono::steady_clock::now();
}
#endif
```

```c++
// In the test code
#ifdef UNITTEST
static std::optional<std::chrono::time_point<std::chrono::steady_clock>> stubbedTime = std::nullopt;

std::chrono::time_point<std::chrono::steady_clock> getTimeNow()
{
  if (!stubbedTime)
  {
    return std::chrono::steady_clock::now();
  }
  return *stubbedTime;
}

void advanceStubbedTime(std::chrono::seconds seconds)
{
  assert(stubbedTime.has_value());
  stubbedTime = stubbedTime.value() + seconds;
}
#endif

```

While this is a straightforward way to stub the time, it relies on static variables in the test code and uses `#ifdef`s. We can do better!

This example simulates a bear that hibernates for a fixed period. It demonstrates how to override and stub time-dependent functionality for unit tests.

In `bear.h` and `bear.cpp`, the clock is defined. Then, in `tests.cpp`, the clock is overridden and stubbed.

## Compile the program
```shell
make all
```
or
```shell
make all CXX=clang++
```

## Run the program

```shell
PS mock_the_clock> .\out\main.exe 1
The bear is hibernating.
```

```shell
PS mock_the_clock> .\out\main.exe 3
The bear is awake.
```

## Compile and run the tests:

```shell
PS mock_the_clock> make test
...
Randomness seeded to: 399936360
===============================================================================
All tests passed (3 assertions in 1 test case)
```