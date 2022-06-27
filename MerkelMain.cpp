// implementation file

#include "MerkelMain.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <cctype>
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


/* print the main user menu */
void MerkelMain::printMenu()
{
    std::cout << "=======================================" << std::endl << std::endl;

    std::cout << "**** MAIN MENU ****" << std::endl << std::endl;
    
    // list of all help commands
    std::cout << "Help:             print all help commands" << std::endl << std::endl;

    // help <cmd> details
    std::cout << "Help <cmd>:       print 'help <cmd>' to get help for a specific command" << std::endl << std::endl;
    
    // to enter individual commands
    std::cout << "Enter commands:   to execute individual commands" << std::endl << std::endl;
    
    // to exit the Advisorbot program
    std::cout << "Exit:             to exit the trading platform!" << std::endl << std::endl;

    std::cout << "=======================================" << std::endl << std::endl;
}


void MerkelMain::printCommandMenu() // the menu for the commands
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
    std::cout << "6" << "    - for stdev" << std::endl;
    std::cout << "7" << "    - for time" << std::endl;
    std::cout << "8" << "    - for step" << std::endl;
    std::cout << "9" << "    - Exit the commands menu" << std::endl << std::endl;

    std::cout << "=======================================" << std::endl << std::endl;
}


void MerkelMain::printHelp() // the help menu
{
    std::cout << "=======================================" << std::endl << std::endl;
    std::cout << "**** HELP ****" << std::endl << std::endl;
    std::cout << "advisorBot> " << "Advisorbot is a trading platform." << std::endl << std::endl;
    std::cout << "advisorBot> " << "The help commands are as follows." << std::endl<<std::endl;
    std::cout << "advisorBot> " << "If you want help for a specific command, enter as follow:   help <cmd>" << std::endl << std::endl;
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
    std::cout << "- stdev:" << std::endl;
    std::cout << "  calculate the standard deviation, for a specific product, for a specific number of time periods." <<std::endl <<std::endl;
    std::cout << "- time:" << std::endl;
    std::cout << "  print the current time period." << std::endl <<std::endl;
    std::cout << "- step:" << std::endl;
    std::cout << "  complete the current time period, and move to the next time period." << std::endl<<std::endl;
    std::cout << "advisorBot> " << "When implementing a command, please ensure to enter all required parameters!" << std::endl << std::endl;
}


std::string MerkelMain::userInput() // get user input form the help menu options
{
    std::string userSelection = " ";
    std::cout << "advisorBot> " << "Make a selection from the menu options:" << std::endl << std::endl;
        std::getline(std::cin, userSelection);
        std::transform(userSelection.begin(), userSelection.end(), userSelection.begin(),[](unsigned char c) {return std::tolower(c); }); // convert all characters to lower case
        std::cout << "advisorBot> " << "You selected: " << userSelection << std::endl <<std::endl;
        return userSelection; // for use in processUserInput
}


