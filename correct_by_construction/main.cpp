#include <iostream>
#include <variant>
#include <utility>

#include "nucelar_submarine.h"
#include "visitor.h"

auto main(void) -> std::int32_t
{
  constexpr visitor visit_sub
  {
    [] (nuclear::invalid_submarine sub) -> void { std::cout << "Submarine does not have orders to fire\n"; },
    [] (auto sub) -> void { sub.load_warhead(); sub.fire_warhead(); }
  };

  // Depending on the input different object can be created.
  // If the input is invalid (nuclear::orders_from_president::do_not_fire), then an invalid object will be created.
  const auto submarine = nuclear::create_sub(nuclear::orders_from_president::perform_test);
  std::visit(visit_sub, submarine);

  return 0;
}