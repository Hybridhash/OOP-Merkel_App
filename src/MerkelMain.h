#pragma once

#include <vector>
#include "OrderBookEntry.h"
#include "OrderBook.h"
#include "Wallet.h"

    class MerkelMain
    {
    public:

    //These are specifications, implementation will be in CPP file.
    MerkelMain(); 
    /**Call this to start the sim*/
    void init();

    private:  
    void printMenu();
    void printHelp();
    void printMarketStats();
    void enterAsk();
    void enterBid();
    void printWallet();        
    void gotoNextTimeframe();
    int getUserOption();
    void processUserOption(int userOption);

    /**To give the simulation current time*/
    std::string currentTime;

    //Making the vector accessible for all the function in private but not accessible from public main app. Object Scope Variable
    OrderBook OrderBook{"20200317.csv"};
    //std::vector<OrderBookEntry> orders;

    Wallet Wallet;
};


