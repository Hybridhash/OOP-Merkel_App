#pragma once
#include "OrderBookEntry.h"
#include <vector>
#include <string>

class CSVReader

{
    public:
        CSVReader();

        //This will be stateless function, otherwise we have to create the instances
        //the static function does not depend up the class data members.
        static std::vector <OrderBookEntry> readCSV (std::string csvFile);

    private:
        static std::vector<std::string> tokenise(std::string line, char separator);
        static OrderBookEntry stringToOBE(std::vector<std::string> strings);
};
   