#include "TradingBot.h"
#include <vector>
#include "OrderBookEntry.h"
#include "OrderBook.h"
#include <iostream>
#include <cmath>
//#include <stdexcept>

TradingBot::TradingBot()
{

};

std::vector<OrderBookEntry> TradingBot::botOrderFilter(std::string product, std::string timesstamp,std::string type)
{
    std::vector <OrderBookEntry> orderFilter;
    
    if (type == "ask")
    {
    orderFilter = OrderBook.getOrders( OrderBookType::ask,
                                                      product,
                                                      timesstamp);
    }
    else
    {
    orderFilter = OrderBook.getOrders( OrderBookType::bid,
                                                      product,
                                                      timesstamp);
    }
    return orderFilter;

}

 double TradingBot::SMAPrice(std::vector<OrderBookEntry> orders)
 {
    double sum = 0;
    double count = 0;
    for(OrderBookEntry& m :orders)
    {   
        
        sum += m.price;
        count += 1; 
        //std::cout<<"Sale Price: "<<m.price<<" amount: "<<m.amount<<std::endl;

    }

    return sum/count;
 }


double TradingBot::SqrLinearRegression(std::vector<OrderBookEntry> orders)
{
    //Linear Regression
    //x independent Variable = timestamps || Since we are taking lastest ten order from the current timestamp, therefore, n is initialized to 10;
    double n = 10;
    //x square
    double xSqr = 0;
    //sum of 10 timestamps
    double sumX = 0;
    //y dependent variable = prices ||  dependent on the latest 10 orders
    double sumY =0;
    //Sum of x*y
    double sumXY = 0;

    for (int i = 1; i <= n; i++)
    {
        OrderBookEntry& m = orders[i];
        sumX += i;
        sumY += m.price;
        xSqr += pow(i, 2);
        sumXY += (i * m.price);

    }

    //Y = a + bx || trend line 
    //Calculating b (Slop) 
    double b = double ((n * sumXY) - (sumX*sumY))/ 
                        ((n*xSqr) - pow(sumX, 2));

    //Calculating a (intercept)
    double a = double (sumY - (b*sumX)) / n;
                        
    //Calculating the estimated price for future period (i.e. 11)
    return a+(b*11);
}
 
void TradingBot::orderProcessing(std::string product)
{

    std::vector<OrderBookEntry>askSales= botOrderFilter(product,OrderBook.getEarliestTime(),"ask");
    std::vector<OrderBookEntry>bidSales= botOrderFilter(product,OrderBook.getEarliestTime(),"bid");

    double currentAsk =  SMAPrice(askSales);
    double currentBid =  SMAPrice(bidSales);
    double expectedPrice = SqrLinearRegression(askSales);

    std::cout << "SMA ask: " << currentAsk << std::endl;
    std::cout << "SMA bid: " << currentBid << std::endl;

    
    std::cout << "Future Expected Price : "<< expectedPrice << std::endl;
    std::cout << "Trading Bot Time : " << OrderBook.getEarliestTime() << std::endl;

    if (expectedPrice < currentAsk) //Expected prices are less than current ask, we are selling the curency
    {
        orderPlacement(currentAsk,10,OrderBook.getEarliestTime(),product,OrderBookType::bid);
        std::cout<< "Ask Price: " << currentAsk << std::endl;
    } 
    else if (expectedPrice > currentAsk) //Expected prices are higher than current ask, we are buying the curency
    {   
        orderPlacement(currentAsk,10,OrderBook.getEarliestTime(),product,OrderBookType::ask);
        std::cout<< "Bid Price: " << currentBid << std::endl;
    }
    else
    {
        std::cout<< "Expected price matches the ask: " << currentAsk << std::endl;
    }
}


 void TradingBot::orderPlacement(double price, 
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
            OrderBook.insertOrder(obe);
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
