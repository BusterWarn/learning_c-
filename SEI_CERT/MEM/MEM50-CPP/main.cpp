#include <string>
#include <iostream>
  
std::string str_func()
{
  return "Hello world!";
}

void display_string(const char* str)
{
  std::cout << str << '\n';
}
  
void f_1() {
  const char *str = str_func().c_str();
  display_string(str);  /* Undefined behavior */
}

void f_2() {
  std::string str = str_func();
  const char *cstr = str.c_str();
  display_string(cstr);  /* ok */
}

void f_3() {
  display_string(str_func().c_str());  /* ok ?*/
}

int main()
{
  f_1();
  f_2();
  f_3();
}