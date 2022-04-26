
#include <cstdint>
#include <iostream>
#include <vector>

#define RANGE 9999

#ifdef WITH_DESTRUTOR

class my_class
{
public:

  my_class(uint32_t count) : my_int(count) {}

  ~my_class() {};

  uint32_t my_int;
};

#else


class my_class
{
public:
  my_class(uint32_t count) : my_int(count) {}

  uint32_t my_int;
};

#endif

void count_stupidly(std::uint32_t& count)
{
  std::vector<my_class*> counters;
  for (std::uint32_t i = 0; i < RANGE; i++)
  {
    if (counters.empty())
    {
      counters.push_back(new my_class(count));
    }
    else
    {
      counters.push_back(new my_class(counters[i - 1]->my_int + 1));
    }
  }

  for (const auto& counter : counters)
  {
    count += counter->my_int;
    delete counter;
  }
}

int main()
{
  std::uint32_t count = 0;

  // Arbitrary good max number
  for (std::uint32_t a = 0; a < RANGE; a++)
  {
    count_stupidly(count);
  }
  std::cout << count << std::endl;
  return 0;
}