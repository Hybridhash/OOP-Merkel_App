#include <iostream>

class MerkelMain
{
    public:

    //These are specifications, implementation will be in CPP file.
    MerkelMain(); 
    void init();   
    void printMenu();
    void printHelp();
    void printMarketStats();
    void enterOffer();
    void enterBid();
    void printWallet();        
    void gotoNextTimeframe();
    int getUserOption();
    void processUserOption(int userOption);
};


