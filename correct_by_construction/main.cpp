#include <iostream>
#include <variant>
#include <utility>
#include <type_traits>

#include "nucelar_submarine.h"


template<typename ... base>
struct visitor : base ...
{
  using base::operator()...;
};

template<typename ... T>
visitor(T ...) -> visitor<T...>;

int main(void)
{
  constexpr visitor visit_sub
  {
    [] (nuclear::invalid_submarine sub) -> void { std::cout << "Submarine does not have orders to fire\n"; },
    [] (nuclear::live_submarine sub) -> void { sub.load_warhead(); sub.fire_warhead(); }
  };

  const auto submarine = nuclear::create_sub(nuclear::orders_from_president::fire);
  std::visit(visit_sub, submarine);

  return 0;
}