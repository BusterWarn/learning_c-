#include <iostream>
#include <cstdlib>
#include <thread>

#include "bear.h"

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "Usage: " << argv[0] << " <seconds>\n";
    return 1;
  }

  const auto wait_seconds = std::atoi(argv[1]);

  if (wait_seconds <= 0)
  {
    std::cerr << "Please provide a positive number of seconds to wait.\n";
    return 1;
  }

  bear my_bear;
  my_bear.hibernate_for(std::chrono::seconds(2));

  // Wait for user-specified amount of time
  std::this_thread::sleep_for(std::chrono::seconds(wait_seconds));

  if (my_bear.is_awake())
  {
    std::cout << "The bear is awake.\n";
  }
  else
  {
    std::cout << "The bear is hibernating.\n";
  }

  return 0;
}