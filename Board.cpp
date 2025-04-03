 #include "Board.h"
#include <fstream>
#include <sstream>

Board::~Board()
{
    for (auto* crawler : crawlers)
    {
        delete crawler;
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
            crawlers.push_back(new Crawler(id, x, y, static_cast<Direction>(dir), size));
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

    for (const auto* crawler : crawlers)
    {
        std::string status = crawler->isAlive() ? "Alive" : "Dead";
        Position pos = crawler->getPosition();
        std::string dirStr;

        switch (crawler->getDirection())
        {
            case Direction::North: dirStr = "North"; break;
            case Direction::East:  dirStr = "East"; break;
            case Direction::South: dirStr = "South"; break;
            case Direction::West:  dirStr = "West"; break;
            default: dirStr = "Unknown"; break;
        }

        std::cout << std::left << std::setw(5) << crawler->getId()
                  << std::setw(10) << "Crawler"
                  << std::setw(10) << ("(" + std::to_string(pos.x) + "," + std::to_string(pos.y) + ")")
                  << std::setw(6) << crawler->getSize()
                  << std::setw(12) << dirStr
                  << std::setw(6) << status << std::endl;
    }

    std::cout << "--------------------------------------------------\n";
}

void Board::findBugById(int id) const
{
    for (const auto* crawler : crawlers)
    {
        if (crawler->getId() == id)
        {
            std::cout << "\n----Bug " << id << " stats----\n";
            std::cout << "ID: " << crawler->getId() << "\n";
            std::cout << "Position: (" << crawler->getPosition().x << ", " << crawler->getPosition().y << ")\n";
            std::cout << "Size: " << crawler->getSize() << "\n";

            std::string dirStr;
            switch (crawler->getDirection())
            {
                case Direction::North: dirStr = "North"; break;
                case Direction::East:  dirStr = "East"; break;
                case Direction::South: dirStr = "South"; break;
                case Direction::West:  dirStr = "West"; break;
                default: dirStr = "Unknown"; break;
            }

            std::cout << "Direction: " << dirStr << "\n";
            std::cout << "Status: " << (crawler->isAlive() ? "Alive" : "Dead") << "\n";
            return;
        }
    }



    std::cout << "Bug " << id << " not found in the file.\n";
}


void Board::tapBoard()
{
    for (auto* crawler : crawlers)
    {
        if (crawler->isAlive())
        {
            crawler->move();
        }
    }

    for (int i = 0; i < crawlers.size(); ++i)
    {
        for (int j = i + 1; j < crawlers.size(); ++j)
        {
            if (crawlers[i]->isAlive() && crawlers[j]->isAlive() &&
                crawlers[i]->getPosition().x == crawlers[j]->getPosition().x &&
                crawlers[i]->getPosition().y == crawlers[j]->getPosition().y)
            {
                if (crawlers[i]->getSize() >= crawlers[j]->getSize())
                {
                    crawlers[i]->setSize(crawlers[i]->getSize() + crawlers[j]->getSize());
                    crawlers[j]->setAlive(false);
                    crawlers[j]->setEatenBy(crawlers[i]->getId());
                }
                else
                {
                    crawlers[j]->setSize(crawlers[j]->getSize() + crawlers[i]->getSize());
                    crawlers[i]->setAlive(false);
                    crawlers[i]->setEatenBy(crawlers[j]->getId());
                }
            }
        }
    }

    std::cout << "---Bug board has been tapped---\n";
}



void Board::displayLifeHistory() const
{
    std::cout << "\n---- Life History of All Bugs ----\n";

    for (const auto* crawler : crawlers)
    {
        std::cout << crawler->getId() << " Crawler Path: ";
        for (const auto& pos : crawler->getPath())
        {
            std::cout << "(" << pos.x << "," << pos.y << "),";
        }
        if (!crawler->isAlive())
        {
            std::cout << " Eaten by " << crawler->getEatenBy();
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

    for (const auto* crawler : crawlers)
    {
        file << crawler->getId() << " Crawler Path: ";
        for (const auto& pos : crawler->getPath())
        {
            file << "(" << pos.x << "," << pos.y << "),";
        }
        if (!crawler->isAlive())
        {
            file << " Eaten by " << crawler->getEatenBy();
        }
        file << "\n";
    }

    file.close();
    std::cout << "Life history saved to 'bugs_life_history.out'\n";
}



