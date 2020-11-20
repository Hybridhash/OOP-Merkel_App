#include "CSVReader.h"
#include <iostream>
#include <vector>
#include <string>

CSVReader::CSVReader()
{

}

std::vector <OrderBookEntry> CSVReader::readCSV (std::string csvFile)
{
    //Returns the vector of order book data entries
    std::vector<OrderBookEntry> entries;
    return entries;

}
std::vector<std::string> CSVReader::tokenise(std::string line, char separator)
{
    //Vector of strings
    std::vector<std::string> tokens;
    return tokens;

}
OrderBookEntry CSVReader::stringToOBE(std::vector<std::string> strings)
{
    //Returns single order book entry 
    OrderBookEntry obe{ 1,
                        1,
                        "",
                        "",
                        OrderBookType::bid};

    return obe;
}
