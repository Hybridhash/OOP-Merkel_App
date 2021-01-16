#include "CSVReader.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

CSVReader::CSVReader()
{

}

std::vector <OrderBookEntry> CSVReader::readCSV (std::string csvFileName)
{
    //Returns the vector of order book data entries
    std::vector<OrderBookEntry> entries;
    
    std::ifstream csvFile{csvFileName};
    std::string line;

    if (csvFile.is_open())
    {
        while(std::getline(csvFile,line))
        {
            try{
            OrderBookEntry obe = stringToOBE(tokenise(line, ','));
            entries.push_back(obe);
            }catch(const std::exception& e)
            {   
                //Try and catch will read the exceptions but continue to parse the data till end and give message
                std::cout << "CSVReader::readCSV read baddata" << std::endl;            
            }
        }// end of while Loop. If there are multiple while loop we should opt the function 

    }

    ///std::cout << "CSVReader::readCSV read :" << entries.size() << " entries" << std::endl;

    return entries;

}
std::vector<std::string> CSVReader::tokenise(std::string line, char separator)
{
    //Vector of strings
    std::vector<std::string> tokens;
    signed int start, end;
    std::string token;
    start = line.find_first_not_of(separator, 0);

    do {
    end = line.find_first_of(separator, start);

    if (start == line.length() || start == end) break;

    if (end >= 0)
    token = line.substr(start, end - start);
    else
    token = line.substr(start, line.length() - start);

    tokens.push_back(token);
    start = end + 1;
    } while(end > 0);

    return tokens;

}
OrderBookEntry CSVReader::stringToOBE(std::vector<std::string> tokens)
{
    //Returns single order book entry from the vector of strings

    double price, amount;

    if (tokens.size() != 5) 
    {
        std::cout << "Bad line" << std::endl;
        throw std::exception{};
    }

    //It will try the stod and catch the exception.
    try {
    amount = std::stod(tokens[4]);
    price = std::stod(tokens[3]);
    }catch(std::exception& e) {
    //std::cout << "CSVReader::stringToOBE Bad float!" << std::endl;
    throw; // throw the exception if it can't meet the criteria.
    }

    OrderBookEntry obe{ price,
                        amount,
                        tokens[0],
                        tokens[1],
                        OrderBookEntry::stringToOrderBookType(tokens[2])};

    return obe;
}

    OrderBookEntry CSVReader::stringToOBE(  std::string priceString,
                                            std::string amountString,
                                            std::string timestamp,
                                            std::string product,
                                            OrderBookType OrderType)

    {
        double price, amount;
        try {
            price = std::stod(priceString);
            amount = std::stod(amountString);
        }catch(const std::exception& e) {
            std::cout << "CSVReader::stringToOBE Bad float!" <<priceString<< std::endl;
            std::cout << "CSVReader::stringToOBE Bad float!" <<amountString<< std::endl;
            throw; // throw the exception if it can't meet the criteria.
        }

        OrderBookEntry obe{ price,
                        amount,
                        timestamp,
                        product,
                        OrderType};

        return obe;
    }