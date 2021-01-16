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
    std::string username = "simuser";

    try{
        OrderBookEntry obe =  OrderBookEntry(
            price,
            amount,
            timestamp,
            product,
            orderType);

        obe.username = "simuser";

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
    currentTime = TradingBot.OrderBook.getNextTime(currentTime);
}

void TradeEngine::printWallet()
{
    std::cout << Wallet.toString() << std::endl;
}

void TradeEngine::printBotCost()
{

    std::cout << tradeCosting.todisplayCharges() << std::endl;
}

// void TradeEngine::autoTrader()
// {
//     std::cout << "AutoTrader Activated " << std::endl;
//     tradeorderProcessing("ETH/BTC")

// }

void TradeEngine::orderProcessing(std::string product, double amount)
{
    double userInput = 0;

    std::vector<OrderBookEntry>askSales= TradingBot.botOrderFilter(product,currentTime,"ask");
    std::vector<OrderBookEntry>bidSales= TradingBot.botOrderFilter(product,currentTime,"bid");

    double currentAsk =  TradingBot.SMAPrice(askSales);
    double currentBid =  TradingBot.SMAPrice(bidSales);
    double averagePrice = TradingBot::meanValue(currentAsk,currentBid);
    double expectedPrice = TradingBot.SqrLinearRegression(askSales);


    if (expectedPrice < averagePrice) //Expected prices are less than current ask, we are selling the curency
    {
        std::cout << "Bot Ask || Future Expected Price : "<< expectedPrice << " is Less than : " << averagePrice << std::endl;

        //std::vector <OrderBookEntry> expectedSales = TradingBot.OrderBook.matchAsksToBids(product, currentTime);

        //std::cout << "Expected Sales " << expectedSales.size() << std::endl;

        std::cin >> userInput; 

        if (userInput == 1)        
        {
            std::cout<< "Ask Price: " << currentBid << std::endl;
            std::cout<< "Ask Amount: " << amount << std::endl;
            botOrderPlacement(currentBid,amount,currentTime,product,OrderBookType::ask);
            
        }
    } 
    else if (expectedPrice > averagePrice) //Expected prices are higher than current ask, we are buying the curency
    {   
        std::cout << "Bot Bid || Future Expected Price : "<< expectedPrice << " is higher than : " << averagePrice << std::endl;

        //std::vector <OrderBookEntry> expectedSales = TradingBot.OrderBook.matchAsksToBids(product, currentTime);

        //std::cout << "Expected Sales " << expectedSales.size() << std::endl;

        std::cin >> userInput;

        std::cout<< "Bid Price: " << currentAsk * double(1.05) << std::endl;
        std::cout<< "Bid Amount: " << amount << std::endl;
        botOrderPlacement((currentAsk * double(1.05)),amount,currentTime,product,OrderBookType::bid);
        
    }
    else
    {
        std::cout<< "Expected price matches the ask: " << currentAsk << std::endl;
    }

}

void TradeEngine::botTrading()
{
    std::cout << "Trading Bot Time : " << currentTime << std::endl;

    for (std::string p : TradingBot.OrderBook.getKnownProducts())
        {
    
            //std::cout << "KnownProduct: " << p << std::endl;
            //std::cout << "Currency Amount: " << Wallet.checkWallet(p) * .80 << std::endl;
            if  (Wallet.checkWallet(p) > 0)
            {
                std::cout << "-------------------------------"<< std::endl;
                std::cout << "Order Is Initiated for " << p << std::endl;
                std::cout << "-------------------------------"<< std::endl; 
                orderProcessing(p,Wallet.checkWallet(p));
            }
        }

    appRefresh();
}

void TradeEngine::appRefresh()
{
    for (std::string p : TradingBot.OrderBook.getKnownProducts()) 
    
    {
        std::cout << "matching " << p << std::endl;
        std::vector <OrderBookEntry> sales = TradingBot.OrderBook.matchAsksToBids(p, currentTime);
        std::cout << "Sales: " << sales.size() << std::endl;

        if (sales.size() > 0)
        {
            tradeCosting.tradeCalculator(sales.size());
        }

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
}
   
//     double averagePrice = currentBid+ 

//     std::cout <<"==============================" << std::endl;
//     std::cout <<"Welcome to Merkel Trading Bot" << std::endl;
//     std::cout <<"==============================" << std::endl;
    
    
    
//     std::set<std::string> time;

//     char userOption = 'Y';
    
//     for (OrderBookEntry& e : OrderBook.orders)
//         {
//             time.insert(e.timestamp);
//         }

//    for (const auto& t : time)
//         {
            
//             std::cout << t << std::endl;
//             std::cout << "Enter 'Y' to next timestamp: " << std::endl;
//             std::cin >> userOption;
//             if (userOption == 'Y')
//             continue;
//             if (userOption == 'N')
//             break;
//         }

//}



