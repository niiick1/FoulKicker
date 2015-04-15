#include "Sprite.h"
#include "RGBAColor.h"

Sprite::Sprite()
{}

Sprite::~Sprite()
{
    delete this->sprite;
}

void Sprite::nextFrame() {
    if (this->currentFrame >= this->frameCount - 1) {
        this->currentFrame = 0;
    } else {
        this->currentFrame++;
    }
}

Image* Sprite::draw(Image* scene, int sceneX, int sceneY) {
    if (!scene) return scene;

    int startX = this->currentFrame * this->frameWidth + this->currentFrame * this->offsetX,
        startY = 0;

    for (int y = 0; y < this->frameHeight; y++) {
        int posY = y + startY + sceneY;
        if (posY >= scene->getHeight()) break;
        if (posY < 0) continue;

        for (int x = 0; x < this->frameWidth; x++) {
            int posX = x + startX + sceneX;
            if (posX >= scene->getWidth()) break;
            if (posX < 0) continue;

            RGBAColor imgPixel(this->sprite->getPixel(x + startX, y + startY));

            if (imgPixel.getA() != 0) {
                scene->setPixel(imgPixel.getARGB(), posX, posY);
            }
        }
    }

    return scene;
}


