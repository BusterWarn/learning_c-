Not parse of the course, but I thought that it fit pretty well. This explores stringing together multiple monadic operations with maybes / optionals and then mapping them over a list.

The program will take a list of names and convert it to lowercase, snakecase and add cool_ as a prefix. It can fail at multiple stages:
 - Numbers can of course not be converted to lowercase.
 - Full names are required, not only first names.
 - Names starting with 'C' won't really sound that cool.

First it is done in Haskell where these operations are natural.

Compile Haskell:
```shell
ghc -O2 -ferror-spans -threaded -rtsopts -o main_hs.exe .\main.hs
```

And run it:
```shell
.\main_hs.exe
["cool_my_name","cool_mary","cool_alice_wonderland","cool_robert_downey","cool_joey","cool_john_doe"]
```

Then it is done with modern C++.