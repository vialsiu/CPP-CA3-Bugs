#include <iostream>
#include <ctime>
#include "Board.h"

int main() {
    srand(time(0));
    Board board;
    board.loadBugsFromFile("crawler-bugs.txt");
    return 0;
}
