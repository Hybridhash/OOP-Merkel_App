 
#include "OrderBookEntry.h"

//Implementation
//Since we are not in the class, Therefore, order book entry classed is called along with constructor function

OrderBookEntry::OrderBookEntry(double _price,
                    double _amount,
                    std::string _timestamp,
                    std::string _product,
                    OrderBookType _orderType)
    //Initilization
    :   price(_price), 
        amount(_amount),
        timestamp(_timestamp),
        product(_product),
        orderType(_orderType)

{

}    