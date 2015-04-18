#include "SpriteLayer.h"

SpriteLayer::SpriteLayer()
{}

SpriteLayer::~SpriteLayer()
{
    delete this->sprite;
}

void SpriteLayer::addImage(string path) {
    this->Layer::addImage(path);

    this->sprite = new Sprite();
    this->sprite->setSprite(this->getImage());
}

void SpriteLayer::nextFrame() {
    this->sprite->nextFrame();
}

Image* SpriteLayer::draw(Image* scene, int sceneX, int sceneY) {
    if (!scene) return scene;

    Sprite* sprite = this->sprite;

    int startX = sprite->getCurrentFrame() * sprite->getFrameWidth() + sprite->getCurrentFrame() * sprite->getOffsetX(),
        startY = 0;

    for (int y = 0; y < sprite->getFrameHeight(); y++) {
        int posY = y + sceneY;
        if (posY >= scene->getHeight()) break;
        if (posY < 0) continue;

        for (int x = 0; x < sprite->getFrameWidth(); x++) {
            int posX = x + sceneX;
            if (posX >= scene->getWidth()) break;
            if (posX < 0) continue;

            RGBAColor imgPixel(sprite->getSprite()->getPixel(x + startX, y + startY));

            if (imgPixel.getA() != 0) {
                scene->setPixel(imgPixel.getARGB(), x + sceneX, y + sceneY);
            }
        }
    }

    this->nextFrame();
    return scene;
}

int SpriteLayer::getWidth() {
    if (!this->sprite) return 0;

    return this->sprite->getFrameWidth();
}

int SpriteLayer::getHeight() {
    if (!this->sprite) return 0;

    return this->sprite->getFrameHeight();
}
