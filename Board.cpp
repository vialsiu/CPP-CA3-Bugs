#include "Board.h"
#include <fstream>
#include <sstream>
#include <windows.h>

Board::~Board()
{
    for (auto* bug : bugs)
    {
        delete bug;
    }
}

void Board::loadBugsFromFile(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file)
    {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string token;
        char type;
        int id, x, y, dir, size;

        std::getline(ss, token, ',');
        type = token[0];
        std::getline(ss, token, ',');
        id = std::stoi(token);
        std::getline(ss, token, ',');
        x = std::stoi(token);
        std::getline(ss, token, ',');
        y = std::stoi(token);
        std::getline(ss, token, ',');
        dir = std::stoi(token);
        std::getline(ss, token, ',');
        size = std::stoi(token);

        if (type == 'C' && dir >= 1 && dir <= 4)
        {
            bugs.push_back(new Crawler(id, x, y, static_cast<Direction>(dir), size));
        }
    }

    file.close();
}

void Board::displayAllBugs() const
{
    std::cout << std::left << std::setw(5) << "ID"
              << std::setw(10) << "Type"
              << std::setw(10) << "Position"
              << std::setw(6) << "Size"
              << std::setw(12) << "Direction"
              << std::setw(6) << "Status" << std::endl;

    std::cout << "--------------------------------------------------\n";

    for (const auto* bug : bugs)
    {
        std::string status = bug->isAlive() ? "Alive" : "Dead";
        Position pos = bug->getPosition();
        std::string dirStr;

        switch (bug->getDirection())
        {
            case Direction::North: dirStr = "North"; break;
            case Direction::East:  dirStr = "East"; break;
            case Direction::South: dirStr = "South"; break;
            case Direction::West:  dirStr = "West"; break;
            default: dirStr = "Unknown"; break;
        }

        std::cout << std::left << std::setw(5) << bug->getId()
                  << std::setw(10) << "Crawler"
                  << std::setw(10) << ("(" + std::to_string(pos.x) + "," + std::to_string(pos.y) + ")")
                  << std::setw(6) << bug->getSize()
                  << std::setw(12) << dirStr
                  << std::setw(6) << status << std::endl;
    }

    std::cout << "--------------------------------------------------\n";
}

void Board::findBugById(int id) const
{
    for (const auto* bug : bugs)
    {
        if (bug->getId() == id)
        {
            std::cout << "\n----Bug " << id << " stats----\n";
            std::cout << "ID: " << bug->getId() << "\n";
            std::cout << "Position: (" << bug->getPosition().x << ", " << bug->getPosition().y << ")\n";
            std::cout << "Size: " << bug->getSize() << "\n";

            std::string dirStr;
            switch (bug->getDirection())
            {
                case Direction::North: dirStr = "North"; break;
                case Direction::East:  dirStr = "East"; break;
                case Direction::South: dirStr = "South"; break;
                case Direction::West:  dirStr = "West"; break;
                default: dirStr = "Unknown"; break;
            }

            std::cout << "Direction: " << dirStr << "\n";
            std::cout << "Status: " << (bug->isAlive() ? "Alive" : "Dead") << "\n";
            return;
        }
    }

    std::cout << "Bug " << id << " not found in the file.\n";
}

