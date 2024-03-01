## README.md

This is an algorithmic trading program that uses random data and a moving average crossover strategy to make trades.

The file market_data_simulator.cpp initializes the Stocks (2 stocks currently) and the updatePrices function changes the price
of the stock randomly to simulate market conditions. 

The order_excecution_simulator.cpp is primarily responsible for displaying the trade made along with other relevant details like
the ticker symbol and the excecution price. 

The trading_strategy.cpp file contains the moveing average crossover strategy implementation, along with a menu to get user
inputs and runs the simulation until stopped. 
