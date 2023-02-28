# System include with static analyzers

Have you ever included an external library and for some reason that library does not pass your [static analyzers](https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html), like for example [-Wconversion](https://gcc.gnu.org/wiki/NewWconversion). Maybe it's because you're using the wrong [directory options](https://gcc.gnu.org/onlinedocs/gcc/Directory-Options.html) and adding their directories as search paths with `-I` or `-iquote` instead of `-isystem`.

Compilation output:
```bash
PS learning_cpp\system_include_with_static_analyzers> make normal
clang++ main.cpp -std=c++17 -Wconversion -I inc
In file included from main.cpp:5:
inc/lib.h:7:16: warning: implicit conversion changes signedness: 'unsigned int' to 'int' [-Wsign-conversion]
  return value * 2;
  ~~~~~~ ~~~~~~^~~
inc/lib.h:12:20: warning: implicit conversion changes signedness: 'int' to 'std::uint32_t' (aka 'unsigned int') [-Wsign-conversion]
  return get_stuff(value);
         ~~~~~~~~~ ^~~~~
2 warnings generated.

PS learning_cpp\system_include_with_static_analyzers> make quotes
clang++ main.cpp -std=c++17 -Wconversion -iquote inc
In file included from main.cpp:5:
inc/lib.h:7:16: warning: implicit conversion changes signedness: 'unsigned int' to 'int' [-Wsign-conversion]
  return value * 2;
  ~~~~~~ ~~~~~~^~~
inc/lib.h:12:20: warning: implicit conversion changes signedness: 'int' to 'std::uint32_t' (aka 'unsigned int') [-Wsign-conversion]
  return get_stuff(value);
         ~~~~~~~~~ ^~~~~
2 warnings generated.

PS learning_cpp\system_include_with_static_analyzers> make system
clang++ main.cpp -std=c++17 -Wconversion -isystem inc -DISYSTEM
```