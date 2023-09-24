# Evaluating the Effectiveness of Automated Fuzz Testing in Uncovering Security Vulnerabilities in C++ Libraries


### Objective:
To investigate the extent to which automated fuzz testing can identify and help mitigate security vulnerabilities and extend branch coverage in C++ libraries.

---

### Main Thesis Questions:

- How many Security Vulnerabilities can be found with fuzz testing?
  - How does fuzz testing compare to modern static analyzer tools?
  - How does different fuzz tester libraries compare to each other?
- How comprehensive is automated fuzz testing in achieving code coverage for C++ libraries?

---

### Methodology:

1. Identify or create a test library with known vulnerabilities.
   - If an existing vulnerable library is available, it may serve as a benchmark for comparison with other studies.
   - In the absence of a suitable library, a synthetic one can be generated, possibly utilizing ChatGPT.

2. Utilize fuzz testing tools like [LLVM LibFuzzer](https://www.llvm.org/docs/LibFuzzer.html) or alternative fuzzers such as [American Fuzzy Lop](https://github.com/google/AFL).

3. Analyze the results. Detail the specific metrics to be assessed, such as types of vulnerabilities, code coverage, and severity levels.

---

### Measurable Outcomes:

1. **Code Coverage**: The percentage of code paths exercised during the fuzz testing process, aiming to understand how comprehensive the fuzzing technique is.
   
2. **Vulnerability Count**: The number and types of vulnerabilities discovered, categorized by severity levels (low, medium, high).

---

### Significance:

This research aims to provide empirical data on the effectiveness of automated fuzz testing for C++ libraries. The study will not only shed light on the security gaps often left undetected but also offer best practices for implementing fuzz testing in C++ development workflows.

### Challanges:

1. **Benchmark for comparison**: If a library contains a plethora of vulnerabilities, should the focus solely be on the efficiency of the fuzz testing? Alternatively, can various fuzz testing tools be compared against each other or against the findings of industry professionals?
  
2. **Branch Coverage**: Should the aim be to achieve 100% branch coverage, and what should serve as the point of comparison?

3. **Tool Selection**: Is LLVM LibFuzzer sufficiently comprehensive, or should other testing frameworks like [Gtest](https://google.github.io/googletest/) or [Catch2](https://github.com/catchorg/Catch2) be integrated? What tools are picked for branch coverage and static code analysis etc.?

4. **Time Complexity**: Some fuzz tests can run indefinitely; determining a cut-off point for testing may be a challenge.
  
5. **False Positives/Negatives**: Filtering out false positives and negatives without missing critical vulnerabilities.
  
6. **Reproducibility**: Ensuring the vulnerabilities found are easily reproducible for validation.

7. **Resource Consumption**: Fuzz testing often requires a substantial amount of computational power and memory.
  
8. **Analysis Overhead**: The time and tools required to analyze large volumes of generated test data could be extensive.

9. **Data Privacy**: In case real-world libraries are used, handling sensitive or proprietary code might be a concern.

---

#### Alternative question

Is it possible to discover new vulnerabilities in widely-acknowledged C++ libraries?

Some examples:
1. [Boost](https://www.boost.org/)
2. [OpenCV](https://opencv.org/)
3. [Qt](https://www.qt.io/)
4. [POCO](https://pocoproject.org/)
5. [Cinder](https://libcinder.org/)
6. [SFML](https://www.sfml-dev.org/)
7. [wxWidgets](https://www.wxwidgets.org/)
8. [Eigen](http://eigen.tuxfamily.org/)
9. [Ogre3D](https://www.ogre3d.org/)
10. [CryEngine](https://www.cryengine.com/)
11. [Asio](https://think-async.com/)
12. [Dlib](http://dlib.net/)
13. [JUCE](https://juce.com/)
14. [Thrust](https://thrust.github.io/)
15. [GSL](https://github.com/microsoft/GSL)
16. [CGAL](https://www.cgal.org/)
17. [Botan](https://botan.randombit.net/)
18. [jsoncpp](https://github.com/open-source-parsers/jsoncpp)
19. [Cocos2d-x](https://www.cocos.com/en/)
20. [Glib](https://developer.gnome.org/glib/)

---

### Prior Research to look at:

1. Security vulnerabilities in C++ codebases
2. Efficacy of static analyzers vs dynamic testing
3. Modern fuzz testing methodologies
4. Application of LLVM LibFuzzer in security testing
5. Code coverage metrics in fuzz testing
6. Vulnerability discovery in open-source libraries
7. Automated testing in CI/CD pipelines
8. Types of vulnerabilities most commonly found in C++ libraries
9. Studies comparing fuzz testing tools
10. Memory safety in compiled languages
