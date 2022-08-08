#include <iostream>

#include "power_of.h"

int main()
{
  int result = power_of(3, 3);

  std::cout << "\nResult: " << result << '\t';

  if (result != 81)
  {
    std::cout << "Test failed" << '\n';
    return 1;
  }
    std::cout << "Test passed" << '\n';
  return 0;
}