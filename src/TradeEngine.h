#pragma once
#include <iostream>
#include <vector>
#include "OrderBook.h"
#include "OrderBookEntry.h"
#include "Wallet.h"
#include "TradingBot.h"
#include "TradeCosting.h"

class TradeEngine

{
    public:

        //Constructor Function
        TradeEngine();
        //To place the orders by bot using the orderbookentry*/
        void botOrderPlacement(double price, 
                            double amount,
                            std::string timestamp,
                            std::string product,
                            OrderBookType orderType);

        void appRefresh();
        void enterBid();
        void enterAsk();
        void gotoNextTimeframe();
        void printWallet();
        void autoTrader();
        void printBotCost();
        
        std::string currentTime;
        //OrderBook OrderBook{"Test.csv"};

        //Function to automate the orders by bot using the price calculated in SMA/Linear Regression
        void orderProcessing(std::string product, double amount); 

        //Function to check the possiblity of tarde before executing.
        void botTrading();



    private:

        tradeCosting tradeCosting;    
        TradingBot TradingBot;      
        Wallet Wallet;
};