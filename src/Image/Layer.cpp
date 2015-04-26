#include "Layer.h"
#include "PTMReader.h"

Layer::Layer()
{
    this->lastPos = nullptr;
}

Layer::~Layer()
{}

void Layer::addImage(string path) {
    PTMReader ptm;
    this->img = ptm.readFile(path);
}

Image* Layer::getImage() {
    return this->img;
}

void Layer::fillColor(RGBAColor color, int w, int h) {
    Image* img = new Image(w, h);
    unsigned argb = color.toARGB();

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            img->setPixel(argb, x, y);
        }
    }

    this->img = img;
}

Image* Layer::draw(Image* scene, int sceneX, int sceneY) {
    if (!scene) return scene;

    Image* img = this->img;

    int height = img->getHeight(),
        width = img->getWidth();

    for (int y = 0; y < height; y++) {
        int posY = y + sceneY;
        if (posY >= scene->getHeight()) break;
        if (posY < 0) continue;

        for (int x = 0; x < width; x++) {
            int posX = x + sceneX;
            if (posX >= scene->getWidth()) break;
            if (posX < 0) continue;

            RGBAColor imgPixel(img->getPixel(x, y));

            if (imgPixel.getA() != 0) {
                scene->setPixel(imgPixel.getARGB(), posX, posY);
            }
        }
    }

    return scene;
}

void Layer::saveCurrentPosition() {
    if (!lastPos) {
        lastPos = new Position(x, y);
    } else {
        lastPos->setPosX(x);
        lastPos->setPosY(y);
    }

    lastPos->setHeight(getHeight());
    lastPos->setWidth(getWidth());
}

int Layer::getWidth() {
    if (!this->img) return 0;

    return this->img->getWidth();
}

int Layer::getHeight() {
    if (!this->img) return 0;

    return this->img->getHeight();
}
