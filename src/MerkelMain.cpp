#include <iostream>
#include "MerkelMain.h"
#include <vector>
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include "OrderBook.h"
#include <stdexcept>
#include <limits>

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

    Wallet.insertCurrency("BTC", 10);

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

void MerkelMain::enterAsk()
{
    std::cout << "Mark and ask - enter the amount: Product,Price, Amount, eg: ETH/BTC,200,0.5 " << std::endl;
    std::string input;
    
    std::getline(std::cin, input); 

    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    if (tokens.size() != 3)
    {
      std::cout <<"Bad input by user " << input << std::endl;      
    }
    else
    {   
        try{
        OrderBookEntry obe = CSVReader::stringToOBE(
            tokens[1],
            tokens[2],
            currentTime,
            tokens[0],
            OrderBookType::ask);
        
        obe.username = "simuser";

        if (Wallet.canFulfillOrder(obe))
        {   
            std::cout << "Wallet Looks good. " << std::endl;
            //Inserting order in the orderbook.
            OrderBook.insertOrder(obe);
        }
        else
        {
            std::cout << "Insufficient Funds. " << std::endl;
                
        }

        
        }catch(const std::exception& e)
        {
            std::cout << "MerkelMain::enterAsk Bad Input: " << std::endl;
        }
    }
    

    std::cout << "You Typed: " << input << std::endl;
}

void MerkelMain::enterBid()
{
     std::cout << "Mark and bid - enter the amount: Product,Price, Amount, eg: ETH/BTC,200,0.5 " << std::endl;
    std::string input;
    
    std::getline(std::cin, input); 

    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    if (tokens.size() != 3)
    {
      std::cout <<" MerkelMain::enterBid | Bad input by user | " << input << std::endl;      
    }
    else
    {   
        try{
        OrderBookEntry obe = CSVReader::stringToOBE(
            tokens[1],
            tokens[2],
            currentTime,
            tokens[0],
            OrderBookType::bid);

        obe.username = "simuser";

        if (Wallet.canFulfillOrder(obe))
        {   
            std::cout << "Wallet Looks good. " << std::endl;
            //Inserting order in the orderbook.
            OrderBook.insertOrder(obe);
        }
        else
        {
            std::cout << "Insufficient Funds. " << std::endl;
                
        }

        
        }catch(const std::exception& e)
        {
            std::cout << "MerkelMain::enterBid |Bad Input| : " << std::endl;
        }
    }
    

    std::cout << "You Typed: " << input << std::endl;


}

void MerkelMain::printWallet()
{
    std::cout << Wallet.toString() << std::endl;
}
        
void MerkelMain::gotoNextTimeframe()
{
    std::cout << "Going to next time frame. " << std::endl;

    for (std::string p : OrderBook.getKnownProducts()) 
    
    {

        std::vector <OrderBookEntry> sales = OrderBook.matchAsksToBids(p, currentTime);

        std::cout << "Sales: " << sales.size() << std::endl;

        for (OrderBookEntry& sale:sales)
        {
            std::cout << "Sale Price: " <<sale.price << " amount: " << sale.amount << std::endl;
            if (sale.username == "simuser")
            {
                //Update the Wallet
                Wallet.processSale(sale);

            }
        }

    }
    currentTime = OrderBook.getNextTime(currentTime);
}
 
int MerkelMain::getUserOption()
{
    int userOption = 0;
    std::string line;
    std::cout << "Type in 1-6" << std::endl;
    std::getline (std::cin, line);
    try{
        //to get the error getline is provided with cin and that line is converted to integer.
        userOption = std::stoi(line);
    }catch(const std::exception& e)
    {
        //
    }
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
        enterAsk();
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
