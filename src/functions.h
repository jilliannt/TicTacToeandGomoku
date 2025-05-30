/*
* Author: Jillian Tarlowe
* Purpose: This file declares functions for the program
*/
#include <vector>
#include <string>
using namespace std;

//enumerates expected index values
enum struct indices { PROGRAM_NAME, INPUT_NAME };

//enumerates possible return values for success or failures
enum struct returns { SUCCESS, WINNER, ARGUMENTS, NO_MOVES, INVALID_INPUT, QUIT, DRAW, COMMAND_LINE, XTURN, YTURN, BAD_ALLOC };

//prints out usage information in the case that the amount of command line arguments does not match the expected amount
int usage(const string& programName, const string& usageMsg);
