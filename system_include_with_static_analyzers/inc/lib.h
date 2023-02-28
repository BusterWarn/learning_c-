#pragma once

#include <cstdint>

int get_stuff(std::uint32_t value)
{
  return value * 2;
}

int do_stuff(int value)
{
  return get_stuff(value);
}