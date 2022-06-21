#pragma once

#include "OrderBookEntry.h"
#include <string>
#include <map>

class Wallet
{
public:
	Wallet();
	void insertCurrency(std::string type, double amount); // add currency to wallet
	bool removeCurrency(std::string type, double amount); // remove currency from wallet

	bool containsCurrency(std::string type, double amount); // check currency ballance

	bool canFulfillOrder(OrderBookEntry order); // check wallet if sufficient currency to fulfill order

	void processSale(OrderBookEntry& sale); // update the contents of the wallet, assuming the order was make by the wallet owner

	std::string toString(); // generate string representation of what is in the wallet

private:
	std::map<std::string, double> currencies; // currencies is variable name

};
