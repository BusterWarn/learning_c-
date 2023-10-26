#include <functional>
#include <iomanip>
#include <iostream>

class animals
{
public:
  static animals& get_instance()
  {
    static animals instance;
    return instance;
  }

  void make_animal_sound(std::function<void(std::ostream&)> callback)
  {
    callback(std::cout);
  }
};

namespace goose_str
{
  static constexpr auto honk_happy = "Happy Honk!";
  static constexpr auto honk_sad = "Sad Honk...";
  static constexpr auto honk_panic = "EMERGENCY HONK!!!1!";
  static constexpr auto honk_relax = "Relaxed honk.";

  template<typename... Strs>
  [[nodiscard]] consteval auto compute_padding_size(Strs... strs)
  {
    const std::string_view values[] {strs...};

    auto max_it = std::max_element(values,
                                   values + sizeof...(Strs),
                                  [](const auto& a, const auto& b) {
                                    return a.size() < b.size();
                                  });
    return max_it->size() + 2;  // +2 for buffer
  }

  static constexpr auto padding_size = compute_padding_size(honk_happy, honk_sad, honk_panic, honk_relax);
}

class goose {
public:
  goose()
  {
    animals::get_instance().make_animal_sound([&](std::ostream& os)
    {
      static_assert(goose_str::padding_size == 21); // Not at all needed, just to show it is known at compile time.

      os << std::left << std::setw(goose_str::padding_size) << goose_str::honk_happy << "honk honk" << std::endl;
      os << std::left << std::setw(goose_str::padding_size) << goose_str::honk_sad << "hoonk" << std::endl;
      os << std::left << std::setw(goose_str::padding_size) << goose_str::honk_panic << "honk honk hooooonk" << std::endl;
      os << std::left << std::setw(goose_str::padding_size) << goose_str::honk_relax << "honk" << std::endl;

      // Could also be done like this...
      // os <<  "Happy Honk!          " << "honk honk" << std::endl;
      // os <<  "Sad Honk...          " << "hoonk" << std::endl;
      // os <<  "EMERGENCY HONK!!!1!  " << "honk honk hooooonk" << std::endl;
      // os <<  "Relaxed honk.        " << "honk" << std::endl;
    });
  }
};

int main()
{
  const goose g;
}
