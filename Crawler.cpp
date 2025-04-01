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
        case Direction::North:
            position.y--;
        break;
        case Direction::East:
            position.x++;
        break;
        case Direction::South:
            position.y++;
        break;
        case Direction::West:
            position.x--;
        break;
    }
    if (newCoord.x >= 0 &&
        newCoord.x < 10 &&
        newCoord.y >= 0 &&
        newCoord.y < 10)
        {
        position = newCoord;
    }

    path.push_back(position);
}

bool Crawler::isWayBlocked() const {
    return false;
}
