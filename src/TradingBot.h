#pragma once
#include <iostream>
#include <string>
#include "OrderBook.h"
#include <vector>
#include "Wallet.h"

class TradingBot

{
    public:
        TradingBot();

        //function to filter the orders by trading bot considering the currency available in Wallet for a given timeframe
        std::vector<OrderBookEntry> botOrderFilter(std::string product, std::string timesstamp, std::string type);

        //Returns the simple moving average on the given orders
        double SMAPrice(std::vector<OrderBookEntry> orders); 

        //Square Linear Regression
        double SqrLinearRegression(std::vector<OrderBookEntry> orders);

        //Function to automate the orders by bot using the price calculated in SMA/Linear Regression
        void orderProcessing(std::string product); 

        //Function to place the orders by bot using the orderbookentry
        void orderPlacement(double price, 
                            double amount,
                            std::string timestamp,
                            std::string product,
                            OrderBookType orderType);


    private:

        
        std::string currentTime;
        //We can use most of the previously declared in "OrderBook" instead of writing new
        OrderBook OrderBook{"20200317.csv"};
        Wallet Wallet;

};