Can you declare templates in your .cc file? Yes, but it's a bit tricky.

```shell
PS template_in_source_file> clang++ -std=c++17 .\main.cpp .\template.cpp
PS template_in_source_file> .\a.exe
Printing... 42
Printing... 4.2
```