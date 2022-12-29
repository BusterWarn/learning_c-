# GCC [[nodiscard]] interface pointer bug

Exploring https://gcc.gnu.org/bugzilla/show_bug.cgi?id=84476

```
PS \learning_cpp\nodiscard_ptr_bug> clang++ --std=c++20 .\main.cpp
.\main.cpp:21:3: warning: ignoring return value of function declared
      with 'nodiscard' attribute [-Wunused-result]
  s_sp->get_value();
  ^~~~~~~~~~~~~~~
.\main.cpp:24:3: warning: ignoring return value of function declared
      with 'nodiscard' attribute [-Wunused-result]
  s_p->get_value();
  ^~~~~~~~~~~~~~
.\main.cpp:25:3: warning: delete called on 's_api' that is abstract
      but has non-virtual destructor
      [-Wdelete-abstract-non-virtual-dtor]
  delete s_p;
  ^
3 warnings generated.
PS \learning_cpp\nodiscard_ptr_bug> g++ --std=c++20 .\main.cpp
PS \learning_cpp\nodiscard_ptr_bug>
```