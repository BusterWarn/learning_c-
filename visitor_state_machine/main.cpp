#include <cassert>
#include <iostream>
#include <utility>
#include <variant>
#include <vector>

#include "../correct_by_construction/visitor.h"

namespace state
{
  struct A {};
  struct B {};
  struct C {};

  struct D
  {
    D(const char prev_state) : prev_state(prev_state) {}
    char prev_state;
  };
  
  struct ERROR {};
}

namespace action
{
  struct PLUS_ODD {};
  struct PLUS_EVEN {};
}

using state_t = std::variant<
  state::A,
  state::B,
  state::C,
  state::D,
  state::ERROR>;

using action_t = std::variant<
  action::PLUS_ODD,
  action::PLUS_EVEN>;

constexpr visitor state_to_char_visitor
{
  [] (const state::A&) -> char
  {
    return 'a';
  },
  [] (const state::B&) -> char
  {
    return 'b';
  },
  [] (const state::C&) -> char
  {
    return 'c';
  },
  [] (const state::D&) -> char
  {
    return 'd';
  },
  [] (const auto&) -> char
  {
    return '\0';
  },
};

constexpr visitor change_state_visitor
{
  // A
  [] (const state::A&, const action::PLUS_ODD&) -> state_t
  {
    return state::B{};
  },
  [] (const state::A&, const action::PLUS_EVEN&) -> state_t
  {
    return state::C{};
  },
  
  // B
  [] (const state::B&, const action::PLUS_ODD&) -> state_t
  {
    return state::C{};
  },
  [] (const state::B& b, const action::PLUS_EVEN&) -> state_t
  {
    return state::D{std::visit(state_to_char_visitor, state_t{b})};
  },
  
  // C
  [] (const state::C& c, const action::PLUS_ODD&) -> state_t
  {
    return state::D{std::visit(state_to_char_visitor, state_t{c})};
  },
  [] (const state::C&, const action::PLUS_EVEN&) -> state_t
  {
    return state::A{};
  },
  
  // D
  [] (const state::D& d, const action::PLUS_ODD&) -> state_t
  {
    // Some weird arbitrary logic here
    if (d.prev_state != 'a')
    {
      return state::B{};
    }

    return state::A{};
  },
  [] (const state::D&, const action::PLUS_EVEN&) -> state_t
  {
    return state::B{};
  },

  // ERROR
  [](const auto&, const auto&) -> state_t
  {
    std::cout << "ERROR" << '\n';
    return state::ERROR{};
  }
};

constexpr visitor print_state_visitor
{
  [] (const auto&) -> void
  {
    std::cout << "I don't care what state this is\n";
  },
  [] (const state::A&) -> void
  {
    std::cout << "State is A\n";
  },
  [] (const state::D& d) -> void
  {
    std::cout << "State is D. Previous state: " << d.prev_state << '\n';
  },
};

template<typename left_variant, typename right_variant>
constexpr bool holds_same_type(const left_variant& left, const right_variant& right)
{
  return std::visit(
    [](const auto& left, const auto& right)
    {
      return std::is_same_v<decltype(left), decltype(right)>;
    },
    left,
    right
  );
}

int main()
{
  const auto actions_and_expected_state = []
  {
    std::vector<std::pair<action_t, state_t>> actions_and_expected_state{};
    actions_and_expected_state.emplace_back(action::PLUS_ODD{}, state::B{});
    actions_and_expected_state.emplace_back(action::PLUS_ODD{}, state::C{});
    actions_and_expected_state.emplace_back(action::PLUS_ODD{}, state::D{'c'});
    actions_and_expected_state.emplace_back(action::PLUS_ODD{}, state::B{});
    actions_and_expected_state.emplace_back(action::PLUS_EVEN{}, state::D{'b'});
    actions_and_expected_state.emplace_back(action::PLUS_EVEN{}, state::B{});
    actions_and_expected_state.emplace_back(action::PLUS_ODD{}, state::C{});
    return actions_and_expected_state;
  }();

  state_t state = state::A{}; // The initial state must be a variant since the std::visit only takes std::variants.

  std::visit(print_state_visitor, state);
  for (const auto& [action, expected_state] : actions_and_expected_state)
  {
    state = std::visit(change_state_visitor, state, action);
    std::visit(print_state_visitor, state);
    assert(holds_same_type(state, expected_state));
  }
};