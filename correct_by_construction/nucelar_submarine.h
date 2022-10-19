
#pragma once

#include <stdexcept>
#include <functional>
#include <variant>
#include <iostream>

namespace nuclear
{

enum class orders_from_president
{
  do_not_fire = 0,
  perform_test = 1,
  fire = 2
};

struct invalid_submarine{};

class test_submarine
{
public:
  void load_warhead()
  {
    std::cout << "This is a test, but it is very serious. Prepare to fire!\n";
  }

  void fire_warhead()
  {
    std::cout << "Kaboooom! Good job submarine crew we have successfully performed the test. Hope no one died by a kitchen fire.\n";
  }
};

class live_submarine
{
public:
  live_submarine()
  {
    m_detonate = []() { std::cout << "No warhead is loaded\n"; };
  }

  void load_warhead()
  {
    std::cout << "Loading warhead\n";
    m_detonate = []()
    {
      std::cout << "Firing warhead!\n";
      throw std::runtime_error("Kaboooom! The world have exploaded!" );
    };
  }

  void fire_warhead()
  {
    m_detonate();
  }

private:
  std::function<void(void)> m_detonate;
};

// This simple function could be replaced by some builder pattern.
auto create_sub(const orders_from_president&& orders) -> std::variant<live_submarine,
                                                                      test_submarine,
                                                                      invalid_submarine> 
{
  // Note that business logic could fail here, and the object created would not be valid.
  switch (orders)
  {
    case orders_from_president::do_not_fire:
      return invalid_submarine();
    case orders_from_president::perform_test:
      return test_submarine();
    case orders_from_president::fire:
      return live_submarine();
  }
}

}