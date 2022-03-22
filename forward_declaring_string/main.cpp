#include <string>
#include <iostream>

#include "stdfwd.h"
#include "my_class.h"

int main(void)
{
  my_class the_class;
  
  std::cout << the_class.get_string() << '\n';

  return 0;
}