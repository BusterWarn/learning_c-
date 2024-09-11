#pragma once

#include <memory>

#include "process_order.h"
#include "calculator.h"

namespace swu::store {

class ProcessOrderImpl : public ProcessOrder {
public:
    ProcessOrderImpl();
    double calculate_order_total(double price, int quantity) const override;

private:
    std::unique_ptr<swu::math::Calculator> calculator_;
};

} // namespace swu::store
