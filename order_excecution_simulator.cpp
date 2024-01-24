#include "order_execution_simulator.h"
#include <iostream>

void executeOrder(const std::string& stockSymbol, const std::string& orderType, double price) {
    std::cout << "Executed " << orderType << " order for " << stockSymbol << " at $" << price << std::endl;
}
