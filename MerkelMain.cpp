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
    // print help
    std::cout << "Help:" << std::endl;
    std::cout << "  Print all help commands: " << std::endl << std::endl;

    // print help cmd
    std::cout << "Help <cmd>:" << std::endl;
    std::cout << "  Print 'help <cmd> to get specific help for the command: " << std::endl << std::endl;

    // exit
    std::cout << "Exit:" << std::endl;
    std::cout << "  Exit the trading platform!" << std::endl << std::endl;

    std::cout << "=======================================" << std::endl << std::endl;

}

void MerkelMain::printHelp() // menu 1
{
    std::cout << "Advisorbot is a trading platform." << std::endl << std::endl;
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
    //try
    //{
    //    std::vector<std::string> helpCommand = CSVReader::tokenise(userInput, ' ');
    //}
    //catch (const std::exception& e)
    //{
    //    std::cout << "Please enter a valid number, not " << userInput << "!" << std::endl;
    //}

    for (std::string command : helpCommand)
        std::cout << "You entered: " << command << std::endl;

    if (userInput == "help")
    {
        std::cout << "You requested the 'Help' menu." << std::endl;
        MerkelMain::printHelp();
    }

    if (userInput == "help prod")
    {
        std::cout << "You requested help with the 'prod' command." << std::endl;
        std::cout << "The <prod> command lists all available products, and no additional arguements are neededhelp." << std::endl;
        std::cout << "For example, ETH/BTC, DOGE/BTC, etc." << std::endl;
    }

    if (userInput == "help min")
    {
        std::cout << "You requested help with the 'prod' command." << std::endl;
        std::cout << "The <prod> lists all available products, and no additional arguements are neededhelp." << std::endl;
        std::cout << "For example, ETH/BTC, DOGE/BTC, etc." << std::endl;
    }

    if (userInput == "help max")
    {
        std::cout << "You requested help with the 'prod' command." << std::endl;
        std::cout << "The <prod> lists all available products, and no additional arguements are neededhelp." << std::endl;
        std::cout << "For example, ETH/BTC, DOGE/BTC, etc." << std::endl;
    }

    if (userInput == "help avg")
    {
        std::cout << "You requested help with the 'prod' command." << std::endl;
        std::cout << "The <prod> lists all available products, and no additional arguements are neededhelp." << std::endl;
        std::cout << "For example, ETH/BTC, DOGE/BTC, etc." << std::endl;
    }

    if (userInput == "help predict")
    {
        std::cout << "You requested help with the 'prod' command." << std::endl;
        std::cout << "The <prod> lists all available products, and no additional arguements are neededhelp." << std::endl;
        std::cout << "For example, ETH/BTC, DOGE/BTC, etc." << std::endl;
    }

    if (userInput == "help time")
    {
        std::cout << "You requested help with the 'prod' command." << std::endl;
        std::cout << "The <prod> lists all available products, and no additional arguements are neededhelp." << std::endl;
        std::cout << "For example, ETH/BTC, DOGE/BTC, etc." << std::endl;
    }

    if (userInput == "help step")
    {
        std::cout << "You requested help with the 'prod' command." << std::endl;
        std::cout << "The <prod> lists all available products, and no additional arguements are neededhelp." << std::endl;
        std::cout << "For example, ETH/BTC, DOGE/BTC, etc." << std::endl;
    }

    if (userInput == "help my own")
    {
        std::cout << "You requested help with the 'prod' command." << std::endl;
        std::cout << "The <prod> lists all available products, and no additional arguements are neededhelp." << std::endl;
        std::cout << "For example, ETH/BTC, DOGE/BTC, etc." << std::endl;
    }

    if (userInput == "prod")
    {
        std::cout << "You requested help with the 'prod' command." << std::endl;
        std::cout << "The <prod> command lists all available products, and no additional arguements are neededhelp." << std::endl;
        std::cout << "For example, ETH/BTC, DOGE/BTC, etc." << std::endl;
    }

    if (userInput == "min")
    {
        std::cout << "You requested help with the 'min' command." << std::endl;
        std::cout << "The <min> command finds the minimum bid or ask for a specified product in the current time period." << std::endl;
        std::cout << "Additional arguments required are <bid> or <ask> and the product, such as ETH/BTC." << std::endl;
        std::cout << "For example, 'The min ask for ETH/BTC is 1.0.'" << std::endl;
    }

    if (userInput == "max")
    {
        std::cout << "You requested help with the 'max' command." << std::endl;
        std::cout << "The <max> command finds the maximum bid or ask for a specified product in the current time period." << std::endl;
        std::cout << "Additional arguments required are <bid> or <ask> and the product, such as ETH/BTC." << std::endl;
        std::cout << "For example, 'The max ask for ETH/BTC is 1.0.'" << std::endl;
    }

    if (userInput == "avg")
    {
        std::cout << "You requested help with the 'avg' command." << std::endl;
        std::cout << "The <avg> command computes the average bid or ask for the specified product over the specified number of time periods." << std::endl;
        std::cout << "Additional arguments required are <int> of time periods, <bid> or <ask> and the product, such as ETH/BTC." << std::endl;
        std::cout << "For example, 'The average ETH/BTC ask price over the last 10 timesteps was 1.0.'" << std::endl;
    }

    if (userInput == "predict")
    {
        std::cout << "You requested help with the 'predict' command." << std::endl;
        std::cout << "The <predict> command will predict the maximum or minimum bid or ask for the specific product specified in the next time period." << std::endl;
        std::cout << "Additional arguments required are <min> or <max>, <bid> or <ask> and the product, such as ETH/BTC." << std::endl;
        std::cout << "For example, 'The average ETH/BTC ask price over the last 10 timesteps was 1.0.'" << std::endl;
    }

    if (userInput == "time")
    {
        std::cout << "You requested help with the 'time' command." << std::endl;
        std::cout << "The <time> command lists the current time period in the dataset." << std::endl;
        std::cout << "For example, 2020/03/17 17:01:24." << std::endl;
    }

    if (userInput == "step")
    {
        std::cout << "You requested help with the 'step' command." << std::endl;
        std::cout << "The <step> command moves trading to the next time period." << std::endl;
        std::cout << "For example, ." << std::endl;
    }

    if (userInput == "my own")
    {
        std::cout << "You requested help with the 'my own' command." << std::endl;
        std::cout << "The <my own> ." << std::endl;
        std::cout << "For example, " << std::endl;
    }

    if (userInput == "exit")
    {
        std::cout << "Exiting the program!" << std::endl << std::endl;
        exitSession();
    }

    else
    {
    std::cout << "Your input did not identify a menu or help option." << std::endl;
    std::cout << "Please re-enter a selection." << std::endl;
    }
}

int MerkelMain::exitSession()
{
    exit(0);
}