#include <optional>
#include <utility>
#include <iostream>

void print_optional(const std::optional<float>& opt)
{
  if (opt)
    std::cout << "Value: " << *opt << std::endl;
  else
    std::cout << "No value." << std::endl;
}

int main()
{
  std::optional<float> my_opt = 3.14;

  std::cout << "Has value: " << (my_opt.has_value() ? "true" : "false") << std::endl;

  // Pass the value and reset in one line
  print_optional(std::exchange(my_opt, std::nullopt));
  print_optional(std::exchange(my_opt, std::nullopt));

  std::cout << "Has value: " << (my_opt.has_value() ? "true" : "false") << std::endl;

  return 0;
}