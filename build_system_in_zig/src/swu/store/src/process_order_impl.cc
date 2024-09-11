#include "process_order_impl.h"
#include "calculator_impl.h"

namespace swu::store {

ProcessOrderImpl::ProcessOrderImpl() : calculator_(std::make_unique<swu::math::CalculatorImpl>()) {}

double ProcessOrderImpl::calculate_order_total(double price, int quantity) const {
    return calculator_->multiply(price, static_cast<double>(quantity));
}

} // namespace swu::store
