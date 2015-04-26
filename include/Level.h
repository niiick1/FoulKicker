#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include "Position.h"

class Level
{
    public:
        Level(int levelNumber);
        virtual ~Level();

        void addPlayerOnWall(Position pos);
        int getNumberOfPlayersOnWall();
        const Position* getPlayerPosition(int player) const;

        void setLevel(int l) { level = l; }
        int getLevel() { return level; }

        void setBallPosition(Position ballPos) { ballPosition = ballPos; }
        const Position& getBallPosition() const { return ballPosition; }
    protected:
    private:
        int level;
        Position ballPosition;
        std::vector<Position> wallPositions;
};

#endif // LEVEL_H
