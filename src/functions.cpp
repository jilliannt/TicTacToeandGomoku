/*
* Author: Jillian Tarlowe
* Purpose: Definitions for functions used in the program
*/

#include "functions.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

int usage(const string& programName, const string& usageMsg) {
	cout << "This program is a game player!" << endl;
	cout << "Usage: " << programName << usageMsg << endl;
	return (int)returns::ARGUMENTS;
}