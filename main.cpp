#include <iostream>
#include <ctime>
#include "Board.h"

int main() {
    srand(time(0));
    Board board;
    board.loadBugsFromFile("crawler-bugs.txt");

    std::cout << "Displaying all bugs:\n";
    board.displayAllBugs();

    return 0;
}
