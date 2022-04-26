# Redundant constructors

Trying out if destructors add more run time to a program. Inspired by Jason Turner's [C++ Weekly - Ep 154 - One Simple Trick For Reducing Code Bloat](https://youtu.be/D8eCPl2zit4).


The results are... well not really there.

```
learning_cpp/redundant_constructors$ g++ main.cpp -DWITH_DESTRUTOR
learning_cpp/redundant_constructors$ /usr/bin/time ./a.out 
4294962297
11.76user 0.59system 0:12.35elapsed 99%CPU (0avgtext+0avgdata 3752maxresident)k
0inputs+0outputs (0major+410123minor)pagefaults 0swaps
learning_cpp/redundant_constructors$ g++ main.cpp
learning_cpp/redundant_constructors$ /usr/bin/time ./a.out 
4294962297
11.62user 0.53system 0:12.16elapsed 99%CPU (0avgtext+0avgdata 3728maxresident)k
0inputs+0outputs (0major+410123minor)pagefaults 0swaps
```

This is maybe not a big chock. When running the code through https://godbolt.org/ with `armv7-a clang (trunk)` I get 247 lines with and 239 without. However it seems that it might improve the run time by a bit. If so it is still worth it.