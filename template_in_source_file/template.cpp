#include "template.h"

#include <iostream>

// Explicit instantiations (definitions) for the types
template void template_print<int>(const int&);
template void template_print<float>(const float&);
// Add more instantiations as needed

template <typename T>
void template_print(const T& t)
{
  std::cout << "Printing... " << t << '\n';
}