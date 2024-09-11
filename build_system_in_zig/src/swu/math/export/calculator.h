#pragma once

namespace swu::math {

class Calculator {
public:
    virtual double add(double a, double b) const = 0;
    virtual double multiply(double a, double b) const = 0;
    virtual ~Calculator() = default;
};

} // namespace swu::math
