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

    std::cout << "---Bug board has been tapped---\n";
}  