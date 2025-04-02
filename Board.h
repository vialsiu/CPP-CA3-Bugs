#ifndef BOARD_H
#define BOARD_H

#include "Crawler.h"
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>

class Board {
private:
    std::vector<Crawler*> crawlers;

public:
    ~Board();
    void loadBugsFromFile(const std::string& filename);
    void displayAllBugs() const;
    void findBugById(int id) const;
    void tapBoard();
};

#endif // BOARD_H