#include <iostream>
#include "TradeCosting.h"
#include <string>
#include <map> 
//#include <iterator>
//#include <algorithm>
#include <cstring>

tradeCosting::tradeCosting()
{
   

}


void tradeCosting::tradeCalculator(double quanity)
{
    //double to calculated the total charges on trade
    double totalCharges;
    
    //Charges are reducing based on the quantity of sales transaction placed by trading bot
    if(quanity <= 10)
        totalCharges = (quanity * 0.10);
    else if (quanity <= 20)
        totalCharges = (10 * 0.10) + ((quanity - 10) * 0.50);
    else
        totalCharges = (10 * 0.10) + (10 * 0.50) + ((quanity - 20) * 0.25);

    //Calling add charges method to map the charges and quantities ordered.
    addCharges(std::to_string(quanity),totalCharges);
}

std::string tradeCosting::todisplayCharges()
{
    //Local variable to store the message as we build.
    std::string s;
    double total = 0;

    //std::map<std::string, double>::iterator it = charges.begin();
    
    for (const auto& pair : charges)
    {
        //to pull the quantities executed from the pair(Local string).
        std::string qty = pair.first;
        //to pull the amount ties with the quantities.
        double amount = pair.second;
        //to get the total of charges
        total = pair.second + total;
        s += "Sale Batch Size: " + qty + " :: " + std::to_string(amount) + " USD "  + "\n";

        
    }   
        if (s.empty())//Checking for the  value in the string
        {
            return "---- [Info] No Trade Executed ----";
        }

        // Returning the total charges for all batches
        return s + "Total Charges: " + std::to_string(total) + " USD ";
    
}
