#pragma once

#include <string>

//Class implementation and specification into header file

enum class OrderBookType {bid, ask, unknown};

    class OrderBookEntry
    {
    public:

     OrderBookEntry(double _price,
                    double _amount,
                    std::string _timestamp,
                    std::string _product,
                    OrderBookType _orderType);
    
        //Function to convert the string to order book type. More practically to do here as statis (don't depend any of the data below)
        
        static OrderBookType stringToOrderBookType (std::string s);

        //Function to compare entires and return boolean.
        static bool compareByTimesstamp(OrderBookEntry& e1, OrderBookEntry& e2 )
        {
            return e1.timestamp < e2.timestamp;
        }

    //It is mendatory to declare the same variables in class which are declared as parameters in constructpr function
    double price; 
    double amount;
    std::string timestamp;
    std::string product;
    OrderBookType orderType;
};