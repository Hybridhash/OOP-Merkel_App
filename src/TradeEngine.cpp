#include "TradeEngine.h"

TradeEngine::TradeEngine()

{
    currentTime = TradingBot.OrderBook.getEarliestTime();
    Wallet.insertCurrency("BTC", 1000);
    Wallet.insertCurrency("ETH", 1000);
}


// void TradeEngine::appRefresh()

// {

//         for (std::string p : TradingBot.OrderBook.getKnownProducts()) 
    
//     {

//         std::vector <OrderBookEntry> sales = TradingBot.OrderBook.matchAsksToBids(p, currentTime);

//         std::cout << "Sales: " << sales.size() << std::endl;

//         for (OrderBookEntry& sale:sales)
//         {
//             std::cout << "Sale Price: " <<sale.price << " amount: " << sale.amount << std::endl;
//             if (sale.username == "simuser" || "trading_bot")
//             {
//                 //Update the Wallet
//                 Wallet.processSale(sale);

//             }
//         }

//     }
//     currentTime = TradingBot.OrderBook.getNextTime(currentTime);
// }

void TradeEngine::botOrderPlacement(double price, 
                                double amount,
                                std::string timestamp,
                                std::string product,
                                OrderBookType orderType)
{
    std::string username = "trading_bot";

    try{
        OrderBookEntry obe =  OrderBookEntry(
            price,
            amount,
            timestamp,
            product,
            orderType,
            username);

        if (Wallet.canFulfillOrder(obe))
        {   
            std::cout << "Trading Bot || Wallet Looks good. " << std::endl;
            //Inserting order in the orderbook.
            TradingBot.OrderBook.insertOrder(obe);
        }
        else
        {
            std::cout << "Trading Bot || Insufficient Funds. " << std::endl;
                
        }

        
        }catch(const std::exception& e)
        {
            std::cout << "TradingBot::orderPlacement |Bad Input| : " << std::endl;
        }
           
}

void TradeEngine::enterAsk()
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
            TradingBot.OrderBook.insertOrder(obe);
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

void TradeEngine::enterBid()
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
            TradingBot.OrderBook.insertOrder(obe);
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

void TradeEngine::gotoNextTimeframe()
{
    std::cout << "Going to next time frame. " << std::endl;

    //appRefresh();
    for (std::string p : TradingBot.OrderBook.getKnownProducts()) 
    
    {
        std::cout << "matching " << p << std::endl;
        std::vector <OrderBookEntry> sales = TradingBot.OrderBook.matchAsksToBids(p, currentTime);
        std::cout << "Sales: " << sales.size() << std::endl;

        for (OrderBookEntry& sale:sales)
        {
            std::cout << "Sale Price: " <<sale.price << " amount: " << sale.amount << std::endl;
            if (sale.username == "simuser" || "trading_bot")
            {
                //Update the Wallet
                Wallet.processSale(sale);

            }
        }

    }
    currentTime = TradingBot.OrderBook.getNextTime(currentTime);
}

void TradeEngine::printWallet()
{
    std::cout << Wallet.toString() << std::endl;
}


// void TradeEngine::autoTrader()
// {
//     std::cout << "AutoTrader Activated " << std::endl;
//     tradeorderProcessing("ETH/BTC")

// }

void TradeEngine::orderProcessing(std::string product, double amount)
{

    std::vector<OrderBookEntry>askSales= TradingBot.botOrderFilter(product,TradingBot.OrderBook.getEarliestTime(),"ask");
    std::vector<OrderBookEntry>bidSales= TradingBot.botOrderFilter(product,TradingBot.OrderBook.getEarliestTime(),"bid");

    double currentAsk =  TradingBot.SMAPrice(askSales);
    double currentBid =  TradingBot.SMAPrice(bidSales);
    double averagePrice = (currentAsk+currentBid)/2;
    double expectedPrice = TradingBot.SqrLinearRegression(askSales);

    std::cout << "SMA ask: " << currentAsk << std::endl;
    std::cout << "SMA bid: " << currentBid << std::endl;

    
    std::cout << "Future Expected Price : "<< expectedPrice << std::endl;
    std::cout << "Trading Bot Time : " << TradingBot.OrderBook.getEarliestTime() << std::endl;

    if (expectedPrice < averagePrice) //Expected prices are less than current ask, we are selling the curency
    {
        botOrderPlacement(averagePrice,amount,TradingBot.OrderBook.getEarliestTime(),product,OrderBookType::bid);
        std::cout<< "Ask Price: " << currentBid << std::endl;
    } 
    else if (expectedPrice > averagePrice) //Expected prices are higher than current ask, we are buying the curency
    {   
        botOrderPlacement((averagePrice * double(1.05)),amount,TradingBot.OrderBook.getEarliestTime(),product,OrderBookType::ask);
        std::cout<< "Bid Price: " << currentAsk << std::endl;
    }
    else
    {
        std::cout<< "Expected price matches the ask: " << currentAsk << std::endl;
    }

    gotoNextTimeframe();

}


void TradeEngine::tradeChecker(std::string product, double amount)
{


    for (std::string p : TradingBot.OrderBook.getKnownProducts()) 
    
    {
        std::cout << "matching " << p << std::endl;
        std::vector <OrderBookEntry> sales = TradingBot.OrderBook.matchAsksToBids(p, currentTime);
        std::cout << "Sales: " << sales.size() << std::endl;

        for (OrderBookEntry& sale:sales)
        {
            std::cout << "Sale Price: " <<sale.price << " amount: " << sale.amount << std::endl;
            if (sale.username == "simuser" || "trading_bot")
            {
                //Update the Wallet
                //Wallet.processSale(sale);

            }
        }

    }

}