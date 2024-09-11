#pragma once

namespace swu::store {

class ProcessOrder {
public:
    virtual double calculate_order_total(double price, int quantity) const = 0;
    virtual ~ProcessOrder() = default;
};

} // namespace swu::store
