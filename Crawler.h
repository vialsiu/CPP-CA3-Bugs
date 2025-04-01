#ifndef CRAWLER_H
#define CRAWLER_H

#include <list>

struct Position {
    int x;
    int y;
};

enum class Direction {
    North = 1,
    East,
    South,
    West };

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