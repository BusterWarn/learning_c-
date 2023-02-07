#include <cstdint>

#if (__cplusplus >= 202002)
consteval
#else
constexpr
#endif
auto get_value(int value) -> int
{
  for (uint32_t i = 0; i < 10; i++)
  {
    value += 2;
  }
  return value;
}


auto main() -> int
{
#if (__cplusplus >= 202002)

  const int is_constexpr = 5;
#else

  const int is_constexpr = 5;
  // static_assert(is_constexpr == 5);
  // static constexpr int is_constexpr = 5;

#endif

  return get_value(is_constexpr);
}