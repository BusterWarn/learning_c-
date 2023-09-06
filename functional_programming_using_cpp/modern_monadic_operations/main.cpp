#include <cctype>
#include <iostream>
#include <optional>
#include <ranges>
#include <string>
#include <vector>

using maybe_name = std::optional<const std::string>;

[[nodiscard]]
auto to_lowercase(const maybe_name& name_opt) -> maybe_name
{
  if (!name_opt) return std::nullopt;
  const auto& name = *name_opt;

  for (char c : name) {
    if (std::isdigit(c)) return std::nullopt;
  }

  std::string result(name.begin(), name.end());
  for (char& c : result)
      c = std::tolower(c);

  return result;
}

[[nodiscard]]
auto split_name(const maybe_name& name_opt) -> std::optional<std::pair<std::string, maybe_name>>
{
  if (!name_opt) return std::nullopt;
  const auto& name = *name_opt;

  size_t space_pos = name.find(' ');
  if (space_pos == std::string::npos)
    return {{name, std::nullopt}};

  return {{name.substr(0, space_pos), name.substr(space_pos + 1)}};
}

[[nodiscard]]
auto to_snake_case(const maybe_name& name_opt) -> maybe_name
{
  const auto full_name = split_name(name_opt);
  if (!full_name) return std::nullopt;

  const auto& [first, last_opt] = *full_name;

  if (!last_opt)
    return std::nullopt;

  return std::string(first) + "_" + std::string(*last_opt);
}

[[nodiscard]]
auto add_cool_prefix(const maybe_name& name_opt) -> maybe_name
{
  if (!name_opt) return std::nullopt;
  const auto& name = *name_opt;

  if (name.empty() || name[0] == 'c')
    return std::nullopt;

  return "cool_" + std::string(name);
}

[[nodiscard]]
auto to_cool_name(const std::string& full_name) -> maybe_name
{
  return add_cool_prefix(to_snake_case(to_lowercase(full_name)));
}

int main()
{
  const std::vector<std::string> people =
  {
    "my name",
    "carl christian",
    "Elon1 musk",
    "Mary",
    "Alice Wonderland",
    "Robert Downey",
    "Chandler Bing",
    "Joey",
    "Clark Kent",
    "John Doe"
  };

#ifndef WITH_RANGES
  for (const auto& person : people)
  {
    const auto cool_person = to_cool_name(person);
    if (!cool_person)
      continue;

    std::cout << *cool_person << std::endl;
  }

#else
  auto cool_names = people
    | std::views::transform(to_lowercase)
    | std::views::transform(to_snake_case)
    | std::views::transform(add_cool_prefix)
    | std::views::filter([](const maybe_name& name_opt) { return name_opt.has_value(); })
    | std::views::transform([](const maybe_name& name_opt) { return name_opt.value(); });

  for (auto&& cool_name : cool_names)
  {
    std::cout << cool_name << '\n';
  }
#endif

  return 0;
}
