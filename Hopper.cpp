#include "Hopper.h"

Hopper::Hopper(int id, int x, int y, Direction dir, int size, int hopLength)
    : Bug(id, x, y, dir, size), hopLength(hopLength)
{

}

void Hopper::move() {
    if (!alive) return;

    while (true)
    {
        Position newPos = position;

        switch (direction)
        {
            case Direction::North: newPos.y -= hopLength; break;
            case Direction::East:  newPos.x += hopLength; break;
            case Direction::South: newPos.y += hopLength; break;
            case Direction::West:  newPos.x -= hopLength; break;
            default: return;
        }


        if (newPos.x < 0) newPos.x = 0;
        if (newPos.x > 9) newPos.x = 9;
        if (newPos.y < 0) newPos.y = 0;
        if (newPos.y > 9) newPos.y = 9;


        if (newPos.x == position.x && newPos.y == position.y)
        {
            Direction newDir;
            do {
                newDir = static_cast<Direction>(rand() % 4 + 1);
            } while (isWayBlocked(newDir));
            direction = newDir;
            continue;
        }

        position = newPos;
        addToPath(position);
        break;
    }
}
