#ifndef KNIGHTBUG_H
#define KNIGHTBUG_H

#include "Bug.h"
#include <vector>

class KnightBug : public Bug {
public:
    KnightBug(int id, int x, int y, Direction dir, int size);
    void move() override;

    std::string getType() const override { return "KnightBug"; }

};

#endif // KNIGHTBUG_H
