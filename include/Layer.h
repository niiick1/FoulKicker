#ifndef LAYER_H
#define LAYER_H

#include <string>
#include "Image.h"
#include "RGBAColor.h"

using std::string;

class Layer
{
    public:
        Layer();
        virtual ~Layer();

        Image* getImage() { return this->img; }
        void setImage(Image* img) { this->img = img; }
        void setImage(string path);

        void fillColor(RGBAColor color, int w, int h);

        int getX() { return this->x; }
        void setX(int x) { this->x = x; }
        int getY() { return this->y; }
        void setY(int y) { this->y = y; }
        int getZ() { return this->z; }
        void setZ(int z) { this->z = z; }
    protected:
    private:
        Image* img;
        int x;
        int y;
        int z;
};

#endif // LAYER_H
