#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <map>


class tradeCosting
{
    public:

    tradeCosting();

    /**To calculate the simulation cost*/
    void tradeCalculator(double quantity);

    std::string todisplayCharges();

    private:



    /**String representation of the charges in vector for Merkel Main*/
    //std::string todisplayCharges();

    //Vector of sale quanity and prices charged.
    std::map<std::string, double> charges;

    
};

