#include "OrderBook.h"
#include "CSVReader.h"
#include "map"
#include <algorithm>
#include <iostream>


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


std::vector<OrderBookEntry> OrderBook::matchAsksToBids(std::string product, std::string timesstamp)
{
    //     asks ← orderBook.asks
           std::vector <OrderBookEntry> asks  = getOrders(  OrderBookType::ask,
                                                            product,
                                                            timesstamp);

    //     bids ← orderBook.bids

            std::vector <OrderBookEntry> bids  = getOrders( OrderBookType::bid,
                                                            product,
                                                            timesstamp);

    // sales ← newVector

            std::vector<OrderBookEntry> sales;

    // SortAscending(asks)
            std::sort(asks.begin(), asks.end(), OrderBookEntry::compareByPriceAsc);

    // SortDescending(bids)
            std::sort(bids.begin(), bids.end(), OrderBookEntry::compareByPriceDesc);

    // Since the order are sorted, therefore, we can get the max and min value.
            std::cout << "max ask " << asks[asks.size()-1].price << std::endl;
            std::cout << "min ask " << asks[0].price << std::endl;
            std::cout << "max bid " << bids[0].price << std::endl;
            std::cout << "min bid " << bids[bids.size()-1].price << std::endl;

    // for all ask ∈ asks do
            for(OrderBookEntry& ask : asks)
            {

    // for every ask for iterate ove  all bid ∈ bids do
                for (OrderBookEntry& bid : bids)
                {
    //     if bid.price ≥ ask.price then
                    if (bid.price >= ask.price)
                    {
    //          sale ← newOrder
    //          sale.price ← ask.price

                        OrderBookEntry sale{ask.price,0,timesstamp,product,
                                            OrderBookType::asksale};

                        //Temporary type is defined as asksale and changed based on if conditions
    
                        if (bid.username == "simuser")
                        {
                            sale.username = "simuser";
                            sale.orderType = OrderBookType::bidsale;
                        }
                        if (ask.username == "simuser")
                        {
                            sale.username = "simuser";
                            sale.orderType = OrderBookType::asksale;
                        }


    //         if bid.amount = ask.amount then
                       if (bid.amount == ask.amount)
                        { 
    //         sale.amount ← ask.amount
                            sale.amount = ask.amount;
    //         Append(sales,sale)
                            sales.push_back(sale);
    //         bid.amount ← 0
                            bid.amount = 0;
    //         break
                            break;
    //         end if
                        }

    //         if bid.amount > ask.amount then
                        if (bid.amount > ask.amount)
                        {
    //         sale.amount ← ask.amount
                            sale.amount = ask.amount;
    //         Append(sales,sale)
                            sales.push_back(sale);
    //         bid.amount ← bid.amount − ask.amount
                            bid.amount = bid.amount - ask.amount;
    //         break(ask is completley fullfilled)
                            break;
    //         end if
                        }
    //         if bid.amount < ask.amount then
                        if (bid.amount < ask.amount && 
                            bid.amount > 0)
                        {
    //         sale.amount ← bid.amount
                            sale.amount = bid.amount;
    //         Append(sales,sale)
                            sales.push_back(sale);
    //         ask.amount ← ask.amount − bid.amount
                            ask.amount = ask.amount - bid.amount;
    //         bid.amount ← 0
                            bid.amount = 0;
    //         continue (Ask is not completley fullfilled, go for next bid in for loop)
                            continue;
    //         end if
                        }
    //     end if
                    }
    // end for
                }
            }

            return sales;
}

void OrderBook::timeStamps()
{
    std::set<std::string> time;

    char userOption = 'Y';
    

    for (OrderBookEntry& e : orders)
        {
            time.insert(e.timestamp);
        }

//    for (const auto& t : time)
//    {
       
//        std::cout << t << std::endl;
//        std::cout << "Enter 'Y' to next timestamp: " << std::endl;
//        std::cin >> userOption;
//        if (userOption == 'Y')
//        continue;
//    }

}