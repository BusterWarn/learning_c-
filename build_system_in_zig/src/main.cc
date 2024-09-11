#include "swu/store/inc/process_order_impl.h"
#include <iostream>

int main() {
    swu::store::ProcessOrderImpl process_order;
    double result = process_order.calculate_order_total(100.0, 5);
    std::cout << "Order total: " << result << std::endl;
    return 0;
}
