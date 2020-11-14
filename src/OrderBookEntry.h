#pragma once

#include <string>

//Class implementation and specification into header file

enum class OrderBookType { bid, ask };

class OrderBookEntry
{
    public:

     OrderBookEntry(double _price,
                    double _amount,
                    std::string _timestamp,
                    std::string _product,
                    OrderBookType _orderType);
    //It is mendatory to declare the same variables in class which are declared as parameters in constructpr function
    double price; 
    double amount;
    std::string timestamp;
    std::string product;
    OrderBookType orderType;
};