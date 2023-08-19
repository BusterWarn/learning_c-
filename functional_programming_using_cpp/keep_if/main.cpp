#include <algorithm>
#include <cstdint>
#include <vector>

#define CATCH_CONFIG_MAIN
#include <catch_amalgamated.hpp>
#include <fplus.hpp>

template <typename func, typename T>
[[nodiscard]]
constexpr auto keep_if(func f, const std::vector<T>& xs)
{
  std::vector<T> ys;
  ys.reserve(xs.size());
  std::copy_if(begin(xs), end(xs), std::back_inserter(ys), f);
  return ys;
}

template <typename T>
[[nodiscard]]
constexpr auto vecs_are_equal(const std::vector<T>& xs, const std::vector<T>& ys)
{
  if (xs.size() != ys.size())
  {
    return false;
  }

  for (std::uint32_t i = 0; i < xs.size(); ++i)
  {
    if (xs[i] != ys[i])
    {
      return false;
    }
  }

  return true;
}

[[nodiscard]]
static constexpr auto is_even = [](const auto& x)
{
  return x % 2 == 0;
};

TEST_CASE("keep_if")
{
  const std::vector xs = {0, 1, 2, 3, 4};

  const auto ys_1 = fplus::keep_if(is_even, xs);
  const auto ys_2 = keep_if(is_even, xs);

  REQUIRE(vecs_are_equal(ys_1, ys_2));
  REQUIRE_FALSE(vecs_are_equal(ys_1, xs));
}
