// specification file

#pragma once // if below class included once already, do not include again; otherwise class called every time 'include' written
#include <vector>
#include "orderBookEntry.h"
#include "OrderBook.h"
#include "Wallet.h"

class MerkelMain // class definition
{
public:
	MerkelMain(); // constructor

    /*** call this to start the simulation */
    void init(); // call this to start the simulation

private:
    //void loadOrderBook();
    void printMenu();
    void printCommandMenu();
    void printHelp(); // menu 1
    std::string userInput();

    std::vector<std::string> helpCommand;
    std::vector<std::string> helpInput;
    std::vector<double> weightings;

    void processUserInput(std::string userSelection);

    std::string currentTime;

    int exitSession();

    OrderBook orderBook{ "20200601.csv" };

    Wallet wallet;

};

