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
    bool finalBattle = false;
    int finalTapCounter = 3;
    int superBugId = 9999;

public:
    ~Board();
    void loadBugsFromFile(const std::string& filename);
    void displayAllBugs() const;
    void findBugById(int id) const;
    void tapBoard();
    void tapBoard(bool checkGameOver);
    void displayLifeHistory() const;
    void writeLifeHistoryToFile() const;
    void displayAllCells() const;
    bool isGameOver() const { return gameOver; }
    void runSimulation();
    void setSuperBugId(int id) { superBugId = id; }
    void addBug(Bug* bug) { bugs.push_back(bug); }
    const std::vector<Bug*>& getBugs() const { return bugs; }
};

#endif
