Exploring some outputs of "Noncompliant Code Example (std::string::c_str())" from [MEM50-CPP. Do not access freed memory](https://wiki.sei.cmu.edu/confluence/display/cplusplus/MEM50-CPP.+Do+not+access+freed+memory)

Wanted to know if a solution with the following code would result in undefined behaviour or not.
```
display_string(str_func().c_str());
```

Output:
```
learning_cpp/SEI_CERT/MEM/MEM50-CPP$ g++ main.cpp -O3
learning_cpp/SEI_CERT/MEM/MEM50-CPP$ ./a.out 
@�>��
Hello world!
Hello world!
```
