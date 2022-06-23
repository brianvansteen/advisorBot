// implementation file for csvReader

#include "csvReader.h" // also includes string and vector from .h
#include <iostream>
#include <fstream>

CSVReader::CSVReader() // constructor
{

}


std::vector<OrderBookEntry> CSVReader::readCSV(std::string csvFilename) // function implementation
{
	std::vector<OrderBookEntry> entries; // return vector of order book entries
	std::ifstream csvFile{ "20200601.csv" }; // instantiates ifstream object; default behaviour is to open file for reading
	std::string line;
	if (csvFile.is_open())
	{
		while (std::getline(csvFile, line))
		{
			try {
				OrderBookEntry obe = stringsToOBE(tokenise(line, ',')); // stringToOBE and tokenise function defined below
				entries.push_back(obe); // obe defined below
			}
			catch (const std::exception& e)
			{
				std::cout << "Bad data...." << std::endl << std::endl;
			}
		} // end of while
	}
	std::cout << "CSVReader:readCSV read " << entries.size() << " entries" << std::endl << std::endl;
	return entries;
}

std::vector<std::string> CSVReader::tokenise(std::string csvLine, char separator) // to tokenise the string; tokenise is a static function in CSVReader class
{
	std::vector<std::string> tokens;

	signed int start, end;
	std::string token;

	start = csvLine.find_first_not_of(separator, 0);

	do {
		end = csvLine.find_first_of(separator, start);
		if (start == csvLine.length()) break;
		if (end >= 0) token = csvLine.substr(start, end - start);
		else token = csvLine.substr(start, csvLine.length() - start);
		tokens.push_back(token);
		start = end + 1;
	} while (end > 0);

	return tokens;
}

// from vector of strings line-by-line from call to tokenise, convert string to appropriate data to send to OBE constructor
OrderBookEntry CSVReader::stringsToOBE(std::vector<std::string> tokens) // return single OBE
{
	double price, amount;

	if (tokens.size() != 5) // need five entries to create order book entry
	{
		std::cout << "Bad line!" << std::endl;
		throw std::exception{};
	}
	try {
		price = std::stod(tokens[3]); // stod is a static function; stateless; called once then removed
		amount = std::stod(tokens[4]);
	}
	catch (const std::exception& e) // always use const for exceptions
	{
		std::cout << "CSVReader::stringsToOBE Bad float! " << tokens[3] << std::endl;
		std::cout << "CSVReader::stringsToOBE Bad float! " << tokens[4] << std::endl;
		throw;
	}

	// from vector of strings from call to tokenise, convert string to appropriate data to send to OBE constructor
	OrderBookEntry obe{price,
						amount,
						tokens[0], // timestamp
						tokens[1], // product
						OrderBookEntry::stringToOrderBookType(tokens[2])}; // call function to take output from tokenise string an convert to order book entry
	return obe;
}

OrderBookEntry CSVReader::stringsToOBE(std::string priceString,
	std::string amountString,
	std::string timestamp,
	std::string product,
	OrderBookType orderType)
{
	double price, amount;
	try {
		price = std::stod(priceString); // stod is a static function; stateless; called once then removed
		amount = std::stod(amountString);
	}
	catch (const std::exception& e) // always use const for exceptions
	{
		std::cout << "CSVReader::stringsToOBE Bad float! " << priceString << std::endl;
		std::cout << "CSVReader::stringsToOBE Bad float! " << amountString << std::endl;
		throw;
	}

	// from vector of strings from call to tokenise, convert string to appropriate data to send to OBE constructor
	OrderBookEntry obe{ price,
						amount,
						timestamp, // timestamp
						product, // product
						orderType };
	return obe;
}
