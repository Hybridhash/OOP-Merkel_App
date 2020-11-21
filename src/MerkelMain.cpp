#include <iostream>
#include "MerkelMain.h"
#include <vector>
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include "OrderBook.h"

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

    currentTime = OrderBook.getEarliestTime();

    while(true)
    {
        printMenu();
        input = getUserOption();
        processUserOption(input);
    }

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

    std::cout << "Current time is:  " << currentTime << std::endl;

}

void MerkelMain::printHelp()
{
    std::cout << "Help - your aim is to make money. Analyse the market and make bids and offers. " << std::endl;
}

void  MerkelMain::printMarketStats()
{
    //don't want to change and copy therefore const& is used
    for (std::string const& p : OrderBook.getKnownProducts())

    {
        std::cout << "Products: " << p << std::endl;
        std::vector <OrderBookEntry> entries = OrderBook.getOrders( OrderBookType::ask, 
                                                                    p,
                                                                    currentTime);

        std::cout << "Asks Seen: " << entries.size() << std::endl; 
        
        std::cout << "Max ask: " << OrderBook::getHighPrice(entries) << std::endl;
        std::cout << "Min ask: " << OrderBook::getLowPrice(entries) << std::endl; 
 
    }
    
    // std::cout << "OrderBook contains :  " << orders.size() << " entries"<< std::endl;

    // unsigned int bids = 0;
    // unsigned int asks = 0;
    // //Reference is provided to avoid copying the items in order book and iterate over the items in order book
    // for (OrderBookEntry& e : orders)
    // {
    //     if (e.orderType == OrderBookType::ask)
    //     {
    //         asks++;
    //     }
    //     if (e.orderType == OrderBookType::bid)
    //     {
    //         bids++;
    //     }
    // }

    // std::cout << "OrderBook ask :  " << asks << " OrderBook bids : " << bids << " entries"<< std::endl;

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
    currentTime = OrderBook.getNextTime(currentTime);
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
