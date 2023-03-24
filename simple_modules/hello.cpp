module;

// These libraries don't work.
// #include <string>
// #include <iostream>

// This does
#include <cstdint>

export module hello;

namespace hello
{
  export [[nodiscard]] auto say([[maybe_unused]] const char* str) -> std::uint64_t
  {
    return 5;
  }
}