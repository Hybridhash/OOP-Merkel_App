#include "TradingBot.h"
#include <vector>
#include "OrderBookEntry.h"
#include "OrderBook.h"
#include <iostream>
#include <cmath>

TradingBot::TradingBot()
{

}

std::vector<OrderBookEntry> TradingBot::botOrderFilter(std::string product, std::string timesstamp,std::string type)
{
    //New vector is created to filter the bot orders
    std::vector <OrderBookEntry> orderFilter;
    
    //The order are filtered using the input arguments
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
    //Returning the vector of filtered order book entries.
    return orderFilter;

}

 double TradingBot::SMAPrice(std::vector<OrderBookEntry> orders)
 {
    //Initializing the double for sum and count 
    double sum = 0;
    double count = 0;
    for(const OrderBookEntry& m :orders)
    {   
        //Performing sum on the prices of orders appearing in vector
        sum += m.price;
        //Counting the no of order appearing the vector
        count += 1; 

    }
    //Returning the moving average
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
 

double TradingBot::meanValue(double first, double second)
{
    //Static function to calculate the mean of two input values provided as input argument.
    double averageValue = (first+second)/2;
    //Retunring the mean of two values provided as input to the method
    return averageValue;
}


 
