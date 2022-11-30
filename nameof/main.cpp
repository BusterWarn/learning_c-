#include <iostream>

#include "nameof.h"

enum class numbers
{
  one = 1,
  two = 2,
  three = 3
};

int main()
{
  numbers one = numbers::one;

  std::cout << "one: " << nameof(one) << '\n';
  numbers my_number = numbers::two;
  std::cout << "my number is: " << nameof(my_number) << " = " << static_cast<int>(my_number) << '\n';
  std::cout << "Three is: " << nameof(numbers::three) << " = " << static_cast<int>(numbers::three) << '\n';

  return 0;
}