// implementation

# #include "orderBookEntry.h"

OrderBookEntry::OrderBookEntry(double _price,
    double _amount,
    std::string _timestamp,
    std::string _product,
    OrderBookType _ordertype)

:price(_price),
 amount(_amount),
 timestamp(_timestamp),
 product(_product),
 ordertype{ _ordertype }
{

}