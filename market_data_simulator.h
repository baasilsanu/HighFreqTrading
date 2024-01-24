#ifndef MARKET_DATA_SIMULATOR_H
#define MARKET_DATA_SIMULATOR_H

#include <vector>
#include <string>

struct Stock {
    std::string symbol;
    double price;
};

void initializeStocks(std::vector<Stock>& stocks);
void updatePrices(std::vector<Stock>& stocks);

#endif
