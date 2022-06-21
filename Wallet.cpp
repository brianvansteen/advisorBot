#include "Wallet.h"
#include "csvReader.h"
#include <iostream>

Wallet::Wallet()
{

}
	void Wallet::insertCurrency(std::string type, double amount) // add currency to wallet
	{
		double balance;
		if (amount < 0)
		{
			throw std::exception{};
		}
		if (currencies.count(type) == 0) // currencies is a map
		{
			balance = 0;
		}
		else
		{
			balance = currencies[type];
		}
		balance += amount;
		currencies[type] = balance; // currencies is a map
	}

	bool Wallet::removeCurrency(std::string type, double amount)
	{
		if (amount < 0) // cannot remove negative amount
		{
			return false;
			// throw std::exception{};
		}
		if (currencies.count(type) == 0) // currencies is a map
		{
			return false; // that currency does not exist in wallet
			// balance = 0;
		}
		else // there is a balance of the currency
		{
			if (containsCurrency(type, amount))
			{
				currencies[type] -= amount;
				return true;
			}
			else
			{
				return false; // currency exist but not enough for the remove amount
			}
		}
	}

	bool Wallet::containsCurrency(std::string type, double amount) // check currency ballance
	{
		if (currencies.count(type) == 0) // currencies is a map
			return false;
		else
			return currencies[type] >= amount; // currencies is a map
	}

	std::string Wallet::toString() // generate string representation of what is in the wallet
	{
		std::string s;
		for (std::pair<std::string, double> pair : currencies) // currencies is a map
		{
			std::string currency = pair.first;
			double amount = pair.second;
			s += currency + " : " + std::to_string(amount) + "\n";
		}
		return s;
	}

	bool Wallet::canFulfillOrder(OrderBookEntry order)
	{
		std::vector<std::string> coins = CSVReader::tokenise(order.product, '/');

		if (order.ordertype == OrderBookType::ask) // check if enough currency to complete the ask / sell
		{
			double amount = order.amount;
			std::string currency = coins[0];
			std::cout << "Wallet::canFulfillOrder " << currency << " : " <<amount << std::endl;
			return containsCurrency(currency, amount);
		}

		if (order.ordertype == OrderBookType::bid)
		{
			double amount = order.amount * order.price;
			std::string currency = coins[1];
			std::cout << "Wallet::canFulfillOrder " << currency << " : " << amount << std::endl;
			return containsCurrency(currency, amount);
		}

		return false;
	}

	void Wallet::processSale(OrderBookEntry& sale)
	{
		std::vector<std::string> coins = CSVReader::tokenise(sale.product, '/');

		if (sale.ordertype == OrderBookType::asksale) // check if enough currency to complete the ask / sell
		{
			double outgoingAmount = sale.amount;
			std::string outgoingCurrency = coins[0];
			double incomingAmount = sale.amount * sale.price;
			std::string incomingCurrency = coins[1];

			currencies[incomingCurrency] += incomingAmount;
			currencies[outgoingCurrency] -= outgoingAmount;
		}

		if (sale.ordertype == OrderBookType::bidsale)
		{
			double incomingAmount = sale.amount;
			std::string incomingCurrency = coins[0];
			double outgoingAmount = sale.amount * sale.price;
			std::string outgoingCurrency = coins[1];

			currencies[incomingCurrency] += incomingAmount;
			currencies[outgoingCurrency] -= outgoingAmount;
		}
	}