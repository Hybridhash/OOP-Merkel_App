 
#include "OrderBookEntry.h"

//Implementation
//Since we are not in the class, Therefore, order book entry classed is called along with constructor function

OrderBookEntry::OrderBookEntry(double _price,
                    double _amount,
                    std::string _timestamp,
                    std::string _product,
                    OrderBookType _orderType,
                    std::string _username)
    //Initilization
    :   price(_price), 
        amount(_amount),
        timestamp(_timestamp),
        product(_product),
        orderType(_orderType),
        username(_username)

{

}
//Name spacing with come before the function and OrderBookType mentioned in the begining is to get the type based on enum class
OrderBookType OrderBookEntry::stringToOrderBookType (std::string s)

{
    if (s == "ask")
    {
        return OrderBookType::ask;
    }
    if (s == "bid")

    {
        return OrderBookType::bid;
    }

    //There is no if provided as it gives some warning of reaaching end of class
    return OrderBookType::unknown;
    
}