#ifndef CRAWLER_H
#define CRAWLER_H

#include <list>
#include <cstdlib>
#include <ctime>

struct Position {
    int x;
    int y;
    Position(int x = 0, int y = 0) : x(x), y(y) {}
    bool operator<(const Position& other) const {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }
};

enum class Direction {
    None = 0,
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
    int eatenById = -1;

public:
    Crawler(int id, int x, int y, Direction dir, int size);
    void move();
    bool isWayBlocked() const;
    bool isWayBlocked(Direction dir) const;

    int getId() const
    {
        return id;
    }
    Position getPosition() const
    {
        return position;
    }
    Direction getDirection() const
    {
        return direction;
    }
    int getSize() const {
        return size;
    }
    bool isAlive() const {
        return alive;
    }
    const std::list<Position>& getPath() const
    {
        return path;
    }
    int getEatenBy() const
    {
        return eatenById;
    }

    void setPosition(const Position& pos) {
        position = pos;
    }

    void setAlive(bool alive)
    {
        this->alive = alive;
    }
    void setSize(int newSize) {
        size = newSize;
    }
    void setDirection(Direction dir)
    {
        direction = dir;
    }

    void setEatenBy(int id)
    {
        eatenById = id;
    }

};

#endif // CRAWLER_H