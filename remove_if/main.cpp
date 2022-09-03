#include <iostream>
#include <string>
#include <map>

void print_doggys(std::map<std::string, std::uint32_t>& doogy_map)
{
  for (const auto& [dog, number] : doogy_map)
  {
    std::cout << "Dog: " << dog << " number: " << number << '\n';
  }
}

#if (__cplusplus >= 201709)
  
  std::uint32_t custom_remove_if(std::map<std::string, std::uint32_t>& doogy_map, std::string key_dog)
  {
    return std::erase_if(doogy_map, [key_dog](const auto& item) {
      auto const& [dog, _] = item;
      return dog == key_dog;
    });
  }

#else
  std::uint32_t custom_remove_if(std::map<std::string, std::uint32_t>& doogy_map, std::string key_dog)
  {
    std::uint32_t count = 0;
    for (auto dog_it = doogy_map.begin(); dog_it != doogy_map.end(); )
    {
      auto const& [dog, _] = *dog_it;
      if (key_dog == dog)
      {
        dog_it = doogy_map.erase(dog_it);
        count++;
      }
      else
      {
        dog_it++;
      }
    }
    return count;
  }
#endif

int main()
{
  std::map<std::string, std::uint32_t> dog_favourite_ints
    {
      {"dog_1", 1},
      {"dog_2", 2},
      {"dog_3", 3}
    };

  std::cout << "Full list of doogies:\n";
  print_doggys(dog_favourite_ints);

  custom_remove_if(dog_favourite_ints, "dog_2");

  std::cout << "\nIncomplete list of doogies:\n";
  print_doggys(dog_favourite_ints);

  return 0;
}
