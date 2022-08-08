#include "power_of.h"

std::uint64_t power_of(const std::uint64_t base, const std::uint16_t exponent)
{
  std::uint64_t result = base;
  for (std::uint16_t i; i < exponent; i++)
  {
    result = result * base;
  }
  return result;
}