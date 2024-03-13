# Visitor / Pattern Matching in Different Languages

> "The Visitor pattern is the most widely misunderstood pattern in all of Design Patterns, which is really saying something when you look at the software architecture excesses of the past couple of decades."
>
> — [Robert Nystrom, Crafting Interpreters](https://craftinginterpreters.com/representing-code.html)

The visitor pattern is a technique used in object-oriented programming to separate an algorithm from the objects on which it operates. This approach allows for adding new operations to existing object structures without modifying those structures. It's often seen as a way to replicate pattern matching capabilities found in functional programming languages within object-oriented contexts.

## Python - Typical Visitor Pattern

In Python, the visitor pattern involves creating a visitor class that implements a visit method for each type of element that can be "visited". This pattern is useful for operations where the elements to be processed are composed of different types but need to be handled in a specific way based on their type.

**Example Output:**
```
python3 animals.py
Goose says Honk
Horse says Neigh
Camel says Grunt
Fox says Wa-pow
Quokka says Squeak
```

## C++ - std::visit and std::variant

The C++ version demonstrates the use of `std::visit` and `std::variant` from the C++17 standard, offering a 'modern approach' to pattern matching in an object-oriented language. This method allows for type-safe, compile-time polymorphism without inheritance.

[cppreference: std::visit](https://en.cppreference.com/w/cpp/utility/variant/visit)
[cppreference: std::variant](https://en.cppreference.com/w/cpp/utility/variant)

**Example Output:**
```
clang++ -std=c++17 animals.cpp -o animals && ./animals
(c++) 5Goose says Honk
(c++) 5Horse says Neigh
(c++) 5Camel says Grunt
(c++) 3Fox says Wa-pow
(c++) 6Quokka says Squeak
```

## Haskell - Pure Functional Pattern Matching

Haskell implements pattern matching directly into the language syntax, allowing for concise and expressive handling of different data types and structures in a purely functional way.

**Example Output:**
```
ghc -o animals animals.hs && ./animals
(haskell) Goose says Honk
(haskell) Horse says Neigh
(haskell) Camel says Grunt
(haskell) Fox says Wa-pow
(haskell) Quokka says Squeak
```

## Rust - Pattern Matching

Rust uses enum and match for pattern matching, providing a powerful and type-safe way to handle various cases with different data types. This approach is somewhat similar to Haskell's, but it is integrated into Rust's system programming environment.

**Example Output:**
```
rustc animals.rs -o animals && ./animals
(rust) Goose says Honk
(rust) Horse says Neigh
(rust) Camel says Grunt
(rust) Fox says Wa-pow
(rust) Quokka says Squeak
```

