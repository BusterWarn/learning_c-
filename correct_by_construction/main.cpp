#include <iostream>
#include <variant>
#include <string>


#include "nucelar_submarine.h"


int main(void)
{
  nucelar_submarine sub = nucelar_submarine();
  sub.load();
  sub.fire();

  std::variant<int, float> data;
  data = 5;
  if (std::get_if<int>(&data))
  {
    std::cout << "INTEGER\n";
  }
  else
  {
    std::cout << "FLOAT\n";
  }
  data = 5;

  return 0;
}