void MerkelMain::processUserInput(std::string userInput) // impelement the user inputs
{
    std::vector<std::string> helpCommand; // enter user command to parse it
    try
    {
        helpCommand = CSVReader::tokenise(userInput, ' '); // attempt to separate user command with ' '
        for (const auto& command : helpCommand)
            std::cout << "advisorBot> " << "You entered: " << command << std::endl; // print user command to confirm accuracy
    }
    catch (const std::exception& e) // if not able to separate user command, ask to re-enter
    {
        std::cout << "advisorBot> " << "Please enter a valid input, not " << userInput << "!" << std::endl;
    }

    std::cout << std::endl;

    if (userInput == "help")
    {
        std::cout << "advisorBot> " << "You requested the 'Help' menu." << std::endl << std::endl;
        MerkelMain::printHelp();
    }

    else if (userInput == "help prod") // print details on <prod> command
    {
        std::cout << "advisorBot> " << "You requested help with the 'prod' command." << std::endl;
        std::cout << "advisorBot> " << "The <prod> command lists all available products, and no additional arguements are needed." << std::endl;
        std::cout << "advisorBot> " << "An example output is: ETH/BTC, DOGE/BTC, etc." << std::endl << std::endl;
    }

    else if (userInput == "help min") // print details on <min> command
    {
        std::cout << "advisorBot> " << "You requested help with the 'min' command." << std::endl;
        std::cout << "advisorBot> " << "The <min> command finds the minimum bid or ask for a specified product in the current time period." << std::endl;
        std::cout << "advisorBot> " << "Arguments required are <bid> or <ask> and the product, such as ETH/BTC." << std::endl;
        std::cout << "advisorBot> " << "An example output is: 'The min ask for ETH/BTC is 1.0.'" << std::endl << std::endl;
    }

    else if (userInput == "help max") // print details on <max> command
    {
        std::cout << "advisorBot> " << "You requested help with the 'max' command." << std::endl;
        std::cout << "advisorBot> " << "The <max> command finds the maximum bid or ask for a specified product in the current time period." << std::endl;
        std::cout << "advisorBot> " << "Arguments required are <bid> or <ask> and the product, such as ETH/BTC." << std::endl;
        std::cout << "advisorBot> " << "An example output is: 'The max ask for ETH/BTC is 1.0.'" << std::endl << std::endl;
    }

    else if (userInput == "help avg") // print details on <avg> command
    {
        std::cout << "advisorBot> " << "You requested help with the 'avg' command." << std::endl;
        std::cout << "advisorBot> " << "The <avg> command computes the average bid or ask for the specified product for the specified number of time periods." << std::endl;
        std::cout << "advisorBot> " << "Additional arguments required are <int> of time periods, <bid> or <ask> and the product, such as ETH/BTC." << std::endl;
        std::cout << "advisorBot> " << "An example output is: 'The average ETH/BTC ask price over the last 10 timesteps was 1.0.'" << std::endl << std::endl;
    }

    else if (userInput == "help predict") // print details on <predict> command
    {
        std::cout << "advisorBot> " << "You requested help with the 'predict' command." << std::endl;
        std::cout << "advisorBot> " << "The <predict> command will predict the maximum or minimum bid or ask for the specified product in the next time period." << std::endl;
        std::cout << "advisorBot> " << "Additional arguments required are <min> or <max>, <bid> or <ask> and the product, such as ETH/BTC." << std::endl;
        std::cout << "advisorBot> " << "An example output is: 'The predicted maximum ETH/BTC ask price in the next time period is 1.0.'" << std::endl << std::endl;
    }

    else if (userInput == "help time") // print details on <time> command
    {
        std::cout << "advisorBot> " << "You requested help with the 'time' command." << std::endl;
        std::cout << "advisorBot> " << "The <time> command lists the current time period in the dataset." << std::endl;
        std::cout << "advisorBot> " << "An example output is: 2020/03/17 17:01:24." << std::endl << std::endl;
    }

    else if (userInput == "help step") // print details on <step> command
    {
        std::cout << "advisorBot> " << "You requested help with the 'step' command." << std::endl;
        std::cout << "advisorBot> " << "The <step> command moves trading to the next time period." << std::endl;
        std::cout << "advisorBot> " << "The output is the timestamp for the next time period." << std::endl << std::endl;
    }

    else if (userInput == "help stdev") // print details on <stdev> command
    {
        std::cout << "advisorBot> " << "You requested help with the 'stdev' command." << std::endl;
        std::cout << "advisorBot> " << "The <stdev> command will calculate the stadard deviation for the product specified for the specific number of time periods." << std::endl;
        std::cout << "advisorBot> " << "An example output is: 'The standart deviation for ETH/BTC over the last 10 timesteps was 1.0.'" << std::endl << std::endl;
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
        std::string minInput;
        std::vector<std::string> minCommand;
        std::cout << "advisorBot> " << "Please enter a <min> command in the following format: " << std::endl;
        std::cout << "advisorBot> " << "min ETH/BTC ask" << std::endl;
        std::getline(std::cin, minInput);
        std::cout << "You entered: " << minInput << std::endl << std::endl;
        minCommand = CSVReader::tokenise(minInput, ' '); // separate user command with ' '
        for (const auto& command : minCommand)
            std::cout << "advisorBot> " << "You entered: " << command << std::endl;
        if (minCommand[0] != "min")
        {
            std::cout << "Please enter a valid <min> command!" << std::endl;
        }

        for (std::string const& p : orderBook.getKnownProducts())
        {
            if (p == minCommand[1]) // user enter product value
            {
                std::cout << "advisorBot> " << "Product: " << p << std::endl; // which product

                if (minCommand[2] == "ask")
                {
                    std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask, p, currentTime);

                    std::cout << "advisorBot> " << "Minimum ask " << "for timeperiod: " << currentTime << " is: " << OrderBook::getLowPrice(entries) << std::endl << std::endl;
                }
                else
                {
                    std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::bid, p, currentTime);

                    std::cout << "advisorBot> " << "Minimum bid " << "for timeperiod: " << currentTime << " is: " << OrderBook::getLowPrice(entries) << std::endl << std::endl;
                }
            } // end if
        } // end for
    }

    else if (userInput == "max")
    {
        std::string maxInput;
        std::vector<std::string> maxCommand;
        std::cout << "advisorBot> " << "Please enter a <max> command in the following format: " << std::endl;
        std::cout << "advisorBot> " << "max ETH/BTC ask" << std::endl;
        std::getline(std::cin, maxInput);
        std::cout << "advisorBot> " << "You entered: " << maxInput << std::endl << std::endl;
        maxCommand = CSVReader::tokenise(maxInput, ' ');
        for (const auto& command : maxCommand)
            std::cout << "advisorBot> " << "You entered: " << command << std::endl;
        if (maxCommand[0] != "max")
        {
            std::cout << "advisorBot> " << "Please enter a valid <max> command!" << std::endl;
        }
        for (std::string const& p : orderBook.getKnownProducts())
        {
            if (p == maxCommand[1]) // user enter product value
            {
                std::cout << "advisorBot> " << "Product: " << p << std::endl; // what are the products; timestamps also works

                if (maxCommand[2] == "ask")
                {
                    std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask, p, currentTime);

                    std::cout << "advisorBot> " << "Maximum ask " << "for timeperiod: " << currentTime << " is: " << OrderBook::getHighPrice(entries) << std::endl << std::endl;
                }
                else
                {
                    std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::bid, p, currentTime);

                    std::cout << "advisorBot> " << "Maximum bid " << "for timeperiod: " << currentTime << " is: " << OrderBook::getHighPrice(entries) << std::endl << std::endl;
                }
            } // end if
        } // end for
    }

    else if (userInput == "avg")
    {
        std::string avgInput;
        std::vector<std::string> avgCommand;
        std::vector<std::string> timestamps;
        std::vector<std::string> avgtimestamps;
        int i;
        ptrdiff_t pos;
        std::cout << "advisorBot> " << "Please enter a <avg> command in the following format: " << std::endl;
        std::cout << "advisorBot> " << "avg ETH/BTC ask 10" << std::endl;
        std::getline(std::cin, avgInput);
        std::cout << "advisorBot> " << "You entered: " << avgInput << std::endl << std::endl;
        avgCommand = CSVReader::tokenise(avgInput, ' ');
        for (const auto& command : avgCommand)
            std::cout << "advisorBot> " << "You entered: " << command << std::endl;
        if (avgCommand[0] != "avg")
        {
            std::cout << "advisorBot> " << "Please enter a valid <avg> command!" << std::endl;
        }

        std::cout << "The current time is: " << currentTime << std::endl;
        timestamps = orderBook.getTimestamps();

        pos = find(timestamps.begin(), timestamps.end(), currentTime) - timestamps.begin(); // get position of current timestamp in vector of all timestamps
        std::cout << "Index of current time = " << pos << std::endl;
        std::cout << std::endl;

        if ((pos - std::stoi(avgCommand[3]) < 1))
        {
            std::cout << "The average cannot be computed, since the number of timestamps is less than input: " << avgCommand[3] << std::endl;
        }

        try
        {
            if ((pos - std::stoi(avgCommand[3]) > 0))
            {
                for (i = (pos - std::stoi(avgCommand[3]) + 1); i <= pos; i++) // convert number of timestamps for average to integer
                {
                    std::cout << "i: " << i << std::endl;
                    avgtimestamps.push_back(timestamps[i]);
                }
            }
        }
        catch (const std::exception& e) // if not able to separate user command, ask to re-enter
        {
            std::cout << "advisorBot> " << "The average cannot be computed since there are not enough time periods: " << avgCommand[3] << std::endl;
        }


        std::cout << "Length: " << avgtimestamps.size() << std::endl;

        for (std::string v : avgtimestamps)
        {
            std::cout << "Timestamp: " << v << std::endl;
        }

        for (std::string const& p : orderBook.getKnownProducts())
        {
            if (p == avgCommand[1]) // user enter product value
            {
                std::cout << "advisorBot> " << "Product: " << p << std::endl; // what are the products

                // std::cout << "TRADE: " << avgCommand[2] << std::endl << std::endl;
                    
                if (avgCommand[2] == "bid")
                {
                    int bidCount = 0;
                    double sum = 0;
                    double bidAvg = 0;
                    for (std::string const& t : avgtimestamps)
                    {
                        std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask, p, t);

                        std::cout << "advisorBot> " << "Minimum bid for " << "timestamp: " << t << " is: " << OrderBook::getLowPrice(entries) << std::endl;
                        std::cout << "advisorBot> " << "Maximum bid for " << "timestamp: " << t << " is: " << OrderBook::getHighPrice(entries) << std::endl;
                        double getAvg = OrderBook::getAvg(entries);
                        std::cout << "advisorBot> " << "Average bid for " << "timestamp: " << t << " is: " << getAvg << std::endl << std::endl;
                        bidCount += 1;
                        sum += getAvg;
                        bidAvg = sum / bidCount;
                    }
                    std::cout << "advisorBot> " << "The overall average bid for " << avgtimestamps.size() << " timestamp periods" << " is: " << bidAvg << std::endl << std::endl;
                }
                else
                {
                    int askCount = 0;
                    double sum = 0;
                    double askAvg = 0;
                    for (std::string const& t : avgtimestamps)
                    {
                        std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::bid, p, t);

                        std::cout << "advisorBot> " << "Minimum ask for " << "timestamp: " << t << " is: " << OrderBook::getLowPrice(entries) << std::endl;
                        std::cout << "advisorBot> " << "Maximum ask for " << "timestamp: " << t << " is: " << OrderBook::getHighPrice(entries) << std::endl;
                        double getAvg = OrderBook::getAvg(entries);
                        std::cout << "advisorBot> " << "Average ask for " << "timestamp: " << t << " is: " << getAvg << std::endl << std::endl;
                        askCount += 1;
                        sum += getAvg;
                        askAvg = sum / askCount;
                    }
                    std::cout << "advisorBot> " << "The overall average ask for " << avgtimestamps.size() << " timestamp periods" << " is: " << askAvg << std::endl << std::endl;
                } // end else
            } // end if
        } // end for
    } // end else if 'avg'

    else if (userInput == "predict")
    {
        std::string predictInput;
        std::vector<std::string> predictCommand;
        std::vector<std::string> timestamps;
        std::vector<std::string> predicttimestamps;
        int i;
        ptrdiff_t pos;
        std::cout << "advisorBot> " << "Please enter a <predict> command in the following format: " << std::endl;
        std::cout << "advisorBot> " << "predict max ETH/BTC bid" << std::endl;
        try
        {
            std::getline(std::cin, predictInput);
        }
        catch (const std::exception& e)
        {
            std::cout << "advisorBot> " << "Please enter a command!" << "!" << std::endl;
        }
        std::cout << "advisorBot> " << "You entered: " << predictInput << std::endl << std::endl;
        predictCommand = CSVReader::tokenise(predictInput, ' ');
        for (const auto& command : predictCommand)
            std::cout << "advisorBot> " << "You entered: " << command << std::endl;
        if (predictCommand[0] != "predict")
        {
            std::cout << "advisorBot> " << "Please enter a valid <predict> command!" << std::endl;
        }
        std::cout << "The current time is: " << currentTime << std::endl;
        timestamps = orderBook.getTimestamps();

        pos = find(timestamps.begin(), timestamps.end(), currentTime) - timestamps.begin();
        std::cout << "Index of curren time = " << pos << std::endl;
        std::cout << std::endl;

        if (pos > 5)
        {
            for (i = (pos - 4); i <= pos; i++)
            {
                //std::cout << "i: " << i << std::endl;
                predicttimestamps.push_back(timestamps[i]);
            }
        }
        else
        {
            std::cout << "Predict will only work when there are at least five timestamps!" << std::endl;
        }

        for (std::string v : predicttimestamps)
        {
            std::cout << "Timestamp: " << v << std::endl;
        }

        for (std::string const& p : orderBook.getKnownProducts())
        {
            if (p == predictCommand[2]) // user enter product value
            {
                std::cout << "advisorBot> " << "Product: " << p << std::endl; // what are the products

                // std::cout << "TRADE: " << predictCommand[3] << std::endl << std::endl;

                if (predictCommand[3] == "bid")
                {
                    double getpredict = 0;
                    std::vector<double> getminpredict;
                    std::vector<double> getmaxpredict;
                    std::vector<double> weightings{ 0.4, 0.3, 0.15, 0.1, 0.05 };
                    for (std::string const& t : predicttimestamps)
                    {
                        std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::bid, p, t);
                        if (predictCommand[1] == "min")
                            {
                                getpredict = OrderBook::getLowPrice(entries);
                                getminpredict.push_back(getpredict);
                                std::cout << "advisorBot> " << "Minimum bid for " << "timestamp: " << t << " is: " << getpredict << std::endl;
                            }
                            else
                            {
                                getpredict = OrderBook::getHighPrice(entries);
                                getmaxpredict.push_back(getpredict);
                                std::cout << "advisorBot> " << "Maximum bid for " << "timestamp: " << t << " is: " << getpredict << std::endl;
                            }
                    } // end for
                    if (getminpredict.size() > 0)
                    {
                        double minPredict = 0;
                        minPredict = (getminpredict[0] * 0.4) + (getminpredict[1] * 0.3) + (getminpredict[2] * 0.15) + (getminpredict[3] * 0.1) + (getminpredict[4] * 0.05);
                        std::cout << "advisorBot> " << "The predicted minimum bid for the next time period is: " << minPredict << std::endl << std::endl;
                    }
                    else if (getmaxpredict.size() > 0)
                    {
                        double maxPredict = 0;
                        maxPredict = (getmaxpredict[0] * 0.4) + (getmaxpredict[1] * 0.3) + (getmaxpredict[2] * 0.15) + (getmaxpredict[3] * 0.1) + (getmaxpredict[4] * 0.05);
                        std::cout << "advisorBot> " << "The predicted maximum bid for the next time period is: " << maxPredict << std::endl << std::endl;
                    }
                } // end if
                else // ask trades
                {
                    double getpredict = 0;
                    std::vector<double> getminpredict;
                    std::vector<double> getmaxpredict;
                    std::vector<double> weightings{ 0.4, 0.3, 0.15, 0.1, 0.05 };
                    for (std::string const& t : predicttimestamps)
                    {
                        std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask, p, t);
                        if (predictCommand[1] == "min")
                        {
                            getpredict = OrderBook::getLowPrice(entries);
                            getminpredict.push_back(getpredict);
                            std::cout << "advisorBot> " << "Minimum ask for " << "timestamp: " << t << " is: " << getpredict << std::endl;
                        }
                        else
                        {
                            getpredict = OrderBook::getHighPrice(entries);
                            getmaxpredict.push_back(getpredict);
                            std::cout << "advisorBot> " << "Maximum ask for " << "timestamp: " << t << " is: " << getpredict << std::endl;
                        }
                    } // end for
                    if (getminpredict.size() > 0)
                    {
                        double minPredict = 0;
                        minPredict = (getminpredict[0] * 0.4) + (getminpredict[1] * 0.3) + (getminpredict[2] * 0.15) + (getminpredict[3] * 0.1) + (getminpredict[4] * 0.05);
                        std::cout << "advisorBot> " << "The predicted minimum ask for the next time period is: " << minPredict << std::endl << std::endl;
                    }
                    else if (getmaxpredict.size() > 0)
                    {
                        double maxPredict = 0;
                        maxPredict = (getmaxpredict[0] * 0.4) + (getmaxpredict[1] * 0.3) + (getmaxpredict[2] * 0.15) + (getmaxpredict[3] * 0.1) + (getmaxpredict[4] * 0.05);
                        std::cout << "advisorBot> " << "The predicted maximum ask for the next time period is: " << maxPredict << std::endl << std::endl;
                    } // end if
                } // end else
            } // end if
        } // end for
    } // end else if 'predict'

    else if (userInput == "time")
    {
        std::cout << "advisorBot> " << "The current time period is: " << currentTime << std::endl << std::endl;
    }

    else if (userInput == "step")
    {
        currentTime = orderBook.getNextTime(currentTime); // update time
        std::cout << "advisorBot> " << "The current time period is: " << currentTime << std::endl << std::endl;
    }

    else if (userInput == "stdev")
    {
    std::string avgInput;
    std::vector<std::string> avgCommand;
    std::vector<std::string> timestamps;
    std::vector<std::string> avgtimestamps;
    int i;
    ptrdiff_t pos;
    std::cout << "advisorBot> " << "Please enter a <avg> command in the following format: " << std::endl;
    std::cout << "advisorBot> " << "stdev ETH/BTC ask 10" << std::endl;
    std::getline(std::cin, avgInput);
    std::cout << "advisorBot> " << "You entered: " << avgInput << std::endl << std::endl;
    avgCommand = CSVReader::tokenise(avgInput, ' ');
    for (const auto& command : avgCommand)
        std::cout << "advisorBot> " << "You entered: " << command << std::endl;
    if (avgCommand[0] != "stdev")
    {
        std::cout << "advisorBot> " << "Please enter a valid <avg> command!" << std::endl;
    }

    std::cout << "The current time is: " << currentTime << std::endl;
    timestamps = orderBook.getTimestamps();

    pos = find(timestamps.begin(), timestamps.end(), currentTime) - timestamps.begin(); // get position of current timestamp in vector of all timestamps
    std::cout << "Index of current time = " << pos << std::endl;
    std::cout << std::endl;

    if ((pos - std::stoi(avgCommand[3]) < 1))
    {
        std::cout << "The average cannot be computed, since the number of timestamps is less than input: " << avgCommand[3] << std::endl;
    }

    try
    {
        if ((pos - std::stoi(avgCommand[3]) > 0))
        {
            for (i = (pos - std::stoi(avgCommand[3]) + 1); i <= pos; i++) // convert number of timestamps for average to integer
            {
                std::cout << "i: " << i << std::endl;
                avgtimestamps.push_back(timestamps[i]);
            }
        }
    }
    catch (const std::exception& e) // if not able to separate user command, ask to re-enter
    {
        std::cout << "advisorBot> " << "The average cannot be computed since there are not enough time periods: " << avgCommand[3] << std::endl;
    }


    std::cout << "Length: " << avgtimestamps.size() << std::endl;

    for (std::string v : avgtimestamps)
    {
        std::cout << "Timestamp: " << v << std::endl;
    }

    for (std::string const& p : orderBook.getKnownProducts())
    {
        if (p == avgCommand[1]) // user enter product value
        {
            std::cout << "advisorBot> " << "Product: " << p << std::endl; // what are the products

            // std::cout << "TRADE: " << avgCommand[2] << std::endl << std::endl;

            if (avgCommand[2] == "bid")
            {
                int bidCount = 0;
                double sum = 0;
                double bidAvg = 0;
                double std = 0;
                double stdev = 0;
                for (std::string const& t : avgtimestamps)
                {
                    std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask, p, t);

                    std::cout << "advisorBot> " << "Minimum bid for " << "timestamp: " << t << " is: " << OrderBook::getLowPrice(entries) << std::endl;
                    std::cout << "advisorBot> " << "Maximum bid for " << "timestamp: " << t << " is: " << OrderBook::getHighPrice(entries) << std::endl;
                    double getAvg = OrderBook::getAvg(entries);
                    std::cout << "advisorBot> " << "Average bid for " << "timestamp: " << t << " is: " << getAvg << std::endl << std::endl;
                    bidCount += 1;
                    sum += getAvg;
                    bidAvg = sum / bidCount;
                    for (i = 0; i < avgtimestamps.size(); i++)
                    {
                        std += pow((OrderBook::getLowPrice(entries) + OrderBook::getHighPrice(entries) / 2) - bidAvg, 2);
                    }
                    stdev = sqrt(std / 10);
                }
                std::cout << "advisorBot> " << "The overall standard deviation for " << avgtimestamps.size() << " timestamp periods" << " is: " << stdev << std::endl << std::endl;
            }
            else
            {
                int askCount = 0;
                double sum = 0;
                double askAvg = 0;
                for (std::string const& t : avgtimestamps)
                {
                    std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::bid, p, t);

                    std::cout << "advisorBot> " << "Minimum ask for " << "timestamp: " << t << " is: " << OrderBook::getLowPrice(entries) << std::endl;
                    std::cout << "advisorBot> " << "Maximum ask for " << "timestamp: " << t << " is: " << OrderBook::getHighPrice(entries) << std::endl;
                    double getAvg = OrderBook::getAvg(entries);
                    std::cout << "advisorBot> " << "Average ask for " << "timestamp: " << t << " is: " << getAvg << std::endl << std::endl;
                    askCount += 1;
                    sum += getAvg;
                    askAvg = sum / askCount;
                }
                std::cout << "advisorBot> " << "The overall standard deviation for " << avgtimestamps.size() << " timestamp periods" << " is: " << askAvg << std::endl << std::endl;
            } // end else
        } // end if
    } // end for
    } // end else if 'stdev'

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
        std::vector<std::string> timestamps;
        std::vector<std::string> avgtimestamps;
        int i;
        ptrdiff_t pos;
        std::string predictInput;
        std::vector<std::string> predictCommand;
        std::vector<std::string> predicttimestamps;
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
            std::cout << "You entered: " << minInput << std::endl << std::endl;
            minCommand = CSVReader::tokenise(minInput, ' ');
            for (const auto& command : minCommand)
                    std::cout << "advisorBot> " << "You entered: " << command << std::endl;
            if (minCommand[0] != "min")
            {
                std::cout << "Please enter a valid <min> command!" << std::endl;
            }

            for (std::string const& p : orderBook.getKnownProducts())
            {
                if (p == minCommand[1]) // user enter product value
                {
                    std::cout << "advisorBot> " << "Product: " << p << std::endl; // what are the products; timestamps also works

                    if (minCommand[2] == "ask")
                    {
                        std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask, p, currentTime);

                        std::cout << "advisorBot> " << "Minimum ask " << "for timeperiod: " << currentTime << " is: " << OrderBook::getLowPrice(entries) << std::endl << std::endl;
                    }
                    else
                    {
                        std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::bid, p, currentTime);

                        std::cout << "advisorBot> " << "Minimum bid " << "for timeperiod: " << currentTime << " is: " << OrderBook::getLowPrice(entries) << std::endl << std::endl;
                    }
                } // end if
            }
            break;

        case 3:
            std::cout << "3: max" << std::endl;
            std::cout << "advisorBot> " << "Please enter a <max> command in the following format: " << std::endl;
            std::cout << "advisorBot> " << "max ETH/BTC ask" << std::endl;
            std::getline(std::cin, maxInput);
            std::cout << "advisorBot> " << "You entered: " << maxInput << std::endl << std::endl;
            maxCommand = CSVReader::tokenise(maxInput, ' ');
            for (const auto& command : maxCommand)
                std::cout << "advisorBot> " << "You entered: " << command << std::endl;
            if (maxCommand[0] != "max")
            {
                std::cout << "advisorBot> " << "Please enter a valid <max> command!" << std::endl;
            }
            for (std::string const& p : orderBook.getKnownProducts())
            {
                if (p == maxCommand[1]) // user enter product value
                {
                    std::cout << "advisorBot> " << "Product: " << p << std::endl; // what are the products; timestamps also works

                    if (maxCommand[2] == "ask")
                    {
                        std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask, p, currentTime);

                        std::cout << "advisorBot> " << "Maximum ask " << "for timeperiod: " << currentTime << " is: " << OrderBook::getHighPrice(entries) << std::endl << std::endl;
                    }
                    else
                    {
                        std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::bid, p, currentTime);

                        std::cout << "advisorBot> " << "Maximum bid " << "for timeperiod: " << currentTime << " is: " << OrderBook::getHighPrice(entries) << std::endl << std::endl;
                    }
                } // end if
            }
            break;

        case 4:
            std::cout << "4: avg" << std::endl;
            std::cout << "advisorBot> " << "Please enter a <avg> command in the following format: " << std::endl;
            std::cout << "advisorBot> " << "avg ETH/BTC ask 10" << std::endl;
            std::getline(std::cin, avgInput);
            std::cout << "advisorBot> " << "You entered: " << avgInput << std::endl << std::endl;
            avgCommand = CSVReader::tokenise(avgInput, ' ');
            for (const auto& command : avgCommand)
                std::cout << "advisorBot> " << "You entered: " << command << std::endl;
            if (avgCommand[0] != "avg")
            {
                std::cout << "advisorBot> " << "Please enter a valid <avg> command!" << std::endl;
            }
            std::cout << "The current time is: " << currentTime << std::endl;
            timestamps = orderBook.getTimestamps();
            
            // std::cout << "Number of timestamps: " << timestamps.size() << std::endl;
            pos = find(timestamps.begin(), timestamps.end(), currentTime) - timestamps.begin();
            std::cout << "Index of current time = " << pos << std::endl;
            std::cout << std::endl;
            
            
            if ((pos - std::stoi(avgCommand[3]) < 1))
            {
                std::cout << "The average cannot be computed, since the number of timestamps is less than input: " << avgCommand[3] << std::endl;
            }

            try
            {
                if ((pos - std::stoi(avgCommand[3]) > 0))
                {
                    for (i = (pos - std::stoi(avgCommand[3]) + 1); i <= pos; i++) // convert number of timestamps for average to integer
                    {
                        std::cout << "i: " << i << std::endl;
                        avgtimestamps.push_back(timestamps[i]);
                    }
                }
            }
            catch (const std::exception& e) // if not able to separate user command, ask to re-enter
            {
                std::cout << "advisorBot> " << "The average cannot be computed since there are not enough time periods: " << avgCommand[3] << std::endl;
            }

             std::cout << "Length: " << avgtimestamps.size() << std::endl;
            
            for (std::string v : avgtimestamps)
            {
                std::cout << "Timestamp: " << v << std::endl;
            }

            for (std::string const& p : orderBook.getKnownProducts())
            {
                if (p == avgCommand[1]) // user enter product value
                {
                    std::cout << "advisorBot> " << "Product: " << p << std::endl; // what are the products
                    
                    // std::cout << "TRADE: " << avgCommand[2] << std::endl << std::endl;
                    
                    if (avgCommand[2] == "bid")
                    {
                        int bidCount = 0;
                        double sum = 0;
                        double bidAvg = 0;
                        for (std::string const& t : avgtimestamps)
                        {
                            std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask, p, t);

                            std::cout << "advisorBot> " << "Minimum bid for " << "timestamp: " << t << " is: " << OrderBook::getLowPrice(entries) << std::endl;
                            std::cout << "advisorBot> " << "Maximum bid for " << "timestamp: " << t << " is: " << OrderBook::getHighPrice(entries) << std::endl;
                            double getAvg = OrderBook::getAvg(entries);
                            std::cout << "advisorBot> " << "Average bid for " << "timestamp: " << t << " is: " << getAvg << std::endl << std::endl;
                            bidCount += 1;
                            sum += getAvg;
                            bidAvg = sum / bidCount;
                        }
                        std::cout << "advisorBot> " << "The overall average bid for " << avgtimestamps.size() << " timestamp periods" << " is: " << bidAvg << std::endl << std::endl;
                    }
                    else
                    {
                        int askCount = 0;
                        double sum = 0;
                        double askAvg = 0;
                        for (std::string const& t : avgtimestamps)
                        {
                            std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::bid, p, t);

                            std::cout << "advisorBot> " << "Minimum ask for " << "timestamp: " << t << " is: " << OrderBook::getLowPrice(entries) << std::endl;
                            std::cout << "advisorBot> " << "Maximum ask for " << "timestamp: " << t << " is: " << OrderBook::getHighPrice(entries) << std::endl;
                            double getAvg = OrderBook::getAvg(entries);
                            std::cout << "advisorBot> " << "Average ask for " << "timestamp: " << t << " is: " << getAvg << std::endl << std::endl;
                            askCount += 1;
                            sum += getAvg;
                            askAvg = sum / askCount;
                        }
                        std::cout << "advisorBot> " << "The overall average ask for " << avgtimestamps.size() << " timestamp periods" << " is: " << askAvg << std::endl << std::endl;
                    } // end else
                } // end if
            } // end for

            break;

        case 5:
            std::cout << "5: predict" << std::endl;
            std::cout << "advisorBot> " << "Please enter a <predict> command in the following format: " << std::endl;
            std::cout << "advisorBot> " << "predict max ETH/BTC bid" << std::endl;
            std::getline(std::cin, predictInput);
            std::cout << "advisorBot> " << "You entered: " << predictInput << std::endl << std::endl;
            predictCommand = CSVReader::tokenise(predictInput, ' ');
            for (const auto& command : predictCommand)
                std::cout << "advisorBot> " << "You entered: " << command << std::endl;
            if (predictCommand[0] != "predict")
            {
                std::cout << "advisorBot> " << "Please enter a valid <predict> command!" << std::endl;
            }
            std::cout << "The current time is: " << currentTime << std::endl;
            timestamps = orderBook.getTimestamps();

            // std::cout << "Number of timestamps: " << timestamps.size() << std::endl;
            pos = find(timestamps.begin(), timestamps.end(), currentTime) - timestamps.begin();
            std::cout << "Index of current time = " << pos << std::endl;
            std::cout << std::endl;

            if (pos > 5)
            {
                for (i = (pos - 4); i <= pos; i++)
                {
                    // std::cout << "i: " << i << std::endl;
                    predicttimestamps.push_back(timestamps[i]);
                }
            }
            else
            {
                std::cout << "Predict will only work when there are at least five timestamps!" << std::endl;
            }

             std::cout << "Length: " << predicttimestamps.size() << std::endl;

            for (std::string v : predicttimestamps)
            {
                std::cout << "Timestamp: " << v << std::endl;
            }

            for (std::string const& p : orderBook.getKnownProducts())
            {
                if (p == predictCommand[2]) // user enter product value
                {
                    std::cout << "advisorBot> " << "Product: " << p << std::endl; // what are the products

                    // std::cout << "TRADE: " << predictCommand[3] << std::endl << std::endl;

                    if (predictCommand[3] == "bid")
                    {
                        double getpredict = 0;
                        std::vector<double> getminpredict;
                        std::vector<double> getmaxpredict;
                        std::vector<double> weightings{ 0.4, 0.3, 0.15, 0.1, 0.05 };
                        for (std::string const& t : predicttimestamps)
                        {
                            std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::bid, p, t);
                            if (predictCommand[1] == "min")
                            {
                                getpredict = OrderBook::getLowPrice(entries);
                                getminpredict.push_back(getpredict);
                                std::cout << "advisorBot> " << "Minimum bid for " << "timestamp: " << t << " is: " << getpredict << std::endl;
                            }
                            else
                            {
                                getpredict = OrderBook::getHighPrice(entries);
                                getmaxpredict.push_back(getpredict);
                                std::cout << "advisorBot> " << "Maximum bid for " << "timestamp: " << t << " is: " << getpredict << std::endl;
                            }
                        } // end for
                        if (getminpredict.size() > 0)
                        {
                            double minPredict = 0;
                            minPredict = (getminpredict[0] * 0.4) + (getminpredict[1] * 0.3) + (getminpredict[2] * 0.15) + (getminpredict[3] * 0.1) + (getminpredict[4] * 0.05);
                            std::cout << "advisorBot> " << "The predicted minimum bid for the next time period is: " << minPredict << std::endl << std::endl;
                        }
                        else if (getmaxpredict.size() > 0)
                        {
                            double maxPredict = 0;
                            maxPredict = (getmaxpredict[0] * 0.4) + (getmaxpredict[1] * 0.3) + (getmaxpredict[2] * 0.15) + (getmaxpredict[3] * 0.1) + (getmaxpredict[4] * 0.05);
                            std::cout << "advisorBot> " << "The predicted maximum bid for the next time period is: " << maxPredict << std::endl << std::endl;
                        }
                    } // end if
                    else // ask trades
                    {
                        double getpredict = 0;
                        std::vector<double> getminpredict;
                        std::vector<double> getmaxpredict;
                        std::vector<double> weightings{ 0.4, 0.3, 0.15, 0.1, 0.05 };
                        for (std::string const& t : predicttimestamps)
                        {
                            std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask, p, t);
                            if (predictCommand[1] == "min")
                            {
                                getpredict = OrderBook::getLowPrice(entries);
                                getminpredict.push_back(getpredict);
                                std::cout << "advisorBot> " << "Minimum ask for " << "timestamp: " << t << " is: " << getpredict << std::endl;
                            }
                            else
                            {
                                getpredict = OrderBook::getHighPrice(entries);
                                getmaxpredict.push_back(getpredict);
                                std::cout << "advisorBot> " << "Maximum ask for " << "timestamp: " << t << " is: " << getpredict << std::endl;
                            }
                        } // end for
                        if (getminpredict.size() > 0)
                        {
                            double minPredict = 0;
                            minPredict = (getminpredict[0] * 0.4) + (getminpredict[1] * 0.3) + (getminpredict[2] * 0.15) + (getminpredict[3] * 0.1) + (getminpredict[4] * 0.05);
                            std::cout << "advisorBot> " << "The predicted minimum ask for the next time period is: " << minPredict << std::endl << std::endl;
                        }
                        else if (getmaxpredict.size() > 0)
                        {
                            double maxPredict = 0;
                            maxPredict = (getmaxpredict[0] * 0.4) + (getmaxpredict[1] * 0.3) + (getmaxpredict[2] * 0.15) + (getmaxpredict[3] * 0.1) + (getmaxpredict[4] * 0.05);
                            std::cout << "advisorBot> " << "The predicted maximum ask for the next time period is: " << maxPredict << std::endl << std::endl;
                        } // end if
                    } // end else
                } // end if
            } // end for

            break;

        case 6:
            std::cout << "6: stdev" << std::endl;
                std::cout << "advisorBot> " << "Please enter a <avg> command in the following format: " << std::endl;
                std::cout << "advisorBot> " << "stdev ETH/BTC ask 10" << std::endl;
                std::getline(std::cin, avgInput);
                std::cout << "advisorBot> " << "You entered: " << avgInput << std::endl << std::endl;
                avgCommand = CSVReader::tokenise(avgInput, ' ');
                for (const auto& command : avgCommand)
                    std::cout << "advisorBot> " << "You entered: " << command << std::endl;
                if (avgCommand[0] != "stdev")
                {
                    std::cout << "advisorBot> " << "Please enter a valid <avg> command!" << std::endl;
                }

                std::cout << "The current time is: " << currentTime << std::endl;
                timestamps = orderBook.getTimestamps();

                pos = find(timestamps.begin(), timestamps.end(), currentTime) - timestamps.begin(); // get position of current timestamp in vector of all timestamps
                std::cout << "Index of current time = " << pos << std::endl;
                std::cout << std::endl;

                if ((pos - std::stoi(avgCommand[3]) < 1))
                {
                    std::cout << "The average cannot be computed, since the number of timestamps is less than input: " << avgCommand[3] << std::endl;
                }

                try
                {
                    if ((pos - std::stoi(avgCommand[3]) > 0))
                    {
                        for (i = (pos - std::stoi(avgCommand[3]) + 1); i <= pos; i++) // convert number of timestamps for average to integer
                        {
                            std::cout << "i: " << i << std::endl;
                            avgtimestamps.push_back(timestamps[i]);
                        }
                    }
                }
                catch (const std::exception& e) // if not able to separate user command, ask to re-enter
                {
                    std::cout << "advisorBot> " << "The average cannot be computed since there are not enough time periods: " << avgCommand[3] << std::endl;
                }


                std::cout << "Length: " << avgtimestamps.size() << std::endl;

                for (std::string v : avgtimestamps)
                {
                    std::cout << "Timestamp: " << v << std::endl;
                }

                for (std::string const& p : orderBook.getKnownProducts())
                {
                    if (p == avgCommand[1]) // user enter product value
                    {
                        std::cout << "advisorBot> " << "Product: " << p << std::endl; // what are the products

                        // std::cout << "TRADE: " << avgCommand[2] << std::endl << std::endl;

                        if (avgCommand[2] == "bid")
                        {
                            int bidCount = 0;
                            double sum = 0;
                            double bidAvg = 0;
                            double std = 0;
                            double stdev = 0;
                            for (std::string const& t : avgtimestamps)
                            {
                                std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask, p, t);

                                std::cout << "advisorBot> " << "Minimum bid for " << "timestamp: " << t << " is: " << OrderBook::getLowPrice(entries) << std::endl;
                                std::cout << "advisorBot> " << "Maximum bid for " << "timestamp: " << t << " is: " << OrderBook::getHighPrice(entries) << std::endl;
                                double getAvg = OrderBook::getAvg(entries);
                                std::cout << "advisorBot> " << "Average bid for " << "timestamp: " << t << " is: " << getAvg << std::endl << std::endl;
                                bidCount += 1;
                                sum += getAvg;
                                bidAvg = sum / bidCount;
                                for (i = 0; i < avgtimestamps.size(); i++)
                                {
                                    std += pow((OrderBook::getLowPrice(entries) + OrderBook::getHighPrice(entries) / 2) - bidAvg, 2);
                                }
                                stdev = sqrt(std / 10);
                            }
                            std::cout << "advisorBot> " << "The overall standard deviation for " << avgtimestamps.size() << " timestamp periods" << " is: " << stdev << std::endl << std::endl;
                        }
                        else
                        {
                            int askCount = 0;
                            double sum = 0;
                            double askAvg = 0;
                            for (std::string const& t : avgtimestamps)
                            {
                                std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::bid, p, t);

                                std::cout << "advisorBot> " << "Minimum ask for " << "timestamp: " << t << " is: " << OrderBook::getLowPrice(entries) << std::endl;
                                std::cout << "advisorBot> " << "Maximum ask for " << "timestamp: " << t << " is: " << OrderBook::getHighPrice(entries) << std::endl;
                                double getAvg = OrderBook::getAvg(entries);
                                std::cout << "advisorBot> " << "Average ask for " << "timestamp: " << t << " is: " << getAvg << std::endl << std::endl;
                                askCount += 1;
                                sum += getAvg;
                                askAvg = sum / askCount;
                            }
                            std::cout << "advisorBot> " << "The overall standard deviation for " << avgtimestamps.size() << " timestamp periods" << " is: " << askAvg << std::endl << std::endl;
                        } // end else
                    } // end if
                } // end for
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