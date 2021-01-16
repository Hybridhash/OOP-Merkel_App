#include "MerkelLog.h"
#include <fstream>
#include <string>
#include <iostream>

//Constructor initialized as prt of the MerkelLog.cpp file.
MerkelLog::MerkelLog()
{

}

//Creating the a new CSV file for the log
void MerkelLog::createCSV(int level , int name, std::string input)

{     
   
    //Pointer to the file
    std::fstream fileOut;
    //Creating a file with the input name given as an argument to the function
    fileOut.open(fileName(name), std::ios::out | std::ios::app);
    //Creating a new file or inserting in the existing file. 
    //Log type is return the nature of log i.e. Warning or Info.
    fileOut <<logType(level) <<input << "\n";
    
}


std::string MerkelLog::logType(int t)
{   
    
    //Checking the input integer against the predefined public integers for file name
     std::string m;
     if (t == LogLevelWarning)
        {
            m += "[Warning]: ";
        }
    if (t == logLevelinfo)
        {
            m += "[Info]: ";
        }
        
    return m;
}


std::string MerkelLog::fileName(int t)
{   
     std::string f;
    //Checking the input integer against the predefined public integers for file name
     if (t == SaleLog)
        {
            f += "SaleLog.csv";
        }
    if (t == WalletLog)
        {
            f += "WalletLog.csv";
        }
    if (t == OrderLog)
        {
            f += "OrderLog.csv";
        }
    //Returning the name of CSV file    
    return f;
}