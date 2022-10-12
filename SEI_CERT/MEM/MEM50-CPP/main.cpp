#include <string>
#include <iostream>
#include <memory>

struct E
{
  E() : str("Hello world!") { std::cout << "Construct E\n"; }
  ~E() { std::cout << "Destruct E\n"; }
  const std::string str;
};

std::string str_func()
{
  return "Hello world!";
}

auto get_e() -> E
{
  return E();
}

void display_string(const char* str)
{
  std::cout << str << '\n';
}
  
void f_1() {
  std::cout << "\nf_1()\n";
  const char *str = str_func().c_str();
  display_string(str);  /* Undefined behavior */
}

void f_2() {
  std::cout << "\nf_2()\n";
  std::string str = str_func();
  const char *cstr = str.c_str();
  display_string(cstr);  /* ok */
}

void f_3() {
  std::cout << "\nf_3()\n";
  display_string(str_func().c_str());  /* ok ?*/
}

void e_1() {
  std::cout << "\ne_1()\n";
  const char *str = get_e().str.c_str();
  display_string(str);  /* Undefined behavior */
}

void e_2() {
  std::cout << "\ne_2()\n";
  E e = get_e();
  const char *cstr = e.str.c_str();
  display_string(cstr);  /* ok */
}

void e_3() {
  std::cout << "\ne_3()\n";
  display_string(get_e().str.c_str());  /* ok ?*/
}

int main()
{
  f_1();
  f_2();
  f_3();
  // With structs
  e_1();
  e_2();
  e_3();
}