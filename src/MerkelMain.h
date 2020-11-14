#pragma once

#include <vector>
#include "OrderBookEntry.h"

class MerkelMain
{
    public:

    //These are specifications, implementation will be in CPP file.
    MerkelMain(); 
    /**Call this to start the sim*/
    void init();

    private:
    void loadOrderBook();   
    void printMenu();
    void printHelp();
    void printMarketStats();
    void enterOffer();
    void enterBid();
    void printWallet();        
    void gotoNextTimeframe();
    int getUserOption();
    void processUserOption(int userOption);

    //Making the vector accessible for all the function in private but not accessible from public main app. Object Scope Variable
    std::vector<OrderBookEntry> orders;
};


