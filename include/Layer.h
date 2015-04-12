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

        Image* getCurrentImage();
        void nextFrame();

        unsigned getCurrentPos() { return this->currentPos; }
        void setCurrentPos(unsigned currentPos) { this->currentPos = currentPos; }
        int getX() { return this->x; }
        void setX(int x) { this->x = x; }
        int getY() { return this->y; }
        void setY(int y) { this->y = y; }
        int getZ() { return this->z; }
        void setZ(int z) { this->z = z; }
    protected:
    private:
        unsigned currentPos;
        std::vector<Image*> sprite;
        int x;
        int y;
        int z;
};

#endif // LAYER_H
