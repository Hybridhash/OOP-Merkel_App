#pragma once
#include <fstream>
#include <string>
#include <iostream>

class MerkelLog

{
    public:
        /**Constructor for MerkelLog class*/
        MerkelLog();

        //**Creating a CSV of log with the input argument of name, log level and log input*/
        void createCSV(int level, int name, std::string input);

        /**public variable for the log level type*/
        const int logLevelinfo = 1;
        const int LogLevelWarning = 0;

        /**public variable for file name/tupe*/
        const int SaleLog = 0;
        const int WalletLog = 1;
        const int OrderLog = 2;
        

    private:
         /**Private Class member for selection of file name*/
        std::string fileName(int t);
         /**Private Class member for defining the log level*/
        std::string logType(int t);
    
};