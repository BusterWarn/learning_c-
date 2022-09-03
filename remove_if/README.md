# C++ 20 map erase_if vs previos versions 

Recently had a problem where I wanted to remove an element in a map. Found the awesome function [std::erase_if](https://en.cppreference.com/w/cpp/container/map/erase_if) but soon realized it is only available in C++20 or later. In previous versions [std::remove_if](https://en.cppreference.com/w/cpp/algorithm/remove) is available however:

"These algorithms cannot be used with associative containers such as std::set and std::map because their iterator types do not dereference to MoveAssignable types (the keys in these containers are not modifiable)."

Sigh. So the best way to make it in C++17 or below i found is to use iterators in a for loop.