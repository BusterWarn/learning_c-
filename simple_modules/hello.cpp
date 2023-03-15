module;


export module hello;

import <iostream>;

namespace hello
{
  export int say([[maybe_unused]] char* str)
  {
    std::cout << "WTF\n";
    return 5;
  }
}