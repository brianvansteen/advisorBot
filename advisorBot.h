#pragma once

#include "OrderBookEntry.h"
#include <string>
#include <map>
#include <vector>
#include <algorithm>

enum class advisorMode { userMode, botMode };

class advisorBot
{
public:
	advisorBot();

	static double getMin(std::vector<OrderBookEntry>& orders);
	static double getMax(std::vector<OrderBookEntry>& orders);




private:

};

