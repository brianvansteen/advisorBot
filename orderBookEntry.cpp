// implementation file, to implement the class / constructor

#include "orderBookEntry.h" // pulls in header file, to implement the class specified

// the constructor, needs to be first 'namespaced' OrderBookEntry, since not in the namespace class
// class::constructor function
OrderBookEntry::OrderBookEntry(double _price,
    double _amount,
    std::string _timestamp,
    std::string _product,
    OrderBookType _ordertype,
    std::string _username) // only set default in header file

    :price(_price),
     amount(_amount),
     timestamp(_timestamp),
     product(_product),
     ordertype(_ordertype),
     username(_username)
{

}

// convert string to OrderBookType enum
OrderBookType OrderBookEntry::stringToOrderBookType(std::string s)
{
    if (s == "ask")
    {
        return OrderBookType::ask;
    }
    if (s == "bid")
    {
        return OrderBookType::bid;
    }
    return OrderBookType::unknown;
}