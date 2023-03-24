// Did not compile with this.
// module;

import hello;

#include <iostream>


int main()
{
  std::cout << hello::say("Hello World!") << '\n';
  return 0;
}