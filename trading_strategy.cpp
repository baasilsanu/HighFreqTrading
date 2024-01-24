#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include <map>
#include <thread>
#include <chrono>
#include <future>
#include <atomic>
#include "market_data_simulator.h"
#include "order_execution_simulator.h"

const int MOVING_AVERAGE_WINDOW = 5;
std::atomic<bool> isRunning(false);

double calculateMovingAverage(const std::deque<double>& prices) {
    double sum = 0.0;
    for (double price : prices) {
        sum += price;
    }
    return sum / prices.size();
}

void executeTradingStrategy(std::vector<Stock>& stocks, std::map<std::string, std::deque<double>>& priceHistory) {
    for (auto& stock : stocks) {
        priceHistory[stock.symbol].push_back(stock.price);
        if (priceHistory[stock.symbol].size() > MOVING_AVERAGE_WINDOW) {
            priceHistory[stock.symbol].pop_front();
        }

        if (priceHistory[stock.symbol].size() == MOVING_AVERAGE_WINDOW) {
            double movingAverage = calculateMovingAverage(priceHistory[stock.symbol]);
            if (stock.price > movingAverage) {
                executeOrder(stock.symbol, "BUY", stock.price);
            } else if (stock.price < movingAverage) {
                executeOrder(stock.symbol, "SELL", stock.price);
            }
        }
    }
}

void displayMenu() {
    std::cout << "\n--- Trading Simulation Menu ---\n";
    std::cout << "1. Start Simulation\n";
    std::cout << "2. Stop Simulation\n";
    std::cout << "3. Exit\n";
    std::cout << "Enter your choice: ";
}

int getUserChoice() {
    int choice;
    std::cin >> choice;
    return choice;
}

void controlSimulation() {
    displayMenu(); 
    while (true) {
        int choice = getUserChoice();
        switch (choice) {
            case 1:
                isRunning = true;
                std::cout << "Simulation started. Press '2' to stop." << std::endl;
                break;
            case 2:
                isRunning = false;
                std::cout << "Simulation stopped. Press '1' to start or '3' to exit." << std::endl;
                break;
            case 3:
                isRunning = false;
                std::cout << "Exiting the simulation." << std::endl;
                std::exit(0); 
            default:
                std::cout << "Invalid choice. Please try again.\n";
                displayMenu();
                break;
        }
    }
}

int main() {
    std::vector<Stock> stocks;
    std::map<std::string, std::deque<double>> priceHistory;
    initializeStocks(stocks);

    
    std::future<void> futureObj = std::async(std::launch::async, controlSimulation);

    // Main simulation loop
    while (true) {
        if (isRunning) {
            updatePrices(stocks);
            executeTradingStrategy(stocks, priceHistory);
        }
        
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;  
}
