#include "Crawler.h"

Crawler::Crawler(int id, int x, int y, Direction dir, int size)
    : Bug(id, x, y, dir, size) {

}

void Crawler::move() {
    if (!alive) return;

    while (true) {
        Position newPos = position;
        switch (direction)
        {
            case Direction::North: newPos.y--; break;
            case Direction::East:  newPos.x++; break;
            case Direction::South: newPos.y++; break;
            case Direction::West:  newPos.x--; break;
            default: return;
        }

        if (newPos.x >= 0 && newPos.x < 10 && newPos.y >= 0 && newPos.y < 10)
        {
            position = newPos;
            addToPath(position);
            break;
        }
        else {
            Direction newDir;
            do {
                newDir = static_cast<Direction>(rand() % 4 + 1);
            } while (isWayBlocked(newDir));
            direction = newDir;
        }
    }
}
