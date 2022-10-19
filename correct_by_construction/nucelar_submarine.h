
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
  fire = 1
};

class submarine
{
public:
  virtual void load_warhead() = 0;
  virtual void fire_warhead() = 0;
};

class invalid_submarine : public submarine
{
public:
  void load_warhead() override
  {
  }

  void fire_warhead() override
  {
  }
};

class live_submarine : public submarine
{
public:
  live_submarine()
  {
    m_detonate = []() { std::cout << "No warhead is loaded\n"; };
  }

  void load_warhead() override
  {
    std::cout << "Loading warhead\n";
    m_detonate = []()
    {
      std::cout << "Firing warhead!\n";
      throw std::runtime_error("Kaboooom! The world have exploaded!" );
    };
  }

  void fire_warhead() override
  {
    m_detonate();
  }

private:
  std::function<void(void)> m_detonate;
};


std::variant<live_submarine, invalid_submarine> create_sub(orders_from_president&& orders)
{
  switch (orders)
  {
    case orders_from_president::do_not_fire:
      return invalid_submarine();
    case orders_from_president::fire:
      return live_submarine();
  }
}

}