#pragma once

#include <memory>

class dogoo
{
public:
  // Without constructor / destructor program won't compile.
  // error: invalid application of ‘sizeof’ to incomplete type ‘dogoo::impl’ 83 |  static_assert(sizeof(_Tp)>0,
  // See https://stackoverflow.com/questions/6012157/is-stdunique-ptrt-required-to-know-the-full-definition-of-t
  dogoo();
  ~dogoo() noexcept;

  void woof();

  int get_woofs();

private:

  // Internal implementation class. Contains all dependencies.
  class impl;

  // Pointer to implementation.
  std::unique_ptr<impl> m_impl_up;
};