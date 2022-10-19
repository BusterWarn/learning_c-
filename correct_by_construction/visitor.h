// This file includes some template boilerplate code that allows use to create visitors.
#include <type_traits>

template<typename ... base>
struct visitor : base ...
{
  using base::operator()...;
};

template<typename ... T>
visitor(T ...) -> visitor<T...>;