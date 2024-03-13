#include <iostream>
#include <string>
#include <variant>
#include <vector>

// Define the Animal variants
struct Goose {};
struct Horse {};
struct Camel {};
struct Fox {};
struct Quokka {};

// Visitor that returns the sound of the animal
class AnimalSoundVisitor {
public:
    std::string operator()(Goose const&) const { return "Honk"; }
    std::string operator()(Horse const&) const { return "Neigh"; }
    std::string operator()(Camel const&) const { return "Grunt"; }
    std::string operator()(Fox const&) const { return "Wa-pow"; }
    std::string operator()(Quokka const&) const { return "Squeak"; }
};

int main() {
    // Create a vector of std::variant with different animal types
    std::vector<std::variant<Goose, Horse, Camel, Fox, Quokka>> animals = {Goose{}, Horse{}, Camel{}, Fox{}, Quokka{}};

    // Iterate over the animals and visit each one to get its sound
    for (auto const& animal : animals) {
        std::string sound = std::visit(AnimalSoundVisitor{}, animal);
        std::visit([&](auto const& a) { std::cout << "(c++) " << typeid(a).name() << " says " << sound << std::endl; }, animal);
    }

    return 0;
}
