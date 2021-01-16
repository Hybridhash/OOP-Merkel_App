#include "TradeEngine.h"

TradeEngine::TradeEngine()

{
    //Updating the current time of the trade engine using the object intanciated under trading bot class
    currentTime = TradingBot.OrderBook.getEarliestTime();
    //Inserting the currency to the wallet.
    Wallet.insertCurrency("BTC", 1000);
    Wallet.insertCurrency("ETH", 1000);
}

void TradeEngine::botOrderPlacement(double price, 
                                double amount,
                                std::string timestamp,
                                std::string product,
                                OrderBookType orderType)
{
    //Declaring the user name as trading bot
    std::string username = "simuser";

    try{
        //Making a order book entry based in input arguments
        OrderBookEntry obe =  OrderBookEntry(
            price,
            amount,
            timestamp,
            product,
            orderType);

        obe.username = "simuser";

        //Checking against the wallet before inserting the order to order book
        if (Wallet.canFulfillOrder(obe))
        {   
            //Displaying the status of oder on terminal
            std::cout << "Trading Bot || Wallet Looks good. " << std::endl;
            //Inserting order in the orderbook.
            TradingBot.OrderBook.insertOrder(obe);
            //Logging the orders execution by Bot
            log.createCSV(log.logLevelinfo, log.OrderLog, 
            product + "," + std::to_string (price) + ","
            + std::to_string (amount) +  " - Bot Order Executed ");
            
        }
        else
        {   //Displaying the status of oder on terminal
            std::cout << "Trading Bot || Insufficient Funds. " << std::endl;
                
        }

        
        }catch(const std::exception& e) // Catching error n wront input
        {
            //Inserting the log of bad input, which is rare to happend
            log.createCSV(log.LogLevelWarning,log.OrderLog, 
            " Bad Input by bot - TradingBot::orderPlacement");
        }

}

void TradeEngine::enterAsk()
{
    std::cout << "Mark and ask - enter the amount: Product,Price, Amount, eg: ETH/BTC,200,0.5 " << std::endl;
    //string for manual input by the user
    std::string input;
    //Getline extarct the complete line written by the user
    std::getline(std::cin, input); 
    //parsing over the line and dividing into different components using the , as delimiter
    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    if (tokens.size() != 3)
    {
      std::cout <<"Bad input by user " << input << std::endl; 
      //Inserting the wrong entru to log file
      log.createCSV(log.LogLevelWarning, log.OrderLog, 
                "Bad input by user - TradeEngine::enterAsk");    
    }
    else
    {   
        try{
        //Converting the string to order book entry
        OrderBookEntry obe = CSVReader::stringToOBE(
            tokens[1],
            tokens[2],
            currentTime,
            tokens[0],
            OrderBookType::ask);
        
        obe.username = "simuser";

        if (Wallet.canFulfillOrder(obe))
        {   
            //Displaying the status of the wallet
            std::cout << "Wallet Looks good. " << std::endl;
            //Inserting order in the orderbook.
            TradingBot.OrderBook.insertOrder(obe);
            //Inserting the log of order
            log.createCSV(log.logLevelinfo, log.OrderLog, input + " - TradeEngine::enterAsk");
            //Matching the bid to sale
            appRefresh();
        }
        else
        {   //Displaying the status of the wallet
            std::cout << "Insufficient Funds. " << std::endl;
                
        }

        
        }catch(const std::exception& e)
        {
            std::cout << "Bad Input: " << std::endl;
            //Entering the warning log to the file
            log.createCSV(log.LogLevelWarning, log.OrderLog, 
                           "Bad Input by user - MerkelMain::enterAsk" );
        }
    }
    
    //Displaying the user enter ask 
    std::cout << "You Typed: " << input << std::endl;
}

void TradeEngine::enterBid()
{
    std::cout << "Mark and bid - enter the amount: Product,Price, Amount, eg: ETH/BTC,200,0.5 " << std::endl;
    //string for manual input by the user
    std::string input;
    //Getline extarct the complete line written by the user
    std::getline(std::cin, input); 

    //parsing over the line and dividing into different components using the , as delimiter
    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    if (tokens.size() != 3)
    {
      std::cout <<"Bad input by user | " << input << std::endl;  
      //Inserting the wrong entru to log file
      log.createCSV(log.LogLevelWarning,log.OrderLog,
                "Bad input by user - TradeEngine::enterBid ");    
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
        {   //Displaying the message for user
            std::cout << "Wallet Looks good. " << std::endl;
            //Inserting order in the orderbook.
            TradingBot.OrderBook.insertOrder(obe);
            //Logging the order entered by user
            log.createCSV(log.logLevelinfo, log.OrderLog, input + " - TradeEngine::enterBid");
            //Matching the bid to sale
            appRefresh();
        }
        else
        {   //Displaying the message for user
            std::cout << "Insufficient Funds. " << std::endl;
                
        }

        
        }catch(const std::exception& e)
        {   
            //Displaying the message
            std::cout << "Bad Input by useer: " << std::endl;
            //Inserting the wrong entru to log file
            log.createCSV(log.LogLevelWarning,log.OrderLog,
                "Bad input by user - TradeEngine::enterBid ");  
        }
    }
    

    std::cout << "You Typed: " << input << std::endl;


}

