# Modern Error Handling

Inspired by [How C++23 Changes the Way We Write Code - Timur Doumler - CppCon 2022](https://youtu.be/eD-ceG-oByA?t=2222), specifically the section on `std::expected` and monadic error handling.

`std::expected` is [so far only implemented](https://en.cppreference.com/w/cpp/23) in [gcc 13](https://gcc.gnu.org/gcc-13/changes.html) which is not released yet and partially implemented in MSVC 19.36, it can be hard to compile the examples using this library. Thus I've created two godbolt links which use gcc trunk.

[std_expected.cpp](https://godbolt.org/z/9qErax4fM)
[std_expected_with_variants.cpp](https://godbolt.org/z/5x3Wsod6s)