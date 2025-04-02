#include "Crawler.h"

Crawler::Crawler(int id, int x, int y, Direction dir, int size) : id(id), position(x, y), direction(dir), size(size), alive(true)
{
    path.push_back(position);
}

void Crawler::move()
{
    if (!alive) return;

    while (true)
        {
        Position newPos = position;
        switch (direction)
            {
            case Direction::North: newPos.y--; break;
            case Direction::East:  newPos.x++; break;
            case Direction::South: newPos.y++; break;
            case Direction::West:  newPos.x--; break;
        }

        if (newPos.x >= 0 && newPos.x < 10 && newPos.y >= 0 && newPos.y < 10)
            {
            position = newPos;
            path.push_back(position);
            break;
        }
        else
            {
            Direction newDir;
            do {
                newDir = static_cast<Direction>(rand() % 4 + 1);
            }
            while (isWayBlocked(newDir));
            direction = newDir;
        }
    }
}

bool Crawler::isWayBlocked() const
{
    return isWayBlocked(direction);
}

bool Crawler::isWayBlocked(Direction dir) const
{
    return (dir == Direction::North && position.y == 0) ||
           (dir == Direction::East  && position.x == 9) ||
           (dir == Direction::South && position.y == 9) ||
           (dir == Direction::West  && position.x == 0);
}