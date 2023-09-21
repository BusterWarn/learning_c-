#include "bear.h"

void bear::hibernate_for(std::chrono::seconds duration)
{
  hibernate_until = bear_clock::get_time_now() + duration;
}

bool bear::is_awake()
{
  return bear_clock::get_time_now() >= hibernate_until;
}

namespace bear_clock
{
  std::function<std::chrono::steady_clock::time_point()> get_time_now = []
  {
    return std::chrono::steady_clock::now();
  };
}