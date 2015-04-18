#include "Sprite.h"
#include "RGBAColor.h"

Sprite::Sprite()
{}

Sprite::~Sprite()
{
    delete this->sprite;
}

void Sprite::nextFrame() {
    if (this->currentFrame >= this->frameCount - 1) {
        this->currentFrame = 0;
    } else {
        this->currentFrame++;
    }
}


