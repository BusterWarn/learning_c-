Exploring some outputs of "Noncompliant Code Example (std::string::c_str())" from [MEM50-CPP. Do not access freed memory](https://wiki.sei.cmu.edu/confluence/display/cplusplus/MEM50-CPP.+Do+not+access+freed+memory)

Wanted to know if a solution with the following code would result in undefined behaviour or not.
```
display_string(str_func().c_str());
```

Output:
```
f_1()
°▬╦çY☻

f_2()
Hello world!

f_3()
Hello world!

e_1()
Construct E
Destruct E
Hello world!

e_2()
Construct E
Hello world!
Destruct E

e_3()
Construct E
Hello world!
Destruct E
```
