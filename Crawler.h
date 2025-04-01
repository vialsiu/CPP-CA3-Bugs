#ifndef CRAWLER_H
#define CRAWLER_H

#include <list>

struct Position {
    int x;
    int y;
    Position(int x = 0, int y = 0) : x(x), y(y) {}
};

enum class Direction {
    North = 1,
    East = 2,
    South = 3,
    West = 4
};

class Crawler {
private:
    int id;
    Position position;
    Direction direction;
    int size;
    bool alive;
    std::list<Position> path;

public:
    Crawler(int id, int x, int y, Direction dir, int size);
    void move();
    bool isWayBlocked() const;
};

#endif