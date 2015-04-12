#include "Layer.h"
#include "PTMReader.h"

Layer::Layer() : currentPos(0)
{}

Layer::~Layer()
{
    //dtor
}

void Layer::addImage(string path) {
    PTMReader ptm;
    this->sprite.push_back(ptm.readFile(path));
}

Image* Layer::getCurrentImage() {
    return this->sprite.at(currentPos);
}

void Layer::nextFrame() {
    if (this->currentPos == this->sprite.size() - 1) {
        this->currentPos = 0;
    } else {
        this->currentPos++;
    }
}

void Layer::fillColor(RGBAColor color, int w, int h) {
    Image* img = new Image(w, h);
    unsigned argb = color.toARGB();

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            img->setPixel(argb, x, y);
        }
    }

    this->sprite.clear();
    this->sprite.push_back(img);
}
