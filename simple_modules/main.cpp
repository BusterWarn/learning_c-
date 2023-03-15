//module;

import hello;
#include <iostream>
// import <iostream>;

int main()
{
  // std::cout << "Hello World!\n";
  std::cout << hello::say("Hello World!") << '\n';
  return 0;
}