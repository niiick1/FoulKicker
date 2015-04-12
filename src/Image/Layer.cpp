#include "Layer.h"
#include "PTMReader.h"

Layer::Layer()
{
    //ctor
}

Layer::~Layer()
{
    //dtor
}

void Layer::setImage(string path) {
    PTMReader ptm;
    this->img = ptm.readFile(path);
}

void Layer::fillColor(RGBAColor color, int w, int h) {
    if (!this->img) {
        delete this->img;
    }

    this->img = new Image(w, h);

    unsigned argb = color.toARGB();

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            this->img->setPixel(argb, x, y);
        }
    }
}
