#ifndef LAYER_H
#define LAYER_H

#include <string>
#include <vector>
#include "Image.h"
#include "RGBAColor.h"

using std::string;

class Layer
{
    public:
        Layer();
        virtual ~Layer();

        void addImage(string path);
        void fillColor(RGBAColor color, int w, int h);

        Image* getImage();
        void nextFrame();

        unsigned getCurrentPos() { return this->currentPos; }
        void setCurrentPos(unsigned currentPos) { this->currentPos = currentPos; }
        int getX() { return this->x; }
        void setX(int x) { this->x = x; }
        int getY() { return this->y; }
        void setY(int y) { this->y = y; }
        int getZ() { return this->z; }
        void setZ(int z) { this->z = z; }

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
    protected:
    private:
        unsigned currentPos;
        Image* img;
        int x;
        int y;
        int z;

        int frameWidth;
        int frameHeight;
        int offsetX;
        int offsetY;
        int frameCount;
        int currentFrame;
};

#endif // LAYER_H
