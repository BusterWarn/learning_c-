#include <iostream>
#include <string>
#include <fstream>
// #include <string_view>

// #define big_string
// #define small_string
// #define with_endl
// #define without_endl
// #define no_reference
// #define reference
// #define STRING_VIEW
// #define better_reference
#define better_string_view

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
}
#endif

#ifdef small_string
int main()
{
  std::string hello_world = "Hello world";
  std::cout << hello_world << '\n';
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
  os << std::flush;
}
#endif

#ifdef no_reference
int main()
{
  std::string hello_world = "Hello World Hello World Hello World";
  auto print = [](std::string str) { std::cout << str << '\n';};
  print(hello_world);
}
#endif

#ifdef reference
int main()
{
  std::string hello_world = "Hello World Hello World Hello World";
  auto print = [](const std::string& str) { std::cout << str << '\n';};
  print(hello_world);
}
#endif

#ifdef STRING_VIEW
int main()
{
  std::string hello_world = "Hello World Hello World Hello World";
  auto print = [](std::string_view str) { std::cout << str << '\n';};
  print(hello_world);
}
#endif

#ifdef better_reference
int main()
{
  auto print = [](const std::string& str) { std::cout << str << '\n';};
  print("Hello World Hello World Hello World");
}
#endif

#ifdef better_string_view
int main()
{
  auto print = [](std::string_view str) { std::cout << str << '\n';};
  print("Hello World Hello World Hello World");
}
#endif
