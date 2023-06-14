# Visitor State Machine.

A "modern" take on a state machine. This utilizes the visitor template magic explored in [Correct By Construction](../correct_by_construction/README.md).

Output:
```shell
PS learning_cpp\visitor_state_machine> clang++ --std=c++17 .\main.cpp
PS learning_cpp\visitor_state_machine> .\a.exe
State is A
I don't care what state this is
I don't care what state this is
State is D. Previous state: c
I don't care what state this is
State is D. Previous state: b
I don't care what state this is
I don't care what state this is
```