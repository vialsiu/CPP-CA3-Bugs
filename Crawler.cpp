#include "Crawler.h"

Crawler::Crawler(int id, int x, int y, Direction dir, int size) {
    this->id = id;
    position.x = x;
    position.y = y;
    direction = dir;
    this->size = size;
    alive = true;
    path.push_back(position);
}

void Crawler::move() {
    if (!alive) return;

    Position newCoord = position;
    switch(direction) {
        case Direction::North: newCoord.y--; break;
        case Direction::East:  newCoord.x++; break;
        case Direction::South: newCoord.y++; break;
        case Direction::West:  newCoord.x--; break;
    }

    if (newCoord.x >= 0 &&
        newCoord.x < 10 &&
        newCoord.y >= 0 &&
        newCoord.y < 10)
        {

        position = newCoord;
        path.push_back(position);
        }
        else {
            do {
                direction = static_cast<Direction>(
                    (static_cast<int>(direction) % 4 + 1)
                );
            }
            while(isWayBlocked());
            move();
        }
}

bool Crawler::isWayBlocked() const {
    return (direction == Direction::North &&
            position.y == 0) ||
           (direction == Direction::East  &&
            position.x == 9) ||
           (direction == Direction::South &&
            position.y == 9) ||
           (direction == Direction::West  &&
            position.x == 0);
}