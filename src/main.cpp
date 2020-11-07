#include <iostream>
#include <string>
#include <vector>

enum class OrderBookType { bid, ask };

class OrderBookEntry
{
    public:

     OrderBookEntry(double _price,
                    double _amount,
                    std::string _timestamp,
                    std::string _product,
                    OrderBookType _orderType)
    {
        //All the data coming from the constructor parameters are passed to the variables within function.
        price = _price;
        amount = _amount;
        timestamp = _timestamp;
        product = _product;
        orderType = _orderType;
    
    }

    //It is mendatory to declare the same variables in class which are declared as parameters in constructpr function
    double price; 
    double amount;
    std::string timestamp;
    std::string product;
    OrderBookType orderType;

};
void printMenu()
{
    // 1 print help
    std::cout << "1: Print help " << std::endl;
    // 2 print exchange stats
    std::cout << "2: Print exchange stats" << std::endl;
    // 3 make an offer
    std::cout << "3: Make an offer " << std::endl;
    // 4 make a bid 
    std::cout << "4: Make a bid " << std::endl;
    // 5 print wallet
    std::cout << "5: Print wallet " << std::endl;
    // 6 continue   
    std::cout << "6: Continue " << std::endl;

    std::cout << "============== " << std::endl;
}

void printHelp()
{
    std::cout << "Help - your aim is to make money. Analyse the market and make bids and offers. " << std::endl;
}

void  printMarketStats()
{
    std::cout << "Market looks good. " << std::endl;
}

void enterOffer()
{
    std::cout << "Mark and offer - enter the amount " << std::endl;
}

void enterBid()
{
    std::cout << "Make a bid - enter the amount" << std::endl;
}

void printWallet()
{
    std::cout << "Your wallet is empty. " << std::endl;
}
        
void gotoNextTimeframe()
{
    std::cout << "Going to next time frame. " << std::endl;
}
 
int getUserOption()
{
    int userOption;

    std::cout << "Type in 1-6" << std::endl;
    std::cin >> userOption;
    std::cout << "You chose: " << userOption << std::endl;
    return userOption;
}

void processUserOption(int userOption)
{
    if (userOption == 0) // bad input
    {
        std::cout << "Invalid choice. Choose 1-6" << std::endl;
    }
    if (userOption == 1) // bad input
    {
        printHelp();
    }
    if (userOption == 2) // bad input
    {
        printMarketStats();
    }
    if (userOption == 3) // bad input
    {
        enterOffer();
    }
    if (userOption == 4) // bad input
    {
        enterBid();
    }
    if (userOption == 5) // bad input
    {
        printWallet();
    }
    if (userOption == 6) // bad input
    {
        gotoNextTimeframe();
    }       
}

int main()
{   
    
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


    OrderBookEntry order1{10000,
                          0.002,
                          "2020/03/17 17:01:24.884492",
                          "btc/usdt",
                           OrderBookType::bid};

    //{} brackets are explicit to call the constructor
    
    //Below Code is before declaring the construction function in Class 

    /*OrderBookEntry order1;
    order1.price = 10000;
    order1.amount = 10.002;
    order1.timestamp = "2020/03/17 17:01:24.884492";
    order1.product = "btc/usdt";
    order1.orderType = OrderBookType::bid;*/

    std::cout << "The price is " << order1.amount << std::endl;

    //return 0;
}

