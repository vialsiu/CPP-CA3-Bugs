#ifndef BOARD_H
#define BOARD_H

#include "Bug.h"
#include "Crawler.h"
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>

class Board {
private:
    std::vector<Bug*> bugs;
    bool gameOver = false;

public:
    ~Board();
    void loadBugsFromFile(const std::string& filename);
    void displayAllBugs() const;
    void findBugById(int id) const;
    void tapBoard();
    void displayLifeHistory() const;
    void writeLifeHistoryToFile() const;
    void displayAllCells() const;
    bool isGameOver() const { return gameOver; }
    void runSimulation();
};

#endif
