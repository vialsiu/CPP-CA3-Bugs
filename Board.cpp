#include "Board.h"
#include <fstream>
#include <sstream>
#include <windows.h>
#include "Bug.h"
#include "Crawler.h"
#include "Hopper.h"
#include "KnightBug.h"


Board::~Board()
{
    for (auto* bug : bugs)
        delete bug;
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
        std::getline(ss, token, ','); id = std::stoi(token);
        std::getline(ss, token, ','); x = std::stoi(token);
        std::getline(ss, token, ','); y = std::stoi(token);
        std::getline(ss, token, ','); dir = std::stoi(token);
        std::getline(ss, token, ','); size = std::stoi(token);

        if (type == 'C')
        {
            bugs.push_back(new Crawler(id, x, y, static_cast<Direction>(dir), size));
        }
        else if (type == 'H')
        {
            std::getline(ss, token, ',');
            int hopLength = std::stoi(token);
            bugs.push_back(new Hopper(id, x, y, static_cast<Direction>(dir), size, hopLength));
        }
        else if (type == 'K')
        {
            bugs.push_back(new KnightBug(id, x, y, static_cast<Direction>(dir), size));
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

        std::string typeStr;
        if (dynamic_cast<const Hopper*>(bug))
            typeStr = "Hopper";
        else if (dynamic_cast<const Crawler*>(bug))
            typeStr = "Crawler";
        else if (dynamic_cast<const KnightBug*>(bug))
            typeStr = "KnightBug";
        else
            typeStr = "Unknown";


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
                  << std::setw(10) << typeStr
                  << std::setw(10) << ("(" + std::to_string(pos.x) + "," + std::to_string(pos.y) + ")")
                  << std::setw(6) << bug->getSize()
                  << std::setw(12) << dirStr
                  << std::setw(6) << status << "\n";
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
                if (bug->getSize() > maxSize)
                    maxSize = bug->getSize();

            std::vector<Bug*> candidates;
            for (auto* bug : bugsInCell)
                if (bug->getSize() == maxSize)
                    candidates.push_back(bug);

            Bug* winner = nullptr;

            if (candidates.size() == 1) {
                winner = candidates[0];
            } else {
                std::cout << "Tie at (" << x << "," << y << ") between Bugs: ";
                for (auto* b : candidates)
                    std::cout << b->getId() << " ";
                std::cout << "-> Random winner chosen: ";

                winner = candidates[rand() % candidates.size()];
                std::cout << "BUG " << winner->getId() << ".\n";
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

            std::cout << "Bug " << winner->getId() << " eats: ";
            bool ateSomeone = false;
            for (auto* bug : bugsInCell)
            {
                if (bug != winner)
                {
                    std::cout << bug->getId() << " ";
                    ateSomeone = true;
                }
            }
            if (ateSomeone)
            {
                int originalSize = winner->getSize();
                std::cout << "-> It suddenly grew from size " << originalSize << " to " << (originalSize + totalSizeGained) << "!\n";
            }


            winner->setSize(winner->getSize() + totalSizeGained);
        }
    }

    for (auto* bug : bugs)
        if (bug->isAlive())
            bug->move();

    std::vector<Bug*> aliveBugs;
    for (auto* bug : bugs)
        if (bug->isAlive())
            aliveBugs.push_back(bug);

    if (tapCount >= 20 && aliveBugs.size() > 1)
    {
        std::cout << "\nMAX TAPS REACHED - FORCING FINAL PVP!\n";
        for (auto* bug : aliveBugs)
            bug->setPosition({0, 0});
    }

    std::cout << "---Bug board has been tapped---\n";

    aliveBugs.clear();
    for (auto* bug : bugs)
        if (bug->isAlive())
            aliveBugs.push_back(bug);

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
        std::string typeStr = dynamic_cast<const Hopper*>(bug) ? "Hopper" : "Crawler";
        std::cout << bug->getId() << " " << typeStr << " Path: ";
        for (const auto& pos : bug->getPath())
            std::cout << "(" << pos.x << "," << pos.y << "),";

        if (!bug->isAlive())
            std::cout << " Eaten by " << bug->getEatenBy();

        std::cout << "\n";
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
        std::string typeStr = dynamic_cast<const Hopper*>(bug) ? "Hopper" : "Crawler";
        file << bug->getId() << " " << typeStr << " Path: ";
        for (const auto& pos : bug->getPath())
            file << "(" << pos.x << "," << pos.y << "),";

        if (!bug->isAlive())
            file << " Eaten by " << bug->getEatenBy();

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

            std::vector<std::string> occupants;
            for (const auto* bug : bugs)
            {
                if (bug->isAlive() &&
                    bug->getPosition().x == x &&
                    bug->getPosition().y == y)
                {
                    std::string typeStr = dynamic_cast<const Hopper*>(bug) ? "Hopper" : "Crawler";
                    occupants.push_back(typeStr + " " + std::to_string(bug->getId()));
                }
            }

            if (occupants.empty())
            {
                std::cout << "empty\n";
            }
            else
            {
                for (size_t i = 0; i < occupants.size(); ++i)
                {
                    std::cout << occupants[i];
                    if (i < occupants.size() - 1)
                        std::cout << ", ";
                }
                std::cout << "\n";
            }
        }
    }
}

void Board::runSimulation()
{
    int tapCount = 0;
    while (!gameOver)
    {
        std::cout << "\n[Simulation Tap #" << ++tapCount << "]\n";

        int aliveCount = 0;
        for (const auto* bug : bugs)
            if (bug->isAlive()) aliveCount++;

        std::cout << "Alive Bugs: " << aliveCount << "\n";

        tapBoard();
        Sleep(100);
    }

    std::cout << "\nSimulation finished.\n";
}
