#include <iostream>
#include "MerkelMain.h"
#include <vector>
//#include "OrderBookEntry.h"
//#include "CSVReader.h"
#include "OrderBook.h"
#include <stdexcept>
//#include <limits>
//#include "TradingBot.h"
#include <cmath>


MerkelMain::MerkelMain()
{
     
}

void MerkelMain::init()
{
    /*we've got a constructor and an init function, logic behind that is that, the constructor is for creating an instance of
    the object and make sure it's ready to be used, and the init is actually to start the object running.*/

    int input;

    //Getting the user 
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

    // 6 bot simulation Cost display
    std::cout << "6: Simulation Cost  " << std::endl;

    // 7 auto Trading by bot
    std::cout << "7: Activate trading bot " << std::endl;

    // 8 continue   
    std::cout << "8: Continue " << std::endl;

    std::cout << "============== " << std::endl;

    std::cout << "Current time is:  " << TradeEngine.currentTime << std::endl;

}

void MerkelMain::printHelp()
{
    std::cout << "Help - your aim is to make money. Analyse the market and make bids and offers. " << std::endl;
}

void  MerkelMain::printMarketStats()
{
    //don't want to change and copy therefore const& is used
    for (std::string const& p : OrderBook.getKnownProducts())

    {   //Getting the name of the products using the for loop
        std::cout << "Products: " << p << std::endl;
        std::vector <OrderBookEntry> entries = OrderBook.getOrders( OrderBookType::ask, 
                                                                    p,
                                                                    TradeEngine.currentTime);

        //Displaying the number of ask in a selected time frame
        std::cout << "Asks Seen: " << entries.size() << std::endl; 
        //Displaying the maximum and minimum value of ask in a selected time frame
        std::cout << "Max ask: " << OrderBook::getHighPrice(entries) << std::endl;
        std::cout << "Min ask: " << OrderBook::getLowPrice(entries) << std::endl; 
 
    }
       
}

int MerkelMain::getUserOption()
{
    //Initilizing the user option to zero
    int userOption = 0;
    std::string line;
    std::cout << "Type in 1-8" << std::endl;
    //getting the user option using standard library cin
    std::getline (std::cin, line);
    try{
        //to get the error getline is provided with cin and that line is converted to integer.
        userOption = std::stoi(line);
    }catch(const std::exception& e)
    {
        //Displaying the same option again on wrog user input
    }
    std::cout << "You chose: " << userOption << std::endl;
    //returning the user option inserted
    return userOption;
}

void MerkelMain::processUserOption(int userOption)
{
    //Using the if conditions to check the user input for execution
    if (userOption == 0) 
    {
        std::cout << "Invalid choice. Choose 1-8" << std::endl;
    }
    if (userOption == 1) 
    {
        printHelp();
    }
    if (userOption == 2) 
    {
        printMarketStats();
    }
    if (userOption == 3) 
    {
        TradeEngine.enterAsk();
    }
    if (userOption == 4) 
    {
        TradeEngine.enterBid();
    }
    if (userOption == 5) 
    {
        TradeEngine.printWallet();
    }
    if (userOption == 6) 
    {
        TradeEngine.printBotCost();
        
    }
    if (userOption == 7) 
    {
        autoTrader();
        
    }
    if (userOption == 8)
    {
        TradeEngine.gotoNextTimeframe();
    }        
} 

void MerkelMain::autoTrader()
{
    //Displaying to terminal that auto trading has activated
    std::cout << "AutoTrader Activated " << std::endl;

    //Giving the welcome message to the user
    std::cout <<"==============================" << std::endl;
    std::cout <<"Welcome to Merkel Trading Bot" << std::endl;
    std::cout <<"==============================" << std::endl;
    
    //Variable to create a set of time
    std::set<std::string> time;
    //User option for continue to next time frame
    char userOption;
    //Checking the available timestamp in OrderBook and Inserting it to set
    for (OrderBookEntry& e : OrderBook.orders)
        {
            time.insert(e.timestamp);
        }
    //Looping over the set and gettting the user input before moving to next timeframe.
   for (const auto& t : time)
        {   //Calling the bot trading method from the trade engine to execute the trades
            TradeEngine.botTrading();
            
            std::cout <<"==============================" << std::endl;
            //Deciding if user should withdraw its offers or continue
            std::cout << "Enter 'Y' to move next timestamp " << std::endl;
            std::cout << "Enter 'N' to go Main Menu" << std::endl;
            //Getting the user input and validating before moving to next time stamp.
            std::cin >> userOption;
            if (userOption == 'Y')
            {
                //Moving the simuilation to next time frame.
                TradeEngine.gotoNextTimeframe();
                //Looping to next timeframe available in set
                continue;
            }
            else if (userOption == 'N')
            {
                //Breaks the loop and going to mian terminal of simulation
                break;
            }
            else
            {   
                //going to main menu and display the error 
                std::cout << "Bad Input by User" << std::endl;
                //Logging the warning message in salelog csv file
                log.createCSV(log.LogLevelWarning,log.SaleLog, "Bad Input by User - MerkelMain::autoTrader");
                //Breaks the loop and goes to main terminal of simulation
                break;   
            }
        }    
}
