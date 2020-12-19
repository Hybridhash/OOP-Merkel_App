#pragma once

#include <string>

//Class implementation and specification into header file

enum class OrderBookType {bid, ask, unknown, asksale, bidsale, botask, botbid};

    class OrderBookEntry
    {
    public:

     OrderBookEntry(double _price,
                    double _amount,
                    std::string _timestamp,
                    std::string _product,
                    OrderBookType _orderType,
                    //Default user name is defined as dataset
                    std::string username = "dataset");
    
        //Function to convert the string to order book type. More practically to do here as statis (don't depend any of the data below)
        
        static OrderBookType stringToOrderBookType (std::string s);

        //Function to compare entires and return boolean.
        static bool compareByTimesstamp(OrderBookEntry& e1, OrderBookEntry& e2 )
        {
            return e1.timestamp < e2.timestamp;
        }

        //Function to compare the price of orderbook entries in ascending order (Prices lwo to high).
        static bool compareByPriceAsc(OrderBookEntry& e1, OrderBookEntry& e2 )
        {
            return e1.price < e2.price;
        }

        
        //Function to compare the price of orderbook entries in decending (Prices High to low).
        static bool compareByPriceDesc(OrderBookEntry& e1, OrderBookEntry& e2 )
        {
            return e1.price > e2.price;
        }

    //It is mendatory to declare the same variables in class which are declared as parameters in constructpr function
    double price; 
    double amount;
    std::string timestamp;
    std::string product;
    OrderBookType orderType;
    std::string username;
};