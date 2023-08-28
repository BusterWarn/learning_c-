#pragma once

template <typename T>
void template_print(const T& t);

// Explicit instantiation of the template for the types you expect to use
extern template void template_print<int>(const int&);
extern template void template_print<float>(const float&);
// Add more instantiations as needed