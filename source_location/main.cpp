#include <iostream>
#include <cstdint>
#include <source_location>
#include <typeinfo>

void log(const char* msg,
         const std::source_location from = std::source_location::current())
{
  std::cout << from.file_name() << "("
            << from.line() << ":"
            << from.column() << ") `"
            << from.function_name() << "`: "
            << msg << '\n';
}

template <typename T>
void from_template(T msg)
{
  log(typeid(msg).name());
}

template <typename... Ts>
struct variadic_log
{
  variadic_log(Ts&&... ts,
                const std::source_location& from = std::source_location::current())
  {
    std::cout << from.file_name() << "("
              << from.line() << ":"
              << from.column() << ") `"
              << from.function_name() << "`: ";
    ((std::cout << std::forward<Ts>(ts) << " "), ...);
    std::cout << '\n';
  }
};

template <typename... Ts>
variadic_log(Ts&&...) -> variadic_log<Ts...>;

auto main() -> int
{
  // Standard logs
  log("hello!");
  
  // With lambda
  const auto from_lambda = [](const char* msg) -> std::uint8_t
  {
    log(msg);
    return 5;
  };
  from_lambda("c++20");

  // With templates
  from_template<double>(2);

  // Variadic style
  variadic_log("Hello", "World");

  return 0;
}