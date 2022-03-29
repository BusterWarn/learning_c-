#include <iostream>

#include "dogoo.h"

int main(void)
{
  dogoo big_dawg;
  
  for (int i = 0; i < 7; i++)
  {
    big_dawg.woof();
  }

  std::cout << "Nr of woofs: " << big_dawg.get_woofs() << '\n';

  return 0;
}