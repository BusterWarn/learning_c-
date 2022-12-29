#include <memory>

struct s_api
{
  [[nodiscard]] virtual auto get_value() -> int const = 0;
};

struct s : public s_api
{
  int value = 42;

  auto get_value() -> int const override
  {
    return value;
  }
};

auto main() -> int
{
  std::shared_ptr<s_api> s_sp = std::make_shared<s>();
  s_sp->get_value();

  s_api* s_p = new s;
  s_p->get_value();
  delete s_p;

  return 0;
}