#pragma once

#include <vector>
#include "OrderBookEntry.h"
#include "OrderBook.h"
//#include "Wallet.h"
//#include "TradingBot.h"
#include "TradeEngine.h"
#include "TradeCosting.h"
#include "MerkelLog.h"

    class MerkelMain
    {
    public:

    //These are specifications, implementation will be in CPP file.
    //Cosntructor
    MerkelMain(); 
    /**Call this to start the simulation - only public method, rest kept in private*/
    void init();

    private:  
    /**Print the menu options for the user*/
    void printMenu();
    /**Help menu*/
    void printHelp();
    /**Print statistic of the market at any given time frame*/
    void printMarketStats();
    /**Gets the user input from the simulation*/
    int getUserOption();
    /**Process the user input and call the different methods*/
    void processUserOption(int userOption);
    /**to check the number of different time sets in trade book*/
    /** provides ability to user to decide if it should withdraw or contine to next time frame*/
    void autoTrader();
    
    //Making it  accessible for all the function in private but not accessible from public main app.
    /**to get the number of timestamps in orderbook by autotrader*/
    OrderBook OrderBook{"20200317.csv"};
    /**to inser the log  of trades and error on bot trade executions*/
    MerkelLog log;
    /**Creating a object of trade engine class*/
    TradeEngine TradeEngine;
    
};



