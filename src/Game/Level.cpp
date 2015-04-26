#include "Level.h"

Level::Level(int levelNumber) :
    level(levelNumber)
{
    //ctor
}

Level::~Level()
{
    //dtor
}

void Level::addPlayerOnWall(Position pos) {
    wallPositions.push_back(pos);
}

int Level::getNumberOfPlayersOnWall()
{
    return wallPositions.size();
}

const Position* Level::getPlayerPosition(int player) const {
    if (player >= (int)wallPositions.size()) return nullptr;

    return &wallPositions.at(player);
}
