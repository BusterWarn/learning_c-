#include <iostream>
#include <string>

class Employee {
  std::string name;

protected:
  virtual void print(std::ostream &os) const {
    os << "Employee: " << get_name() << std::endl;
  }

public:
  Employee(const std::string &name) : name(name) {}

#ifdef no_copy
  Employee(const Employee&) = delete;             // copy constructor
  Employee& operator=(const Employee&) = delete;  // copy assignment
#endif

  const std::string &get_name() const { return name; }
  friend std::ostream &operator<<(std::ostream &os, const Employee &e) {
    e.print(os);
    return os;
  }
};

class Manager : public Employee {
  Employee assistant;

protected:
  void print(std::ostream &os) const override {
    os << "Manager: " << get_name() << std::endl;
    os << "Assistant: " << std::endl << "\t" << get_assistant() << std::endl;
  }

public:
#ifdef no_copy
  Manager(const std::string &name, const Employee &assistant) : Employee(name), assistant{assistant.get_name()} {}
#else
  Manager(const std::string &name, const Employee &assistant) : Employee(name), assistant(assistant) {}
#endif
  const Employee &get_assistant() const { return assistant; }
};

#ifdef compliant_solution
void f(const Employee& e) {
#else
void f(Employee e) {
#endif
  std::cout << e;
}

int main() {
  Employee coder("Joe Smith");
  Employee typist("Bill Jones");
  Manager designer("Jane Doe", typist);

  f(coder);
  f(typist);
  f(designer);
}