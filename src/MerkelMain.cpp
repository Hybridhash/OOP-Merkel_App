#include <iostream>
#include "MerkelMain.h"
#include <vector>
#include "OrderBookEntry.h"


//***Extract from Video****
/* normally the idea that you call a constructor and then that starts the whole program
seems a bit different. I'd rather call the constructor and then code an explicit function to initialize it. */

MerkelMain::MerkelMain()
{

}

void MerkelMain::init()
{
    /*we've got a constructor and an init function, logic behind that is that the constructor is for creating an instance of
    the object and make sure it's ready to be used, and the init is actually to start the object running.*/

    int input;
    while(true)
    {
        printMenu();
        input = getUserOption();
        processUserOption(input);
    }

}

void MerkelMain::loadOrderBook()
{
   orders.push_back(OrderBookEntry {10000,
                                     0.002,
                                     "2020/03/17 17:01:24.884492",
                                     "btc/usdt",
                                     OrderBookType::bid});


   orders.push_back(OrderBookEntry {2000,
                                     0.005,
                                     "2020/03/17 17:01:24.884492",
                                     "btc/usdt",
                                     OrderBookType::bid});
   
   //Instead of declaring the variable we can call the construction within push back


}

//class should be declared after the "void" function declarations.
void MerkelMain::printMenu()
{
    // 1 print help
    std::cout << "1: Print help " << std::endl;
    // 2 print exchange stats
    std::cout << "2: Print exchange stats" << std::endl;
    // 3 make an offer
    std::cout << "3: Make an offer " << std::endl;
    // 4 make a bid 
    std::cout << "4: Make a bid " << std::endl;
    // 5 print wallet
    std::cout << "5: Print wallet " << std::endl;
    // 6 continue   
    std::cout << "6: Continue " << std::endl;

    std::cout << "============== " << std::endl;
}

void MerkelMain::printHelp()
{
    std::cout << "Help - your aim is to make money. Analyse the market and make bids and offers. " << std::endl;
}

void  MerkelMain::printMarketStats()
{
    std::cout << "OrderBook contains :  " << orders.size() << " entries"<< std::endl;
}

void MerkelMain::enterOffer()
{
    std::cout << "Mark and offer - enter the amount " << std::endl;
}

void MerkelMain::enterBid()
{
    std::cout << "Make a bid - enter the amount" << std::endl;
}

void MerkelMain::printWallet()
{
    std::cout << "Your wallet is empty. " << std::endl;
}
        
void MerkelMain::gotoNextTimeframe()
{
    std::cout << "Going to next time frame. " << std::endl;
}
 
int MerkelMain::getUserOption()
{
    int userOption;

    std::cout << "Type in 1-6" << std::endl;
    std::cin >> userOption;
    std::cout << "You chose: " << userOption << std::endl;
    return userOption;
}

void MerkelMain::processUserOption(int userOption)
{
    if (userOption == 0) // bad input
    {
        std::cout << "Invalid choice. Choose 1-6" << std::endl;
    }
    if (userOption == 1) // bad input
    {
        printHelp();
    }
    if (userOption == 2) // bad input
    {
        printMarketStats();
    }
    if (userOption == 3) // bad input
    {
        enterOffer();
    }
    if (userOption == 4) // bad input
    {
        enterBid();
    }
    if (userOption == 5) // bad input
    {
        printWallet();
    }
    if (userOption == 6) // bad input
    {
        gotoNextTimeframe();
    }       
}
