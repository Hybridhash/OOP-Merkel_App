#include "Wallet.h"
#include <iostream>
#include "CSVReader.h"



 Wallet::Wallet()
 {

 }
     
void Wallet::insertCurrency(std::string type, double amount)
{
    //First we have to check that is there any currency in the wallet for particular type.

    double balance;   

    if (amount <0)
    {
        throw std::exception{};
    }

    //we check the count of currency not value
    if (currencies.count(type) == 0) //Not yet there 
        {
            balance = 0;
        }
    else
        {   //is there
            //Square brackets are used to push the type
            balance = currencies[type];
        }

    balance += amount;
    //Map function in header file will make the currency type as unique value and balance as a double value 
    currencies[type] = balance;
}

bool Wallet::removeCurrency(std::string type, double amount)
{
    double balance;   

    if (amount <0)
    {
        return false;
    }

    //we check the count of currency not value
    if (currencies.count(type) == 0) //Not yet there 
        {
            //No currency in wallet return false
            return false;
        }
    else
        {   //is there - do we have enough
            //Square brackets are used to push the type
            if (containsCurrency(type, amount)) // we have enough
            {
                std::cout << "Removing " << type << " : " << amount << std::endl;
                currencies[type] -=amount;
                return true;
            }
            else // they have it but not enough
                return false;
        }
}

bool Wallet::containsCurrency(std::string type, double amount)
{
  if (currencies.count(type) == 0)
            return false;
    else
        return currencies[type] >= amount;
        
}

std::string Wallet::toString()
{
    /**This function was not called intially so that's why no linker error
     * Now we will iterate over the map items using the pair to represent the one of the item in map 
    */

    //Local variable to store the message as we build.
    std::string s;
    for (std::pair<std::string, double> pair : currencies)
    {
        //to pull the first items from the pair(Local string).
        std::string currency = pair.first;
        //to pull the second ites from the pair.
        double amount = pair.second;
        s += currency + " : " + std::to_string(amount) /** Convert double to string*/ + "\n"; 
    }    
    return s;
}


bool Wallet::canFulfillOrder(OrderBookEntry order)
{
    //CSVReader::Tokenise is used not CSVReader.tokenise because it is static function
    std::vector<std::string> currs = CSVReader::tokenise(order.product, '/');
    //ask
    if (order.orderType == OrderBookType::ask)
    {
         double amount = order.amount;   
         std::string currency =  currs[0];

         std::cout << "Wallet::canFulfillOrder || ASK " << currency << " : " << amount << std::endl; 

         return containsCurrency (currency, amount);
    }
    //bid
    if (order.orderType == OrderBookType::bid)
    {
        double amount = order.amount*order.price;   
        std::string currency =  currs[1];

        std::cout << "Wallet::canFulfillOrder || BID " << currency << " : " << amount << std::endl; 

        return containsCurrency (currency, amount);
    }

    return false;
}

void Wallet::processSale(OrderBookEntry& sale)
{
    
    std::vector<std::string> currs = CSVReader::tokenise(sale.product, '/');
    //ask
    if (sale.orderType == OrderBookType::asksale)
    {
         double outgoingAmount = sale.amount;   
         std::string outgoingCurrency =  currs[0];
         //Amount tells how many unit we have bought or sold because it could 0.1
         double incomingAmount = sale.amount*sale.price;
         std::string incomingCurrency =  currs[1];

         currencies[incomingCurrency] += incomingAmount;
         currencies[outgoingCurrency] -= outgoingAmount;

    }
    //bid
    if (sale.orderType == OrderBookType::bidsale)
    {
         double incomingAmount = sale.amount;   
         std::string incomingCurrency =  currs[0];
         //Amount tells how many unit we have bought or sold because it could 0.1
         double outgoingAmount = sale.amount*sale.price;
         std::string outgoingCurrency =  currs[1];

         currencies[incomingCurrency] += incomingAmount;
         currencies[outgoingCurrency] -= outgoingAmount;
    }

}

double Wallet::checkWallet(std::string product)
{

    for (std::pair<std::string, double> pair : currencies)
    {
        std::vector<std::string> currs = CSVReader::tokenise(product, '/');
        //to pull the first items from the pair(Local string).
        std::string currency = pair.first;
        //to pull the second ites from the pair.
        double amount = pair.second;

        if (currs[0] == currency)
        {
            return amount;
        }
    }
    
    return 0;
}