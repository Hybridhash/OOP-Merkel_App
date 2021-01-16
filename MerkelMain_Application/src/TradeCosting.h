#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <map>


class tradeCosting
{
    public:

    /**Constructor*/
    tradeCosting();

    /**To calculate the simulation cost*/
    void tradeCalculator(double quantity);

    /**To display the charges at any given time*/
    std::string todisplayCharges();

    private:

    /**to add the charges to the map*/
    void addCharges(const std::string& first,double second)
        {
            charges[first] += second;
        }  


    //Mapping the  sale quanity and prices charged.
    std::map<std::string, double> charges;

    
};

