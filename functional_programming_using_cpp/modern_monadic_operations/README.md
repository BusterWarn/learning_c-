Not parse of the course, but I thought that it fit pretty well. This explores stringing together multiple monadic operations with maybes / optionals and then mapping them over a list.

The program will take a list of names and convert it to lowercase, snakecase and add cool_ as a prefix. It can fail at multiple stages:
 - Numbers can of course not be converted to lowercase.
 - Full names are required, not only first names.
 - Names starting with 'C' won't really sound that cool.

First it is done in Haskell where these operations are natural.

Compile Haskell and run it:
```shell
ghc -O2 -ferror-spans -threaded -rtsopts -o main_hs.exe .\main.hs
.\main_hs.exe
cool_my_name
cool_alice_wonderland
cool_robert_downey
cool_john_doe
```

Then it is done with more modern C++ using [std::optional](https://en.cppreference.com/w/cpp/utility/optional).
```shell
clang++ -std=c++20 -o main_cpp.exe .\main.cpp
.\main_cpp.exe
cool_my_name
cool_alice_wonderland
cool_robert_downey
cool_john_doe
```


It is also doable with C++20 [std::ranges]().
```shell
clang++ -std=c++20 -DWITH_RANGES -o main_cpp.exe .\main.cpp
.\main_cpp.exe
cool_my_name
cool_alice_wonderland
cool_robert_downey
cool_john_doe
```

However this is not exactly like the Haskell Example. Next step is to use the monadic [std::optional::and_then](https://en.cppreference.com/w/cpp/utility/optional/and_then).