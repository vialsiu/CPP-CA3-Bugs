#include <iostream>
#include "Board.h"

int main() {
    Board board;
    board.loadBugsFromFile("crawler-bugs.txt");
    return 0;
}