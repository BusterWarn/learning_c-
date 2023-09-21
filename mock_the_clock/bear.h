#pragma once

#include <chrono>
#include <functional>

class bear
{
  std::chrono::steady_clock::time_point hibernate_until;
public:
  void hibernate_for(std::chrono::seconds duration);
  bool is_awake();
};

namespace bear_clock
{
  extern std::function<std::chrono::steady_clock::time_point()> get_time_now;
}
