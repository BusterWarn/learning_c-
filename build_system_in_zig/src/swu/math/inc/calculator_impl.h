#pragma once
#include "calculator.h"

namespace swu::math {

class CalculatorImpl : public Calculator {
public:
    double add(double a, double b) const override;
    double multiply(double a, double b) const override;
};

} // namespace swu::math
