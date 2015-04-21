#ifndef SPRITE_H
#define SPRITE_H

#include "Image.h"

class Sprite
{
    public:
        Sprite();
        Sprite(const Sprite& s);
        Sprite& operator=(const Sprite& s);
        virtual ~Sprite();

        void nextFrame();

        Image* getSprite() { return this->sprite; }
        void setSprite(Image* sprite) { this->sprite = sprite; }
        int getFrameWidth() { return this->frameWidth; }
        void setFrameWidth(int w) { this->frameWidth = w; }
        int getFrameHeight() { return this->frameHeight; }
        void setFrameHeight(int h) { this->frameHeight = h; }
        int getOffsetX() { return this->offsetX; }
        void setOffsetX(int x) { this->offsetX = x; }
        int getOffsetY() { return this->offsetY; }
        void setOffsetY(int y) { this->offsetY = y; }
        int getFrameCount() { return this->frameCount; }
        void setFrameCount(int frameCount) { this->frameCount = frameCount; }
        int getCurrentFrame() { return this->currentFrame; }
        void setCurrentFrame(int currentFrame) { this->currentFrame = currentFrame; }
    protected:
    private:
        Image* sprite;
        int frameWidth;
        int frameHeight;
        // TODO: Create offset structure to hold info for each frame
        int offsetX;
        int offsetY;
        int frameCount;
        int currentFrame;
};

#endif // SPRITE_H
