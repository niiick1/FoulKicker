#include "WallPlayer.h"
#include "PTMReader.h"

WallPlayer::WallPlayer()
{
   PTMReader ptm;
   image = ptm.readFile("resources/img/wall-1.ptm");
}

WallPlayer::~WallPlayer()
{
    //dtor
}
