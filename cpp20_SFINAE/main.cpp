#include <cstdint>
#include <type_traits>
#include <source_location>
#include <iostream>
#include <concepts>
#include <utility>

void log(const std::source_location from = std::source_location::current())
{
  std::cout << from.file_name() << "("
            << from.line() << ":"
            << from.column() << ") '"
            << from.function_name() << "'\n";
}

#if (__cplusplus >= 202002)

template<typename T>
auto add_floats(const T f1, const T f2) requires std::is_floating_point_v<T> && std::is_rvalue_reference_v<T>
{
  log();
  return f1 + f2;
}

template<typename Float>
concept floating_point = std::is_floating_point_v<Float> && std::is_lvalue_reference_v<Float>;

template<floating_point F>
auto add_floats(const F f1, const F f2)
{
  log();
  return f1 + f2;
}

template <typename T>
requires std::integral<T>
auto add_floats(const T f1, const T f2)
{
  log();
  return f1 + f2;
}

std::floating_point auto add_floats(std::floating_point auto f1, std::floating_point auto f2)
{
  log();
  return f1 + f2;
}

auto main() -> int
{
  auto a = add_floats(1.0, 2.0);
  auto b = add_floats(1.0, 2.0);
  auto c = add_floats(a, b);
  return add_floats(1, 2);
}

#else

template<typename F,
        typename = std::enable_if<std::is_floating_point_v<F>>>
auto add_floats(const F f1, const F f2)
{
  log();
  return f1 + f2;
}

auto main() -> int
{
  return add_floats(1.0, 2.0);
}

#endif

