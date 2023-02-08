#include <iostream>
#include <compare>

class A
{
public:
  A(const int value) : m_value(value) {};
  
#if (__cplusplus >= 202002)

  auto operator<=>(const A&) const = default;

#else
  friend inline bool operator==(const A& lhs, const A& rhs) { return lhs.m_value == rhs.m_value; }
  friend inline bool operator!=(const A& lhs, const A& rhs) { return !(lhs == rhs); }
  friend inline bool operator< (const A& lhs, const A& rhs) { return lhs.m_value < rhs.m_value; }
  friend inline bool operator> (const A& lhs, const A& rhs) { return rhs < lhs; }
  friend inline bool operator<=(const A& lhs, const A& rhs) { return lhs.m_value <= rhs.m_value; }
  friend inline bool operator>=(const A& lhs, const A& rhs) { return rhs <= lhs; }
#endif

private:
  int m_value;
};


#if (__cplusplus >= 202002)
class B
{
public:
  B(const int value_1, const int value_2) : m_value_1(value_1), m_value_2(value_2) {};
  

  auto operator<=>(const B&) const = default;

private:
  int m_value_1;
  int m_value_2;
};
#endif


auto main() -> int
{
  A a_1(1);
  A a_2(2);

  std::cout << "a_1 == a_2: " << (a_1 == a_2 ? "true" : "false") << '\n';
  std::cout << "a_1 != a_2: " << (a_1 != a_2 ? "true" : "false") << '\n';
  std::cout << "a_1 > a_2: "  << (a_1 > a_2 ? "true" : "false") << '\n';
  std::cout << "a_1 >= a_2: " << (a_1 >= a_2 ? "true" : "false") << '\n';
  std::cout << "a_1 < a_2: "  << (a_1 < a_2 ? "true" : "false") << '\n';
  std::cout << "a_1 <= a_2: " << (a_1 <= a_2 ? "true" : "false") << '\n';


#if (__cplusplus >= 202002)
  std::cout << "\n\n";
  B b_1(250, 250);
  B b_2(100, 401);
  std::cout << "b_1 == b_2: " << (b_1 == b_2 ? "true" : "false") << '\n';
  std::cout << "b_1 != b_2: " << (b_1 != b_2 ? "true" : "false") << '\n';
  std::cout << "b_1 > b_2: "  << (b_1 > b_2 ? "true" : "false") << '\n';
  std::cout << "b_1 >= b_2: " << (b_1 >= b_2 ? "true" : "false") << '\n';
  std::cout << "b_1 < b_2: "  << (b_1 < b_2 ? "true" : "false") << '\n';
  std::cout << "b_1 <= b_2: " << (b_1 <= b_2 ? "true" : "false") << '\n';
#endif
}

