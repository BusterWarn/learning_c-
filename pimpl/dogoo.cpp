#include "dogoo.h"

#include <cstdint>
#include <iostream>

class dogoo::impl
{
public:

  impl() : m_woofs(0) {}

  void woof();

  int get_woofs();

private:
  // We want to keep this unsigned because of buisness logic reasons
  std::uint32_t m_woofs;
};

void dogoo::impl::woof()
{
  m_woofs++;
  std::cout << "Wooooof\n";
}

int dogoo::impl::get_woofs()
{
  return static_cast<int>(m_woofs);
}

dogoo::dogoo()
  : m_impl_up(std::make_unique<dogoo::impl>())
{}

dogoo::~dogoo() = default;

void dogoo::woof()
{
  m_impl_up->woof();
}

int dogoo::get_woofs()
{
  return m_impl_up->get_woofs();
}