#ifndef BUG_H
#define BUG_H

#include "Position.h"
#include <list>
#include <string>


enum class Direction {
    None = 0,
    North = 1,
    East,
    South,
    West
};

class Bug {
protected:
    int id;
    Position position;
    Direction direction;
    int size;
    bool alive;
    int eatenById = -1;
    std::list<Position> path;


public:
    Bug(int id, int x, int y, Direction dir, int size)
        : id(id), position(x, y), direction(dir), size(size), alive(true) {
        path.push_back(position);
    }

    virtual ~Bug() {}

    virtual void move() = 0;

    virtual std::string getType() const = 0;


    int getId() const {
        return id;
    }

    Position getPosition() const {
        return position;
    }

    Direction getDirection() const {
        return direction;
    }

    int getSize() const {
        return size;
    }

    bool isAlive() const {
        return alive;
    }

    const std::list<Position>& getPath() const {
        return path;
    }

    int getEatenBy() const {
        return eatenById;
    }

    void setPosition(const Position& pos) {
        position = pos;
    }

    void setDirection(Direction dir) {
        direction = dir;
    }

    void setSize(int newSize) {
        size = newSize;
    }

    void setAlive(bool status) {
        alive = status;
    }

    void setEatenBy(int id) {
        eatenById = id;
    }

    bool isWayBlocked() const {
        return isWayBlocked(direction);
    }

    bool isWayBlocked(Direction dir) const {
        return (dir == Direction::North && position.y == 0) ||
               (dir == Direction::East && position.x == 9) ||
               (dir == Direction::South && position.y == 9) ||
               (dir == Direction::West && position.x == 0);
    }

protected:
    void addToPath(Position newPos) {
        path.push_back(newPos);
    }
};

#endif
