#ifndef CRAWLER_H
#define CRAWLER_H

#include "Bug.h"
#include <cstdlib>
#include <ctime>

class Crawler : public Bug {
public:
    Crawler(int id, int x, int y, Direction dir, int size);
    void move() override;
};

#endif // CRAWLER_H
