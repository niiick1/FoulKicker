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

        virtual void addImage(string path);
        void fillColor(RGBAColor color, int w, int h);
        virtual Image* draw(Image* scene, int sceneX, int sceneY);

        Image* getImage();

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