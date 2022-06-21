// cryptoTrading.cpp : This file contains the 'main' function. Program execution begins and ends there.
// all other functions specified and implemented in the MerkelMain files (.h and .cpp)


#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

#include "orderBookEntry.h"
#include "MerkelMain.h"
#include "csvReader.h"


int main()
{
    // public functions
    MerkelMain app{}; // call the constructor function, .h file
    app.init(); // call the init function; with comment from .h file

    //Wallet wallet;
    //wallet.insertCurrency("BTC", 10);
    //wallet.insertCurrency("USDT", 500);
    //std::cout << wallet.toString() << std::endl;
    //wallet.removeCurrency("USDT", 32);
    //std::cout << wallet.toString() << std::endl;
    //std::cout << "Does the wallet contain BTC: " << wallet.containsCurrency("BTC", 10) << std::endl;
    //std::cout << wallet.toString() << std::endl;
   

    CSVReader reader;

    // CSVReader::readCSV("20200317.csv");

    return 0;
}

//    while (true) {

//        printMenu();

//        int userSelection = userInput();

//        processUserInput(userSelection);

//    };



