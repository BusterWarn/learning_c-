
#include <algorithm>
#include <vector>
#include <iostream>
#include <ranges>
#include <iterator>
#include <numeric>
#include <span>
#include <string>
#include <string_view>

// #define CPP_17
#define CPP_20
// #define GET_AUTO
// #define CAN_CANT_DO
// #define WILL_NOT_COMPILE

const auto is_even = [](int number) { return number % 2 == 0; };
const auto square = [](int number) { return number * number; };

std::vector<int> get_vector()
{
  return {2, 3, 6, 1, 10, -3, 77, 3, 2};
}

std::span<int> get_span()
{
  static int arr[] = { 1, 2, 3 };
  return std::span(arr);
}

void get_auto_type()
{
  auto vec = get_vector();
#ifdef GET_AUTO

  // __gnu_cxx::__normal_iterator<int*, std::vector<int> >
  int range = std::ranges::min_element(vec.begin(), vec.end());

  // std::ranges::filter_view<std::ranges::ref_view<std::vector<int> >, <lambda(int)> >
  int filter = vec | std::views::filter(is_even);

  // std::ranges::filter_view<std::ranges::ref_view<std::vector<int> >, <lambda(int)> >
  int v1 = vec | std::views::transform(square);

  // std::ranges::transform_view<std::ranges::ref_view<std::vector<int> >, <lambda(int)> >
  int v2 = get_span() | std::views::transform(square);

  // std::ranges::transform_view<std::ranges::subrange<__gnu_cxx::__normal_iterator<int*, std::vector<int> >, __gnu_cxx::__normal_iterator<int*, std::vector<int> >, std::ranges::subrange_kind::sized>, <lambda(int)> >
  int v3 = std::ranges::subrange(vec.begin(), vec.end()) | std::views::transform(square);


#else
  // Can compile :D
  __gnu_cxx::__normal_iterator<int*, std::vector<int> > range = std::ranges::min_element(vec.begin(), vec.end());

  // Could not get to compile
  // std::ranges::filter_view<std::ranges::ref_view<std::vector<int> >, <lambda(int)> > filter = vec | std::views::filter(is_even);

  // Could not get to compile
  // std::ranges::filter_view<std::ranges::ref_view<std::vector<int> >, <lambda(int)> > v1 = vec | std::views::transform(square);

  // Could not get to compile
  // std::ranges::transform_view<std::span<int>, <lambda(int)> > v2 = get_span() | std::views::transform(square);

  // Could not get to compile
  // std::ranges::transform_view<std::ranges::subrange<__gnu_cxx::__normal_iterator<int*, std::vector<int> >, __gnu_cxx::__normal_iterator<int*, std::vector<int> >, std::ranges::subrange_kind::sized>, <lambda(int)> > v3 = std::ranges::subrange(vec.begin(), vec.end()) | std::views::transform(square);
#endif
}

// All code here is stolen from Tristan Brindle at CppCon 2020
void test_borrowed_range()
{
  // compiles into std::ranges::dangling which is an empty struct with no operations.
  auto iter = std::ranges::min_element(get_vector());

#ifdef WILL_NOT_COMPILE
  std::cout << "min element: " << *iter << '\n';
#endif

  std::string str = "Hello world";
  // Weird, but okay:
  auto iter2 = std::string_view{str}.begin();
  // Did not work
  // *iter2 = 'h';
}

#ifdef CPP_17
int find_min_value(std::vector<int>& vec)
{
  auto iter = std::min_element(vec.begin(), vec.end());
  return *iter;
}

int find_min_even_value(std::vector<int> vec)
{
  std::vector<int> even_numbers;
  std::copy_if(vec.begin(), vec.end(),
               std::back_inserter(even_numbers),
               is_even);

  std::vector<int> squared;
  std::transform(even_numbers.begin(), even_numbers.end(),
                 std::back_inserter(squared),
                 square);

  return *std::min_element(squared.begin(), squared.end());
}
#endif

#ifdef CPP_20
int find_min_value(std::vector<int> vec)
{
  auto iter = std::ranges::min_element(vec);
  return *iter;
}

int find_min_even_value(std::vector<int> vec)
{
  auto view = vec | std::views::filter(is_even)
                  | std::views::transform(square);

  // How can we include this in the |
  return *std::ranges::min_element(view);
}
#endif


void funky_func()
{
#ifdef CAN_CANT_DO
  // get_vector() returns an r value vector
  auto vec = get_vector();

  // Okay: vec is an lvalue
  auto v1 = vec | std::views::transform(is_even);

  // get_span() returns an rvalue span
  // Okay: span is a borrowed range (and usually a view)
  // auto v2 = get_span() : std::views::transform(func);

  // Okay: rvalue subrange is borrowed (and a view)
  auto v3 = std::ranges::subrange(vec.begin(), vec.end())
            | std::views::transform(is_even);

  // ERROR: get_vector() returns an rvalue vector, which is neither a view nor
  // a borrowed range
  // Will generate a cryptic error messasge at compile time.
  auto v4 = get_vector() | std::views::transform(is_even);
#endif
}



int main(void)
{
  std::cout << "my vec: { ";
  for (int my_int : get_vector())
  {
    std::cout << my_int << " " ;
  }
  std::cout << "}\n";

  std::cout << "Smallest element: " << find_min_value(get_vector()) << '\n';
  std::cout << "Smallest even squared element: " << find_min_even_value(get_vector()) << '\n';

  get_auto_type();
  funky_func();

  return 0;
}