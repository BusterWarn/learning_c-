#define CATCH_CONFIG_MAIN
#include <catch_amalgamated.hpp>

#include "bear.h"

TEST_CASE("Bear should hibernate and wake up correctly")
{
  bear my_bear;
  auto stubbed_time = std::chrono::steady_clock::now();
  bear_clock::get_time_now = [&stubbed_time]() mutable
  {
    return stubbed_time;
  };

  SECTION("Bear initially awake")
  {
    REQUIRE(my_bear.is_awake() == true);
  }

  SECTION("Bear should hibernate")
  {
    my_bear.hibernate_for(std::chrono::seconds(3));
    REQUIRE(my_bear.is_awake() == false);

    SECTION("Bear should wake up after time advances")
    {
      stubbed_time += std::chrono::seconds(4);
      REQUIRE(my_bear.is_awake() == true);
    }
  }
}
