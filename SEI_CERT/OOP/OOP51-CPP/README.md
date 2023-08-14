[OOP51-CPP. Do not slice derived objects](https://wiki.sei.cmu.edu/confluence/display/cplusplus/OOP51-CPP.+Do+not+slice+derived+objects)

Exploring the noncompliant and the compliant solutions.

## Noncompliant

```Bash
PS OOP51-CPP> clang++ .\main.cpp
PS OOP51-CPP> .\a.exe
Employee: Joe Smith
Employee: Bill Jones
Employee: Jane Doe
```

With copy removed from Employee so that it won't compile
```Bash
PS OOP51-CPP> clang++ .\main.cpp -D no_copy
.\main.cpp:58:5: error: call to deleted constructor of 'Employee'
  f(coder);
    ^~~~~
.\main.cpp:16:3: note: 'Employee' has been explicitly marked deleted here
  Employee(const Employee&) = delete;             // copy constructor
  ^
.\main.cpp:48:17: note: passing argument to parameter 'e' here
void f(Employee e) {
                ^
.\main.cpp:59:5: error: call to deleted constructor of 'Employee'
  f(typist);
    ^~~~~~
.\main.cpp:16:3: note: 'Employee' has been explicitly marked deleted here
  Employee(const Employee&) = delete;             // copy constructor
  ^
.\main.cpp:48:17: note: passing argument to parameter 'e' here
void f(Employee e) {
                ^
.\main.cpp:60:5: error: call to deleted constructor of 'Employee'
  f(designer);
    ^~~~~~~~
.\main.cpp:16:3: note: 'Employee' has been explicitly marked deleted here
  Employee(const Employee&) = delete;             // copy constructor
  ^
.\main.cpp:48:17: note: passing argument to parameter 'e' here
void f(Employee e) {
                ^
3 errors generated.
```

## Compliant

```Bash
PS OOP51-CPP> clang++ .\main.cpp -D compliant_solution           
PS OOP51-CPP> .\a.exe                                            
Employee: Joe Smith
Employee: Bill Jones
Manager: Jane Doe
Assistant:
        Employee: Bill Jones
```

```Bash
PS OOP51-CPP> clang++ .\main.cpp -D compliant_solution -D no_copy
PS OOP51-CPP> .\a.exe
Employee: Joe Smith
Employee: Bill Jones
Manager: Jane Doe
Assistant:
        Employee: Bill Jones
```