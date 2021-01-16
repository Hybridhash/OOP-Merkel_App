#pragma once
#include <iostream>
#include <string>
#include "OrderBook.h"
#include <vector>
#include "Wallet.h"


class TradingBot

{
    public:
        /**Constructor inside the trading bot class*/
        TradingBot();

        //To filter the orders by trading bot considering the currency available in Wallet for a given timeframe
        std::vector<OrderBookEntry> botOrderFilter(std::string product, std::string timesstamp, std::string type);

        //Returns the simple moving average on the given orders
        double SMAPrice(std::vector<OrderBookEntry> orders); 

        /**Method to price the price using Square Linear Regression*/
        double SqrLinearRegression(std::vector<OrderBookEntry> orders);
        
        /**Static functiont to calculate the mean of two inputs values*/
        static double meanValue(double first, double second);

        /**Object of the orderbook class is instanciated*/
        
        OrderBook OrderBook{"20200317.csv"};

    private:
        

        /**Object of the wallet Class is instanciated*/
        Wallet Wallet;

        

};