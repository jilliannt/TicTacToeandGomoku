/**
 * Main.cpp
 * Author: Jillian Tarlowe
*/

#include <iostream>
#include "functions.h"
#include "game.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <memory>


using namespace std;

int main(int argc, char* argv[]) {
    shared_ptr<GameBase> create (GameBase::objectConstruct(argc, argv));

    if (create == 0) { //makes sure we pass in the correct command line arguments
        string usageMsg = " <TicTacToe OR Gomoku>";
        return usage(argv[(int)indices::PROGRAM_NAME], usageMsg);
    }

    int returnv;
    try {
        returnv = create->play();
    }
    catch (bad_alloc const&) {
        return (int)returns::BAD_ALLOC;
    }
    return returnv;
}

