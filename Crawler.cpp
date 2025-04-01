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
}

bool Crawler::isWayBlocked() const {
    return false;
}
