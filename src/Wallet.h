#pragma once
#include "OrderBookEntry.h"
#include <string>
#include <map>
#include <iostream>
#include "OrderBook.h"

class Wallet

{
    public:
        Wallet();
        /**Insert Currency to the Wallet*/
        void insertCurrency(std::string type, double amount);

        /**Remove Currency to the Wallet*/
        bool removeCurrency(std::string type, double amount);

        /**Check if the wallet has some currency or not*/
        bool containsCurrency(std::string type, double amount);
        
        /**Check that the wallet can cope with the ask and bid*/
        bool canFulfillOrder(OrderBookEntry order);
        
        /**Update the contents of the wallet
         * assumes the order was made by the owner of wallet
        */
        void processSale(OrderBookEntry& sale);

        /**String representation of the currency Wallet is having*/
        std::string toString();

        /**Processing the sales, updating wallet and shifting to next time frame*/
        void appRefresh();

    private:

        std::string currentTime;

        OrderBook OrderBook{"20200317.csv"};
        /**Mapping the strings to double i.e. Currency Name and Amounts*/
        std::map<std::string, double> currencies;    

};