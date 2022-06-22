// cryptoTrading.cpp : This file contains the 'main' function. Program execution begins and ends there.
// all other functions specified and implemented in the MerkelMain files (.h and .cpp)


#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

#include "orderBookEntry.h"
#include "MerkelMain.h"
#include "csvReader.h"


int main()
{
    // public functions
    MerkelMain app{}; // call the constructor function, .h file
    app.init(); // call the init function; with comment from .h file

    return 0;
}





