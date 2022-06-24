#include "OrderBook.h"
#include "csvReader.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

OrderBook::OrderBook(std::string filename) // constructor reading csv data file
{
	orders = CSVReader::readCSV(filename); // vector of order book entries
}


std::vector<std::string> OrderBook::getKnownProducts() // return vector of all known products in the dataset
{
	std::vector<std::string> products; // define vector

	std::map<std::string, bool> prodMap; // dictionary 'prodMap'
 
	for (OrderBookEntry& e : orders) // from orders above, using OrderBookEntry class
	{
		prodMap[e.product] = true; // key is product from OBE class; value is 'true'
	}

	// now flatten the map to a vector of strings
	for (auto const& e : prodMap) // variable type is 'auto'
	{
		products.push_back(e.first); // first is the key, i.e. product
	}

	return products; // function called from MerkelMain 'exchangestats' menu #2
}


std::vector<std::string> OrderBook::getTimestamps() // return vector of all known products in the dataset
{
	std::vector<std::string> timestamps; // define vector

	std::map<std::string, bool> timeMap; // dictionary 'prodMap'

	for (OrderBookEntry& e : orders) // from orders above, using OrderBookEntry class
	{
		timeMap[e.timestamp] = true; // key is timestamp from OBE class; value is 'true'
		
	}

	// now flatten the map to a vector of strings
	for (auto const& e : timeMap) // variable type is 'auto'
	{
		timestamps.push_back(e.first); // first is the key, i.e. product
	}

	return timestamps; // function called from MerkelMain 'exchangestats' menu #2
}

// return vector of Orders according to the sent filters of type (bid or ask), product and timestamp (i.e. 'currentTime)
std::vector<OrderBookEntry> OrderBook::getOrders(OrderBookType type, std::string product, std::string timestamp)
{
	std::vector<OrderBookEntry> orders_sub;

	for (OrderBookEntry& e : orders)
	{
		if (e.ordertype == type && // bid or ask
			e.product == product && // for the product available
			e.timestamp == timestamp) // for specific time stamp
		{
			orders_sub.push_back(e);
		}
	}

	return orders_sub; // function called from MerkelMain 'exchangestats' menu #2
}

double OrderBook::getHighPrice(std::vector<OrderBookEntry>& orders)
{
	double max = orders[0].price;
	for (OrderBookEntry& e : orders)
	{
		if (e.price > max)max = e.price;
	}
	return max;
};


double OrderBook::getLowPrice(std::vector<OrderBookEntry>& orders)
{
	double min = orders[0].price;
	for (OrderBookEntry& e : orders)
	{
		if (e.price < min)min = e.price;
	}
	return min;
}


double OrderBook::getAvg(std::vector<OrderBookEntry>& orders)
{
	double min = orders[0].price;
	int count = 0;
	double sum = 0;
	double avg = 0;
	for (OrderBookEntry& e : orders)
	{
		count += 1;
		sum += e.price;
	}
	avg = sum / count;
	std::cout << "advisorBot> " << "Count of orders: " << count << " Sum of orders: " << sum << std::endl;
	return avg;
}


double OrderBook::getPredict(std::vector<OrderBookEntry>& orders)
{
	double min = orders[0].price;
	int count = 0;
	double sum = 0;
	double avg = 0;
	for (OrderBookEntry& e : orders)
	{
		count += 1;
		sum += e.price;
	}
	avg = sum / count;
	std::cout << "advisorBot> " << "Count of orders: " << count << " Sum of orders: " << sum << std::endl;
	return avg;
}


std::string OrderBook::getEarliestTime()
{
	return orders[0].timestamp; // timestamp of first order
}

std::string OrderBook::getNextTime(std::string timestamp)
{
	std::string next_timestamp = "";
	for (OrderBookEntry& e : orders)
	{
		if (e.timestamp > timestamp)
		{
			next_timestamp = e.timestamp;
				break;
		}
	}
	if (next_timestamp == "")
	{
		next_timestamp = orders[0].timestamp; // timestamp of first order
	}
	return next_timestamp; // used for 'currentTime'
}

void OrderBook::insertOrder(OrderBookEntry& order)
{
	orders.push_back(order); // add order to end of vector
	std::sort(orders.begin(), orders.end(), OrderBookEntry::compareByTimestamp); // after adding to the end, re-sort whole vector
}

std::vector<OrderBookEntry> OrderBook::matchAsksToBids(std::string product, std::string timestamp) // match specific product in specific timestamp
{
	std::vector<OrderBookEntry> asks = getOrders(OrderBookType::ask, product, timestamp); // get vector of asks from orders
	std::vector<OrderBookEntry> bids = getOrders(OrderBookType::bid, product, timestamp); // get vector of bids from orders

	std::vector<OrderBookEntry> sales;

	std::sort(asks.begin(), asks.end(), OrderBookEntry::compareByPriceA); // sort asks from lowest
	std::sort(bids.begin(), bids.end(), OrderBookEntry::compareByPriceD); // sort bids from highest

	for (OrderBookEntry& ask : asks) // iterate over asks first, from lowest
	{
		for (OrderBookEntry& bid : bids) // iterate over bids second, from highest
		{
			if (bid.price >= ask.price)
			{
				OrderBookEntry sale{ ask.price, 0, timestamp, product, OrderBookType::asksale };

				if (bid.username == "simuser")
				{
					sale.username = "simuser";
					sale.ordertype = OrderBookType::bidsale;
				}
				if (ask.username == "simeuser")
				{
					sale.username = "simuser";
					sale.ordertype = OrderBookType::asksale;
				}
				
					if (bid.amount == ask.amount)
					{
						sale.amount = ask.amount;
						sales.push_back(sale);
						bid.amount = 0; // bid order completely satisfied
						break; // move to next bid and ask
					}
					if (bid.amount > ask.amount)
					{
						sale.amount = ask.amount; // only the amout of the ask offer
						sales.push_back(sale);
						bid.amount = bid.amount - ask.amount;
						break; // move to next ask, attempt to fill bid
					}
					if (bid.amount < ask.amount && bid.amount > 0)
					{
						sale.amount = bid.amount;
						sales.push_back(sale);
						ask.amount = ask.amount - bid.amount;
						bid.amount = 0;
						continue; // go to next bid, attempt to fill ask
					}
			}
		}
	}
	return sales;
}