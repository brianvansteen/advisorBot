// implementation file

#include "MerkelMain.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <cctype>
#include "orderBookEntry.h"
#include "csvReader.h"
#include "advisorBot.h"

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
    std::cout << "=======================================" << std::endl << std::endl;

    std::cout << "**** MAIN MENU ****"<<std::endl << std::endl;
    
    // print help
    std::cout << "Help" << std::endl;
    std::cout << "  Print all help commands: " << std::endl << std::endl;

    // print help cmd
    std::cout << "Help <cmd>" << std::endl;
    std::cout << "  Print 'help <cmd>' to get specific help for the command: " << std::endl << std::endl;

    std::cout << "Enter commands" << std::endl;
    std::cout << "    - to execute individual commands." << std::endl << std::endl;

    // exit
    std::cout << "Exit" << std::endl;
    std::cout << "  Exit the trading platform!" << std::endl << std::endl;

    std::cout << "=======================================" << std::endl << std::endl;

}



/* print the user menu */
void MerkelMain::printCommandMenu()
{
    std::cout << "=======================================" << std::endl << std::endl;

    std::cout << "**** COMMAND MENU ****" << std::endl << std::endl;

    std::cout << "Enter number" << std::endl;
    std::cout << "    - to execute individual commands." << std::endl << std::endl;

    std::cout << "1" << "    - for prod" << std::endl;
    std::cout << "2" << "    - for min" << std::endl;
    std::cout << "3" << "    - for max" << std::endl;
    std::cout << "4" << "    - for avg" << std::endl;
    std::cout << "5" << "    - for predict" << std::endl;
    std::cout << "6" << "    - for my own" << std::endl;
    std::cout << "7" << "    - for time" << std::endl;
    std::cout << "8" << "    - for step" << std::endl;
    std::cout << "9" << "    - Exit the commands menu" << std::endl << std::endl;

    std::cout << "=======================================" << std::endl << std::endl;

}

void MerkelMain::printHelp() // menu 1
{
    std::cout << "Advisorbot is a trading platform." << std::endl << std::endl;
    std::cout << "The help commands are as follows." << std::endl<<std::endl;
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
    std::cout << "advisorBot> " << "When implementing a command, please ensure to enter all required parameters!" << std::endl << std::endl;
}


std::string MerkelMain::userInput()
{
    std::string userSelection = " ";
    std::cout << "advisorBot> " << "Make a selection from the options:" << std::endl << std::endl;
        std::getline(std::cin, userSelection);
        std::transform(userSelection.begin(), userSelection.end(), userSelection.begin(),[](unsigned char c) {return std::tolower(c); });
        std::cout << "You selected: " << userSelection << std::endl <<std::endl;
        return userSelection;
}


