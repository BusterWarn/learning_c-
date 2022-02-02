#include <iostream>
#include <string>
#include <fstream>

#define big_string
// #define small_string
// #define c_str
// #define with_endl
// #define without_endl
// #define no_reference
// #define reference
// #define STRING_VIEW
// #define better_reference
// #define better_string_view
// #define rat_string_literal

void* operator new(size_t size)
{
  std::cout << "Allocating " << size << " bytes\n";
  return malloc(size);
}

#ifdef big_string
int main()
{
  std::string hello_world = "Hello world Hello World Hello World";
  std::cout << hello_world << '\n';

  return 0;
}
#endif

#ifdef small_string
int main()
{
  std::string hello_world = "Hello world";
  std::cout << hello_world << '\n';

  return 0;
}
#endif

#ifdef with_endl
int main()
{
  std::ofstream file("output.txt", std::ios_base::trunc);
  for (std::uint32_t i = 0; i < 1000000; i++)
  {
    file << "Hello World" << std::endl;
  }

  return 0;
}
#endif

#ifdef without_endl
int main()
{
  std::ofstream os("output.txt", std::ios_base::trunc);
  for (std::uint32_t i = 0; i < 1000000; i++)
  {
    os << "Hello World\n";
  }
  // If you want to flush ou can do it like this.
  os << std::flush;

  return 0;
}
#endif

#ifdef c_str
int main()
{
  const char hello_world[] = "Hello World Hello World Hello World";
  auto print = [](const char str[]) { std::cout << str << '\n';};
  print(hello_world);

  return 0;
}
#endif

#ifdef no_reference
int main()
{
  std::string hello_world = "Hello World Hello World Hello World";
  auto print = [](std::string str) { std::cout << str << '\n';};
  print(hello_world);

  return 0;
}
#endif

#ifdef reference
int main()
{
  std::string hello_world = "Hello World Hello World Hello World";
  auto print = [](const std::string& str) { std::cout << str << '\n';};
  print(hello_world);

  return 0;
}
#endif

#ifdef STRING_VIEW
int main()
{
  std::string hello_world = "Hello World Hello World Hello World";
  auto print = [](std::string_view str) { std::cout << str << '\n';};
  print(hello_world);

  return 0;
}
#endif

#ifdef better_reference
int main()
{
  auto print = [](const std::string& str) { std::cout << str << '\n';};
  print("Hello World Hello World Hello World");

  return 0;
}
#endif

#ifdef better_string_view
int main()
{
  auto print = [](std::string_view str) { std::cout << str << '\n';};
  print("Hello World Hello World Hello World");

  return 0;
}
#endif

// This is not an example of string Optimization but of raw string literals.
#ifdef rat_string_literal
int main()
{
  // Normal string.
  std::string str_1 = "\nHe\tllo\rworld\n";

  // Raw string literal
  std::string str_2 = R"(\nHe\tllo\rworld\n)";

  std::cout << "String 1: " << str_1 << '\n';
  std::cout << "String 2: " << str_2 << '\n';

  return 0;
}
#endif