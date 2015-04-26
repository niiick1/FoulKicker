#ifndef WALLPLAYER_H
#define WALLPLAYER_H

#include "Image.h"

class WallPlayer
{
    public:
        WallPlayer();
        virtual ~WallPlayer();

        Image* getImage() const { return image; }
    protected:
    private:
        Image* image;
};

#endif // WALLPLAYER_H