void MerkelMain::processUserInput(std::string userInput)
{
    std::vector<std::string> helpCommand;
    try
    {
        helpCommand = CSVReader::tokenise(userInput, ' ');
        for (const auto& command : helpCommand)
            std::cout << "Entered: " << command << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << "advisorBot> " << "Please enter a valid input, not " << userInput << "!" << std::endl;
    }

    std::cout << "advisorBot> " << "Showing details for: " << userInput << std::endl << std::endl;

    std::vector<std::string> helpInput = CSVReader::tokenise(userInput, ' ');
    
    for (std::string command : helpInput)
        std::cout << "advisorBot> " << "Your inputs: " << command << std::endl;

    for (const auto& command : helpCommand)
        std::cout << "advisorBot> " << "You entered helpCommands: " << command << std::endl;

    std::cout << "advisorBot> " << "The input: " << helpInput[0] << std::endl;

    if (userInput == "help")
    {
        std::cout << "advisorBot> " << "You requested the 'Help' menu." << std::endl << std::endl;
        MerkelMain::printHelp();
    }

    else if (userInput == "help prod")
    {
        std::cout << "advisorBot> " << "You requested help with the 'prod' command." << std::endl;
        std::cout << "advisorBot> " << "The <prod> command lists all available products, and no additional arguements are neededhelp." << std::endl;
        std::cout << "advisorBot> " << "For example, ETH/BTC, DOGE/BTC, etc." << std::endl << std::endl;
    }

    else if (userInput == "help min")
    {
        std::cout << "advisorBot> " << "You requested help with the 'min' command." << std::endl;
        std::cout << "advisorBot> " << "The <min> command finds the minimum bid or ask for a specified product in the current time period." << std::endl;
        std::cout << "advisorBot> " << "Arguments required are <bid> or <ask> and the product, such as ETH/BTC." << std::endl;
        std::cout << "advisorBot> " << "For example, 'The min ask for ETH/BTC is 1.0.'" << std::endl << std::endl;
    }

    else if (userInput == "help max")
    {
        std::cout << "advisorBot> " << "You requested help with the 'max' command." << std::endl;
        std::cout << "advisorBot> " << "The <max> command finds the maximum bid or ask for a specified product in the current time period." << std::endl;
        std::cout << "advisorBot> " << "Arguments required are <bid> or <ask> and the product, such as ETH/BTC." << std::endl;
        std::cout << "advisorBot> " << "For example, 'The max ask for ETH/BTC is 1.0.'" << std::endl << std::endl;
    }

    else if (userInput == "help avg")
    {
        std::cout << "advisorBot> " << "You requested help with the 'avg' command." << std::endl;
        std::cout << "advisorBot> " << "The <avg> command computes the average bid or ask for the specified product over the specified number of time periods." << std::endl;
        std::cout << "advisorBot> " << "Additional arguments required are <int> of time periods, <bid> or <ask> and the product, such as ETH/BTC." << std::endl;
        std::cout << "advisorBot> " << "For example, 'The average ETH/BTC ask price over the last 10 timesteps was 1.0.'" << std::endl << std::endl;
    }

    else if (userInput == "help predict")
    {
        std::cout << "advisorBot> " << "You requested help with the 'predict' command." << std::endl;
        std::cout << "advisorBot> " << "The <predict> command will predict the maximum or minimum bid or ask for the specific product specified in the next time period." << std::endl;
        std::cout << "advisorBot> " << "Additional arguments required are <min> or <max>, <bid> or <ask> and the product, such as ETH/BTC." << std::endl;
        std::cout << "advisorBot> " << "For example, 'The average ETH/BTC ask price over the last 10 timesteps was 1.0.'" << std::endl << std::endl;
    }

    else if (userInput == "help time")
    {
        std::cout << "advisorBot> " << "You requested help with the 'time' command." << std::endl;
        std::cout << "advisorBot> " << "The <time> command lists the current time period in the dataset." << std::endl;
        std::cout << "advisorBot> " << "For example, 2020/03/17 17:01:24." << std::endl << std::endl;
    }

    else if (userInput == "help step")
    {
        std::cout << "advisorBot> " << "You requested help with the 'step' command." << std::endl;
        std::cout << "advisorBot> " << "The <step> command moves trading to the next time period." << std::endl;
        std::cout << "advisorBot> " << "For example, ." << std::endl << std::endl;
    }

    else if (userInput == "help my own")
    {
        std::cout << "advisorBot> " << "You requested help with the 'my own' command." << std::endl;
        std::cout << "advisorBot> " << "The <my own> ." << std::endl;
        std::cout << "advisorBot> " << "For example, " << std::endl << std::endl;
    }

    else if (userInput == "prod")
    {
        std::cout << "advisorBot> " << "These are the available products:" << std::endl << std::endl;
        for (std::string const& p : orderBook.getKnownProducts())
        {
            std::cout << "Product: " << p << std::endl; // what are the products; timestamps also works
        }
    }

    else if (userInput == "min")
    {
        std::cout << "advisorBot> " << "You " << std::endl << std::endl;
    }

    else if (userInput == "max")
    {
        std::cout << "advisorBot> " << "You r" << std::endl << std::endl;
    }

    else if (userInput == "avg")
    {
        std::cout << "advisorBot > " << "You" << std::endl << std::endl;
    }

    else if (userInput == "predict")
    {
        std::cout << "advisorBot> " << "You r" << std::endl << std::endl;
    }

    else if (userInput == "time")
    {
        std::cout << "advisorBot> " << "The current time period is: " << currentTime << std::endl << std::endl;
    }

    else if (userInput == "step")
    {
        currentTime = orderBook.getNextTime(currentTime); // update time
        std::cout << "advisorBot> " << "The current time period is: " << currentTime << std::endl << std::endl;
    }

    else if (userInput == "my own")
    {
        std::cout << "advisorBot> " << "You " << std::endl << std::endl;
    }

    else if (userInput == "enter commands")
    {
        MerkelMain::printCommandMenu();
        std::cout << "advisorBot> " << "Please enter your command:" << std::endl;
        int userCommand = 0;
        std::string line;
        // std::string userCommand = " ";
        std::getline(std::cin, line);
        try
        {
            userCommand = std::stoi(line);
        }
        catch (const std::exception& e)
        {
            std::cout << "advisorBot> " << "Please enter a valid number, not " << line << "!" << std::endl;
        }

        std::cout << "advisorBot> " << "You selected: " << userCommand << std::endl << std::endl;

        std::string prodCommand;
        std::string p;
        std::string trade;
        std::string minInput;
        std::vector<std::string> minCommand;
        std::string maxInput;
        std::vector<std::string> maxCommand;
        std::string avgInput;
        std::vector<std::string> avgCommand;
        std::string predictInput;
        std::vector<std::string> predictCommand;
        std::string myInput;
        std::vector<std::string> myCommand;

        switch (userCommand)
        {
        case 1:
            std::cout << "1: prod"<<std::endl;
            std::cout << "advisorBot> " << "Please enter a 'prod' command in the following format: " << std::endl;
            std::cout << "advisorBot> " << "prod" << std::endl;
            std::getline(std::cin, prodCommand);
            std::transform(prodCommand.begin(), prodCommand.end(), prodCommand.begin(), [](unsigned char c) {return std::tolower(c); });
            std::cout << "advisorBot> " << "These are the available products:" << std::endl << std::endl;
            for (std::string const& p : orderBook.getKnownProducts())
            {
                std::cout << "advisorBot> " << "Product: " << p << std::endl; // what are the products; timestamps also works
            }
            break;

        case 2:
            std::cout << "2: min" << std::endl;
            std::cout << "advisorBot> " << "Please enter a <min> command in the following format: " << std::endl;
            std::cout << "advisorBot> " << "min ETH/BTC ask" << std::endl;
            std::getline(std::cin, minInput);
            //std::transform(minInput.begin(), minInput.end(), minInput.begin(), [](unsigned char c) {return std::tolower(c); });
            std::cout << "You entered: " << minInput << std::endl << std::endl;
            minCommand = CSVReader::tokenise(minInput, ' ');
            for (const auto& command : minCommand)
                    std::cout << "advisorBot> " << "Entered: " << command << std::endl;
            if (minCommand[0] != "min")
            {
                std::cout << "Please enter a valid <min> command!" << std::endl;
            }

            for (std::string const& p : orderBook.getKnownProducts())
            {
                if (p == minCommand[1])
                {
                    std::cout << "advisorBot> " << "Product: " << p << std::endl; // what are the products; timestamps also works

                    if (minCommand[2] == "ask")
                    {
                        std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask, p, currentTime);

                        std::cout << "advisorBot> " << "Min ask: " << OrderBook::getLowPrice(entries) << std::endl << std::endl;
                    }
                    else
                    {
                        std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::bid, p, currentTime);

                        std::cout << "advisorBot> " << "Min bid: " << OrderBook::getLowPrice(entries) << std::endl << std::endl;
                    }
                }
            }
            break;

        case 3:
            std::cout << "3: max" << std::endl;
            std::cout << "advisorBot> " << "Please enter a <max> command in the following format: " << std::endl;
            std::cout << "advisorBot> " << "max ETH/BTC ask" << std::endl;
            std::getline(std::cin, maxInput);
            // std::transform(maxInput.begin(), maxInput.end(), maxInput.begin(), [](unsigned char c) {return std::tolower(c); });
            std::cout << "advisorBot> " << "You entered: " << maxInput << std::endl << std::endl;
            maxCommand = CSVReader::tokenise(maxInput, ' ');
            for (const auto& command : maxCommand)
                std::cout << "advisorBot> " << "Entered: " << command << std::endl;
            if (maxCommand[0] != "max")
            {
                std::cout << "advisorBot> " << "Please enter a valid <max> command!" << std::endl;
            }
            for (std::string const& p : orderBook.getKnownProducts())
            {
                if (p == maxCommand[1])
                {
                    std::cout << "advisorBot> " << "Product: " << p << std::endl; // what are the products; timestamps also works

                    if (maxCommand[2] == "ask")
                    {
                        std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask, p, currentTime);

                        std::cout << "advisorBot> " << "Max bid: " << OrderBook::getHighPrice(entries) << std::endl << std::endl;
                    }
                    else
                    {
                        std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::bid, p, currentTime);

                        std::cout << "advisorBot> " << "Max ask: " << OrderBook::getHighPrice(entries) << std::endl << std::endl;
                    }
                }
            }
            break;

        case 4:
            std::cout << "4: avg" << std::endl;
            std::cout << "advisorBot> " << "Please enter a <avg> command in the following format: " << std::endl;
            std::cout << "advisorBot> " << "avg ETH/BTC ask 10" << std::endl;
            std::getline(std::cin, avgInput);
            std::transform(avgInput.begin(), avgInput.end(), avgInput.begin(), [](unsigned char c) {return std::tolower(c); });
            std::cout << "advisorBot> " << "You entered: " << avgInput << std::endl << std::endl;
            avgCommand = CSVReader::tokenise(avgInput, ' ');
            for (const auto& command : avgCommand)
                std::cout << "advisorBot> " << "Entered: " << command << std::endl;
            if (avgCommand[0] != "avg")
            {
                std::cout << "advisorBot> " << "Please enter a valid <avg> command!" << std::endl;
            }
            break;

        case 5:
            std::cout << "5: predict" << std::endl;
            std::cout << "advisorBot> " << "Please enter a <predict> command in the following format: " << std::endl;
            std::cout << "advisorBot> " << "predict max ETH/BTC bid" << std::endl;
            std::getline(std::cin, predictInput);
            std::transform(predictInput.begin(), predictInput.end(), predictInput.begin(), [](unsigned char c) {return std::tolower(c); });
            std::cout << "advisorBot> " << "You entered: " << predictInput << std::endl << std::endl;
            predictCommand = CSVReader::tokenise(predictInput, ' ');
            for (const auto& command : predictCommand)
                std::cout << "advisorBot> " << "Entered: " << command << std::endl;
            if (predictCommand[0] != "predict")
            {
                std::cout << "advisorBot> " << "Please enter a valid <predict> command!" << std::endl;
            }
            break;

        case 6:
            std::cout << "6: my own" << std::endl;
            std::cout << "advisorBot> " << "Please enter a <my> command in the following format: " << std::endl;
            std::cout << "advisorBot> " << "" << std::endl;
            std::getline(std::cin, myInput);
            std::transform(myInput.begin(), myInput.end(), myInput.begin(), [](unsigned char c) {return std::tolower(c); });
            std::cout << "advisorBot> " << "You entered: " << myInput << std::endl << std::endl;
            myCommand = CSVReader::tokenise(myInput, ' ');
            for (const auto& command : myCommand)
                std::cout << "Entered: " << command << std::endl;
            if (myCommand[0] != "my")
            {
                std::cout << "advisorBot> " << "Please enter a valid <my> command!" << std::endl;
            }
            break;

        case 7:
            std::cout << "7: time" << std::endl;
            std::cout << "advisorBot> " << "The current time period is: " << currentTime << std::endl << std::endl;
            break;

        case 8:
            std::cout << "8: step" << std::endl;
            currentTime = orderBook.getNextTime(currentTime); // update time
            std::cout << "advisorBot> " << "The current time period is: " << currentTime << std::endl << std::endl;
            break;
        }
        std::cout << std::endl;
        std::cout << "advisorBot> " << "Returning to main menu!" << std::endl << std::endl;
        // MerkelMain::printCommandMenu();

    }


    else if (userInput == "exit")
    {
        std::cout << "advisorBot> " << "Exiting the program!" << std::endl << std::endl;
        exitSession();
    }


    else if (userInput == "home")
    {
        std::cout << "advisorBot> " << "Exiting the commands!" << std::endl << std::endl;
        MerkelMain::printMenu();
    }


    else
    {
    std::cout << "advisorBot> " << "Your input did not identify a menu or help option." << std::endl;
    std::cout << "advisorBot> " << "Please re-enter a selection." << std::endl;
    }
}

int MerkelMain::exitSession()
{
    exit(0);
}