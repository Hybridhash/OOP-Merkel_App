#pragma once

#include "OrderBookEntry.h"
#include "CSVReader.h"
#include <string>
#include <vector>

class OrderBook
{

    public:
    /**Construct, reading a csv data file*/
        OrderBook(std::string fileName);
    /**return vector of all the known products in the dataset*/
        std::vector<std::string> getKnownProducts();
    /**return vector of orders according to sent filters*/
        std::vector<OrderBookEntry> getOrders (OrderBookType type,
                                               std::string product,
                                               std::string timesstamp);
    
        /**Returns earliest time in order book*/   
        std::string getEarliestTime();

        /**Returns the next time after the 
         * sent time in the orderbookt
         * if there is no nect timestamp, wraps around to the start*/
        std::string getNextTime (std::string timestamp);

        /**It is kept here because mostly orders are taking place at this place
         * We will pass in the product type and timestamp as match criteria
        */
        std::vector<OrderBookEntry> matchAsksToBids(std::string product, std::string timestamp);
    
        /**Function to add the entry in the orderbook by generating the object and parse*/
        void insertOrder(OrderBookEntry& order);

    /**It will not look at the orders completely but only to those which are parsed unlink other function defined above*/
        static double getHighPrice(std::vector<OrderBookEntry>& orders);
        static double getLowPrice(std::vector<OrderBookEntry>& orders);
    private:
        std::vector<OrderBookEntry> orders;

};