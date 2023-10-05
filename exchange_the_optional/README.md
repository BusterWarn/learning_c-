## Exchange The Optional

Just a quick example of how you can use [std::exchange](https://en.cppreference.com/w/cpp/utility/exchange) passing in an [std::optional](https://en.cppreference.com/w/cpp/utility/optional) and clearing the value at the same time.

```shell
PS exchange_the_optional> clang++ .\main.cpp
PS exchange_the_optional> .\a.exe
Has value: true
Value: 3.14
No value.
Has value: false
```