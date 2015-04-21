#include "Sprite.h"
#include "RGBAColor.h"

Sprite::Sprite() :
    sprite(nullptr),
    frameWidth(0), frameHeight(0),
    offsetX(0), offsetY(0),
    frameCount(0), currentFrame(0)
{}

Sprite::Sprite(const Sprite& s) {
    *this = s;
}

Sprite::~Sprite()
{
    delete this->sprite;
}

Sprite& Sprite::operator=(const Sprite& s) {
    this->currentFrame = s.currentFrame;
    this->frameCount = s.frameCount;
    this->frameHeight = s.frameHeight;
    this->frameWidth = s.frameWidth;
    this->offsetX = s.offsetX;
    this->offsetY = s.offsetY;
    this->sprite = new Image(*s.sprite);

    return *this;
}

void Sprite::nextFrame() {
    if (this->currentFrame >= this->frameCount - 1) {
        this->currentFrame = 0;
    } else {
        this->currentFrame++;
    }
}


