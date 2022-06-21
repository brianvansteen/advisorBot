// implementation file

#include "MerkelMain.h"
#include <iostream>
#include <vector>
#include "orderBookEntry.h"
#include "csvReader.h"

MerkelMain::MerkelMain() // constructor is for creating instance of object and ensure it is ready to be used
{

}

void MerkelMain::init() // start the object running
{
    // loadOrderBook(); // call function
    std::string input;
    currentTime = orderBook.getEarliestTime();

    wallet.insertCurrency("BTC", 10);

    while (true)
    {
        printMenu();
        input = userInput();
        processUserInput(input);
    }
}


/* print the user menu */
void MerkelMain::printMenu()
{
    // 1 print help
    std::cout << "Help:" << std::endl;
    std::cout << "  Print help commands: " << std::endl << std::endl;

    // 7 exit
    std::cout << "Exit:" << std::endl;
    std::cout << "  Exit the trading platform!" << std::endl << std::endl;

    std::cout << "=======================================" << std::endl << std::endl;

}

void MerkelMain::printHelp() // menu 1
{
    std::cout << "Advisorbot are a trading platform." << std::endl << std::endl;
    std::cout << "The help commands are as follows below." << std::endl<<std::endl;
    std::cout << "If you want help for a specific command, enter as follow:" << std::endl;
    std::cout << "  help <cmd>" << std::endl <<std::endl;
    std::cout << "- prod:" << std::endl;
    std::cout <<"   print a list of currency trading products." << std::endl<<std::endl;
    std::cout << "- min:"<<std::endl;
    std::cout << "  find the minimum bid or minimum ask, for a specific product in the current time period." << std::endl << std::endl;
    std::cout << "- max:" << std::endl;
    std::cout << "  find the minimum bid or minimum ask, for a specific product in the current time period." << std::endl << std::endl;
    std::cout << "- avg:" << std::endl;
    std::cout << "  compute the average bid or ask, for a specific product, for a specific number of time periods." << std::endl << std::endl;
    std::cout << "- predict:" << std::endl;
    std::cout << "  predict the maximum or minimum bid or ask, for a specific product, in the next time period." << std::endl << std::endl;
    std::cout << "- my own:" << std::endl;
    std::cout << "  cccccc....... " <<std::endl <<std::endl;
    std::cout << "- time:" << std::endl;
    std::cout << "  print the current time period." << std::endl <<std::endl;
    std::cout << "- step:" << std::endl;
    std::cout << "  complete the current time period, and move to the next time period." << std::endl<<std::endl;
    std::cout << "When implementing a help command, please make sure to enter all required parameters!" << std::endl << std::endl;
}


std::string MerkelMain::userInput()
{
    std::string userSelection = " ";
    std::cout << "Make a selection from the options:" << std::endl;
    std::getline(std::cin, userSelection);
    std::cout << "You selected: " << userSelection << std::endl <<std::endl;
    return userSelection;
}


void MerkelMain::processUserInput(std::string userInput)
{
    try
    {
        std::vector<std::string> helpCommand = CSVReader::tokenise(userInput, ' ');
    }
    catch (const std::exception& e)
    {
        std::cout << "Please enter a valid number, not " << userInput << "!" << std::endl;
    }

    for (std::string command : helpCommand)
        std::cout << "You entered: " << command << std::endl;

    if (userInput == "help") // not valid selection
    {
        std::cout << "You requested the 'Help' menu." << std::endl;
        MerkelMain::printHelp();
    }

    else if (userInput == "exit")
    {
        std::cout << "Exiting the program!" << std::endl << std::endl;
        exitSession();
    }
}

int MerkelMain::exitSession()
{
    exit(0);
}