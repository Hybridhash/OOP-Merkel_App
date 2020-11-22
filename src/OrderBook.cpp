#include "OrderBook.h"
#include "CSVReader.h"
#include "map"
#include <algorithm>

/**Construct, reading a csv data file*/
OrderBook::OrderBook(std::string fileName)
{
    orders = CSVReader::readCSV(fileName);
}
/**return vector of all the known products in the dataset*/
std::vector<std::string> OrderBook::getKnownProducts()
{
        std::vector<std::string> products;

        //it will map the string to bool and bool is basic data type
        std::map<std::string,bool> prodMap;

        for (OrderBookEntry& e : orders)
        {
            prodMap[e.product] = true;
        }

        //now flatten the map to a vector of strings
        //If bits of data not need to be changed than const is used.

        for (auto const& e: prodMap) 
        {
            //e.first will give the key and e.last will give the value
            products.push_back(e.first);
        }

        return products;

}

/**return vector of orders according to sent filters*/
std::vector<OrderBookEntry> OrderBook::getOrders (  OrderBookType type,
                                                    std::string product,
                                                    std::string timesstamp)
{
    std::vector<OrderBookEntry> orders_sub;

    for (OrderBookEntry& e : orders)
    {
        if( e.orderType == type &&
            e.product == product &&
            e.timestamp == timesstamp)
            {
                orders_sub.push_back(e);
            }
    }


    return orders_sub;
}

double OrderBook::getHighPrice(std::vector<OrderBookEntry>& orders)

{
    //Checking the first order price
    double max = orders[0].price;
    //If there is any thing higher than order give that value
    for (OrderBookEntry& e : orders)
    {
        if (e.price > max) max = e.price;
        
    }

    return max;

}

double OrderBook::getLowPrice(std::vector<OrderBookEntry>& orders)
{
    double min = orders[0].price;
    //If there is any thing higher than order give that value
    for (OrderBookEntry& e : orders)
    {
        if (e.price < min) min = e.price;
        
    }

    return min;
}


std::string OrderBook::getEarliestTime()

{
    //Return the ltest entry in the order book routed through Markel Main App.
    return orders[0].timestamp;

}

std::string OrderBook::getNextTime (std::string timestamp)

{
    std::string next_timestamp = "";
    for (OrderBookEntry& e : orders)
    {
        if (e.timestamp > timestamp)
        {
            next_timestamp = e.timestamp;
            break;
        }
    }

    if (next_timestamp == "")
    {
        next_timestamp = orders[0].timestamp;
    }

    return next_timestamp;
}

void OrderBook::insertOrder(OrderBookEntry& order)

{
    orders.push_back(order);

    //C++ has standard function for sort but need the comparing function
    //Since, we are comparing the orderbookentries so function will go to orderbookentries class. 
    //Parse in the name of the function nothing else.
    std::sort(orders.begin(), orders.end(), OrderBookEntry::compareByTimesstamp);
}