void TradeEngine::gotoNextTimeframe()
{   
    //Displying the message for user
    std::cout << "Going to next time frame. " << std::endl;
    //Updating the sting 
    currentTime = TradingBot.OrderBook.getNextTime(currentTime);
}

void TradeEngine::printWallet()
{
    //Display the currency currently owned
    std::cout << Wallet.toString() << std::endl;
}

void TradeEngine::printBotCost()
{
    //print the cost of simulation
    std::cout << tradeCosting.todisplayCharges() << std::endl;
}


void TradeEngine::orderProcessing(std::string product, double amount)
{
    //Initializing the double 
    double userInput = 0;

    //Filtering the bid or ask sales using the filter arguments (product, time and type)
    std::vector<OrderBookEntry>askSales= TradingBot.botOrderFilter(product,currentTime,"ask");
    std::vector<OrderBookEntry>bidSales= TradingBot.botOrderFilter(product,currentTime,"bid");

    //Checking the moving average of ask and bids for a given time frame
    double currentAsk =  TradingBot.SMAPrice(askSales);
    double currentBid =  TradingBot.SMAPrice(bidSales);
    //Calculating the mean of the both simple moving ask and bid prices
    double averagePrice = TradingBot::meanValue(currentAsk,currentBid);
    //Predicting the future price using square linear method of trading bot
    double expectedPrice = TradingBot.SqrLinearRegression(askSales);


    if (expectedPrice < averagePrice) //Expected prices are less than current ask, we are selling the curency
    {
        //Displaying the expected future price
        std::cout << "Bot Ask || Future Expected Price : "<< expectedPrice << " is Less than : " << averagePrice << std::endl;
        //Displaying the ask price and amount used by bot
        std::cout<< "Ask Price: " << currentBid << std::endl;
        std::cout<< "Ask Amount: " << amount << std::endl;
        //Placing the order for ask type
        botOrderPlacement(currentBid,amount,currentTime,product,OrderBookType::ask);
            
    } 
    else if (expectedPrice >= averagePrice) //Expected prices are higher than current ask, we are buying the curency
    {   
        //Displaying the expected future price
        std::cout << "Bot Bid || Future Expected Price : "<< expectedPrice << " is higher than : " << averagePrice << std::endl;
        //Displaying the ask price and amount used by bot
        std::cout<< "Bid Price: " << currentAsk * double(1.05) << std::endl;
        std::cout<< "Bid Amount: " << amount << std::endl;
        //Placing the order for bid type
        botOrderPlacement((currentAsk * double(1.05)),amount,currentTime,product,OrderBookType::bid);
        
    }
    else
    {
        std::cout<< "Issue encountered during bot trading " << std::endl;
        //Logging the error enountered during the bot trading
        log.createCSV(log.LogLevelWarning,log.OrderLog, 
                     "Issue encountered during bot trading - TradeEngine::orderProcessing");
    }

}

void TradeEngine::botTrading()

{
    //Displaying the bot timing. It given idea for the timeframe in which bot is operating 
    std::cout << "Trading Bot Time : " << currentTime << std::endl;

    //Looping over know products
    for (std::string p : TradingBot.OrderBook.getKnownProducts())
        {
            //Comparing the balance of the wallet for a given product.
            if  (Wallet.checkWallet(p) > 0)
            {
                //Printing the product type for which order is initiated
                std::cout << "-------------------------------"<< std::endl;
                std::cout << "Order Is Initiated for " << p << std::endl;
                std::cout << "-------------------------------"<< std::endl; 
                //Checking the availablity of the funds in the wall.          
                orderProcessing(p,Wallet.checkWallet(p));
                
            }
        }
    //Matching the bids against the sale
    appRefresh();
}

void TradeEngine::appRefresh()
{
    //Looping over the kwown products
    for (std::string p : TradingBot.OrderBook.getKnownProducts()) 
    
    {   //Displaying the message for matching products
        std::cout << "matching " << p << std::endl;
        //Matching the bids against ask
        std::vector <OrderBookEntry> sales = TradingBot.OrderBook.matchAsksToBids(p, currentTime);
        // Displaying the size of sales
        std::cout << "Sales: " << sales.size() << std::endl;

        if (sales.size() > 0)
        {
            //Calculating the cost of simulation
            tradeCosting.tradeCalculator(sales.size());
            //Logging the trade executed by bot
            log.createCSV(log.logLevelinfo, log.SaleLog, p + " Sales : " + std::to_string(sales.size()));
        }

        for (OrderBookEntry& sale:sales)
        {
            //Display the sale price and amount
            std::cout << "Sale Price: " <<sale.price << " amount: " << sale.amount << std::endl;
            if (sale.username == "simuser" || "trading_bot")
            {
                //Update the Wallet
                Wallet.processSale(sale);

            }
        }

    }
}


