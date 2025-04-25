#include "KnightBug.h"
#include <cstdlib>
#include <ctime>

KnightBug::KnightBug(int id, int x, int y, Direction dir, int size)
    : Bug(id, x, y, dir, size)
{
}

void KnightBug::move() {
    if (!alive) return;

    // The moves that a knight makes in chess that are possible on our bug board in my opinion
    static const std::vector<std::pair<int, int>> knightMoves = {
        {2, 1}, {1, 2},
        {-1, 2}, {-2, 1},
        {-2, -1}, {-1, -2},
        {1, -2}, {2, -1}
    };

    std::vector<Position> validMoves;

    for (const auto& move : knightMoves)
    {
        int newX = position.x + move.first;
        int newY = position.y + move.second;

        if (newX >= 0 && newX < 10 && newY >= 0 && newY < 10)
        {
            validMoves.push_back(Position(newX, newY));
        }
    }

    if (!validMoves.empty())
    {
        int idx = rand() % validMoves.size();
        position = validMoves[idx];
        addToPath(position);
    }
    // or else no move because it got stuck on the edge
}
