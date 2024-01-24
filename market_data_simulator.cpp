#include "market_data_simulator.h"
#include <cstdlib>
#include <thread>
#include <chrono>
#include <iostream>

void initializeStocks(std::vector<Stock>& stocks) {
    stocks.push_back({"AAPL", 150.0});
    stocks.push_back({"MSFT", 250.0});
}

void updatePrices(std::vector<Stock>& stocks) {
    for (auto& stock : stocks) {
        double change = (rand() % 200 - 100) * 0.01;
        stock.price += change;
        if (stock.price < 0) stock.price = 0.01;
    }
}
