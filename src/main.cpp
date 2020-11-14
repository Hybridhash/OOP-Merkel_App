#include <iostream>
#include <string>
#include <vector>
#include "OrderBookEntry.h"
#include "MerkelMain.h"

int main()
{   
    MerkelMain app{};

    app.init();    
   
}


//Double is used as it is financial data and it might reduce quality over time like picture
    //double price = 5405.41766912;
    //double amount = 0.69895055;
    
    //String is class called in the CPP and it's kind of constructor function. = sign can also be used to declare variable
    
    /*std::string timestamp {"2020/03/17 17:01:24.884492"};
    std::string produt {"btc/usdt"};
    std::string ordertype{ "ask" };*/

   /* std::vector<double> prices;
    std::vector<double> amounts;
    std::vector<std::string> timestamps;
    std::vector<std::string> products;
    std::vector<orderbooktype> ordertype;

    prices.push_back(5000.01);
    amounts.push_back(0.001);
    timestamps.push_back("2020/03/17 17:01:24.884492");
    products.push_back("btc/usdt");
    ordertype.push_back(orderbooktype::bid);

    std::cout << "prices " << prices[0] << std::endl;*/

    /*while (true)
    {
        printMenu();
        int userOption = getUserOption();
        processUserOption(userOption);
    }*/

// std::vector<OrderBookEntry> orders;
   // orders.push_back(OrderBookEntry {10000,
   //                                  0.002,
   //                                  "2020/03/17 17:01:24.884492",
   //                                  "btc/usdt",
   //                                  OrderBookType::bid});


    //orders.push_back(OrderBookEntry {2000,
   //                                  0.005,
   //                                  "2020/03/17 17:01:24.884492",
   //                                  "btc/usdt",
   //                                  OrderBookType::bid});
    //Instead of declaring the variable we can call the construction within push back


    // OrderBookEntry order1{10000,
    //                       0.002,
    //                       "2020/03/17 17:01:24.884492",
    //                       "btc/usdt",
    //                        OrderBookType::bid};

    
    
    //{} brackets are explicit to call the constructor
    
    //Below Code is before declaring the construction function in Class 

    /*OrderBookEntry order1;
    order1.price = 10000;
    order1.amount = 10.002;
    order1.timestamp = "2020/03/17 17:01:24.884492";
    order1.product = "btc/usdt";
    order1.orderType = OrderBookType::bid;*/

    //std::cout << "The price is " << orders[1].price << std::endl;

    //****Iterative Style of printing *****

    //Method 1 :It is making the copy thing to order but adding & will make it more efficient
   
    // for (OrderBookEntry& order : orders)
   // {
   //     std::cout << "The price is " << order.price << std::endl; 
   // }    

    //Method 2 - ++i is more efficient it copy and increment at same time.
   // for (unsigned int i =0; i < orders.size(); ++i)
   // {
   //     std::cout << "The price is " << orders[i].price << std::endl;
   // }
    
    //Method 3 - orders.at(i) object style syntax
    // for (unsigned int i =0; i < orders.size(); ++i)
    //{
    //    std::cout << "The price is " << orders.at(i).price << std::endl;
    //}
    //return 0;