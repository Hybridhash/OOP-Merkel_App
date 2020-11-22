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

        //Moved to public for purpose of using in ask bid to tokenize the inut
        static std::vector<std::string> tokenise(std::string line, char separator);
        //OrderBookEntry object is created with explicit items. We can keep same function twice if variables are different.
        static OrderBookEntry stringToOBE(  std::string price,
                                            std::string amount,
                                            std::string timestamp,
                                            std::string product,
                                            OrderBookType OrderType);

    private:
        static OrderBookEntry stringToOBE(std::vector<std::string> strings);
};
   