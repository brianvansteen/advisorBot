// header file is the specification file; not how class works, only how to use it

#pragma once // if below class included once already, do not include again
#include<string>

enum class OrderBookType { bid, ask, unknown, asksale, bidsale };

class OrderBookEntry // namespace of the class OrderBookEntry
{
public:
    // specify constructor since already in the class
    OrderBookEntry(double _price,
        double _amount,
        std::string _timestamp,
        std::string _product,
        OrderBookType _ordertype,
        std::string _username = "dataset"); // default for all OBE objects, when no username

    // static - non-changing
    static OrderBookType stringToOrderBookType(std::string s); // function converts from string to OrderBookType enum, string as argument

    // to ensure the first timestamp is earlier than the second timestamp
    static bool compareByTimestamp(OrderBookEntry& e1, OrderBookEntry& e2)
    {
        return e1.timestamp < e2.timestamp;
    }

    static bool compareByPriceA(OrderBookEntry& e1, OrderBookEntry& e2)
    {
        return e1.price < e2.price;
    }

    static bool compareByPriceD(OrderBookEntry& e1, OrderBookEntry& e2)
    {
        return e1.price > e2.price;
    }

    double price;
    double amount;
    std::string timestamp;
    std::string product;
    OrderBookType ordertype;

    std::string username;
};