void Board::tapBoard()
{
    static int tapCount = 0;
    tapCount++;
    std::cout << "\nTap #" << tapCount << "\n";

    for (auto* bug : bugs)
    {
        if (bug->isAlive())
        {
            bug->move();
        }
    }

    std::vector<Bug*> aliveBugs;
    for (auto* bug : bugs)
    {
        if (bug->isAlive())
        {
            aliveBugs.push_back(bug);
        }
    }

    if (tapCount >= 20 && aliveBugs.size() > 1)
    {
        std::cout << "\nMAX TAPS REACHED - FORCING FINAL PVP!\n";
        for (auto* bug : aliveBugs)
        {
            bug->setPosition({0, 0});
        }
    }

    for (int x = 0; x < 10; ++x)
    {
        for (int y = 0; y < 10; ++y)
        {
            std::vector<Bug*> bugsInCell;
            for (auto* bug : bugs)
            {
                if (bug->isAlive() &&
                    bug->getPosition().x == x &&
                    bug->getPosition().y == y)
                {
                    bugsInCell.push_back(bug);
                }
            }

            if (bugsInCell.size() <= 1) continue;

            int maxSize = 0;
            for (auto* bug : bugsInCell)
            {
                if (bug->getSize() > maxSize)
                    maxSize = bug->getSize();
            }

            std::vector<Bug*> candidates;
            for (auto* bug : bugsInCell)
            {
                if (bug->getSize() == maxSize)
                    candidates.push_back(bug);
            }

            Bug* winner;
            if (candidates.size() == 1)
            {
                winner = candidates[0];
            }
            else
            {
                int randomIndex = std::rand() % static_cast<int>(candidates.size());
                winner = candidates[randomIndex];
            }

            int totalSizeGained = 0;
            for (auto* bug : bugsInCell)
            {
                if (bug != winner)
                {
                    bug->setAlive(false);
                    bug->setEatenBy(winner->getId());
                    totalSizeGained += bug->getSize();
                }
            }

            winner->setSize(winner->getSize() + totalSizeGained);
        }
    }

    std::cout << "---Bug board has been tapped---\n";

    aliveBugs.clear();
    for (auto* bug : bugs)
    {
        if (bug->isAlive())
            aliveBugs.push_back(bug);
    }

    if (aliveBugs.size() == 1)
    {
        std::cout << "\nLAST BUG STANDING: Bug " << aliveBugs[0]->getId() << "\n";
        writeLifeHistoryToFile();
        gameOver = true;
    }
}

void Board::displayLifeHistory() const
{
    std::cout << "\n---- Life History of All Bugs ----\n";

    for (const auto* bug : bugs)
    {
        std::cout << bug->getId() << " Crawler Path: ";
        for (const auto& pos : bug->getPath())
        {
            std::cout << "(" << pos.x << "," << pos.y << "),";
        }
        if (!bug->isAlive())
        {
            std::cout << " Eaten by " << bug->getEatenBy();
        }
        std::cout << std::endl;
    }
}

void Board::writeLifeHistoryToFile() const
{
    std::ofstream file("bugs_life_history.out");
    if (!file)
    {
        std::cout << "Error: Cannot write to file.\n";
        return;
    }

    for (const auto* bug : bugs)
    {
        file << bug->getId() << " Crawler Path: ";
        for (const auto& pos : bug->getPath())
        {
            file << "(" << pos.x << "," << pos.y << "),";
        }
        if (!bug->isAlive())
        {
            file << " Eaten by " << bug->getEatenBy();
        }
        file << "\n";
    }

    file.close();
    std::cout << "LIFE HISTORY -------> 'bugs_life_history.out'\n";
}

void Board::displayAllCells() const
{
    std::cout << "\n---- Board Cell Occupancy ----\n";

    for (int y = 0; y < 10; ++y)
    {
        for (int x = 0; x < 10; ++x)
        {
            std::cout << "(" << x << "," << y << "): ";

            bool found = false;
            for (const auto* bug : bugs)
            {
                if (bug->isAlive() &&
                    bug->getPosition().x == x &&
                    bug->getPosition().y == y)
                {
                    if (found) std::cout << ", ";
                    std::cout << "Bug " << bug->getId();
                    found = true;
                }
            }

            if (!found)
                std::cout << "empty";

            std::cout << "\n";
        }
    }
}

void Board::runSimulation()
{
    int tapCount = 0;

    while (!gameOver)
    {
        tapCount++;
        std::cout << "\n[Simulation Tap #" << tapCount << "]\n";

        int aliveCount = 0;
        for (const auto* bug : bugs)
        {
            if (bug->isAlive()) aliveCount++;
        }

        std::cout << "Alive Bugs: " << aliveCount << "\n";

        tapBoard();
        Sleep(100);
    }

    std::cout << "\nSimulation finished.\n";
}
