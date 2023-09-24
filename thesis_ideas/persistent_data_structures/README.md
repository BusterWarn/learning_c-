# Evaluating the Efficiency and Practicality of Implementing Persistent Data Structures in C++: A Comparative Study


### Background

Functional programming paradigms promote the use of immutable data to guarantee predictability and ease of reasoning about the code. In mathematical terms, functions serve as mappings from one set of values (domain) to another (codomain) without modifying the input. Unlike procedural programming, where functions may change the state of the input, functional programming treats functions more like their mathematical counterparts. Persistent Data Structures (PDS) embody this philosophy by preserving previous versions of data, enabling a functional approach to data management. However, C++ lacks native support for PDS, making it challenging to implement functional programming techniques seamlessly.

---

### Objective

To investigate the performance trade-offs and advantages of implementing a Persistent Data Structure (PDS) in C++ and comparing its efficiency against standard C++ containers (e.g., `std::vector` or `std::list`). The study aims to run three different tests:

1. Using `std::transform` on both the standard C++ container and the custom PDS.
2. Implementing a custom `map` function that does not mutate the container but creates a new copy, for both the standard container and the PDS.
3. Comparing `std::transform` on the standard C++ container against our custom `map` function with the PDS.

---

### Main Thesis Questions

1. How does the custom Persistent Data Structure compare in terms of time complexity with standard C++ containers for the same operations?

2. What is the memory overhead of using the custom PDS compared to standard C++ containers?

3. How effective is the custom `map` function in adhering to functional programming principles without sacrificing performance?

4. How compatible is the custom PDS with standard C++ algorithms like `std::transform`?

---

### Measurable Outcomes

1. **Time Complexity**: Measure and compare the time taken for performing the same operations on both the custom PDS and standard C++ containers.

2. **Memory Usage**: Document the amount of memory consumed by both types of containers during the tests.

---

### Methodology

1. **Literature Review**: Comprehensive review of existing literature on Persistent Data Structures, standard C++ containers, and functional programming paradigms.

2. **Design Phase**: Outline the specifications for the custom PDS, including its architecture and API.

3. **Development Phase**: Implement the custom PDS and ensure its compatibility with standard algorithms like `std::transform`. Also, implement the custom `map` function.

4. **Testing Setup**: Establish a testing environment, potentially using Catch2 as the testing framework.

5. **Benchmarking**: Conduct three different tests as outlined in the objectives. Record various performance metrics, including but not limited to time complexity and memory usage.

6. **Data Analysis**: Analyze the recorded metrics and compare them with standard C++ containers.

7. **Conclusions and Recommendations**: Formulate conclusions based on the results and recommend best practices or potential improvements.

---

### Challenges

1. **Implementation Complexity**: Designing and coding a PDS from scratch is a challenging task, requiring a deep understanding of both functional programming principles and C++ language features.

2. **Standard Library Compatibility**: Adapting the PDS to fit with standard algorithms like `std::transform` will require the PDS to implement the standard iterator pattern, which could be a complex undertaking.

3. **Custom Functionality**: Implementing a custom `map` function that adheres to the functional programming paradigm is another hurdle.

4. **Tool Selection**: Choosing appropriate tools for benchmarking and testing. [Catch2](https://github.com/catchorg/Catch2) might be a suitable choice for this purpose.

5. **Benchmark Reliability**: Ensuring that the tests and benchmarks provide a fair comparison between the standard container and the PDS.


6. **Lacking Implementation leading to Unfair Comparisons**: C++ is a tricky language and implementing library features such as a container or a custom `map` function might be one of the harder things to do in the language. Small things like violating the [rule of 0](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#c20-if-you-can-avoid-defining-default-operations-do) can lead to worse time complexity outcomes skewing the results.

7. **Memory Management**: Persistent data structures often require advanced memory handling, which could complicate the implementation.

---

### Prior Research

The research should delve into:

1. Studies that evaluate the efficiency of functional programming paradigms.
2. Papers on the design and implementation of Persistent Data Structures.
3. Comparative studies on container performance in C++.
4. Research on the utility and drawbacks of immutable data.
5. Benchmarking methodologies for container classes.
6. Studies on the adaptation of functional programming concepts in procedural languages.
