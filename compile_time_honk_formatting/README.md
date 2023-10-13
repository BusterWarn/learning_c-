# Goose Honking in C++, calculated at compile time.

A small example of a `goose` class that honks in different ways, with neatly formatted output. The strings are all known at compile time, thus we calculate padding at compile time as well.

### Compile:

```powershell
g++ -std=c++20 .\main.cpp
```

### Run:
```powershell
PS compile_time_honk_formatting> .\a.exe
Happy Honk!          honk
Sad Honk...          hoonk
EMERGENCY HONK!!     honk honk hooooonk
Relaxed honk.        honk
```

## C++ Concepts Covered

1. **Compile-time Computations**: The program uses `constexpr` to perform certain operations at compile time, ensuring efficiency.
   
5. **C++20 Features**: Mostly ranges stl library.
   
6. **IO Manipulation**: The program uses IO manipulators like [`std::left`](https://en.cppreference.com/w/cpp/io/manip/left) and [`std::setw`](https://en.cppreference.com/w/cpp/io/manip/setw) to format the output neatly `(✿◠‿◠)`.