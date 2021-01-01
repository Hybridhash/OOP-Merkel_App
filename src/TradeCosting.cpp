#include <iostream>
#include "TradeCosting.h"
#include <string>
#include <map> 
#include <iterator>
#include <algorithm>

tradeCosting::tradeCosting()
{
   

}

std::string tradeCosting::todisplayCharges()
{
    //Local variable to store the message as we build.
    std::string s;

    std::map<std::string, double>::iterator it = charges.begin();
    
    for (std::pair<std::string, double> pair : charges)
    {
        //to pull the first items from the pair(Local string).
        std::string currency = pair.first;
        //to pull the second ites from the pair.
        double amount = pair.second;
        s += currency + " : " + std::to_string(amount) /** Convert double to string*/ + "\n"; 
    }   

    /**std::for_each(charges.begin(), charges.end(),
        [](std::pair<std::string, double> element){
                    // Accessing KEY from element
                    std::string quantity = element.first;
                    // Accessing VALUE from element.
                    double value = element.second;

                    s += quantity + " : " value;
                    //std::cout<<"Sale Quantity: "<<quantity<<" :: " <<"Charges "<<value<< " USD" <<std::endl;
        }); */

    return s;
}


void tradeCosting::tradeCalculator(double quanity)
{
    double totalCharges;
    
    //Charges are reducing based on the quantity of sales transaction placed by trading bot
    if(quanity <= 10)
        totalCharges = (quanity * 0.10);
    else if (quanity <= 20)
        totalCharges = (10 * 0.10) + ((quanity - 10) * 0.50);
    else
        totalCharges = (10 * 0.10) + (10 * 0.50) + ((quanity - 20) * 0.25);

    charges.insert({std::to_string(quanity),totalCharges});
}