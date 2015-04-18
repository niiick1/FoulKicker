#ifndef SPRITELAYER_H
#define SPRITELAYER_H

#include "Layer.h"
#include "Sprite.h"
#include <string>

class SpriteLayer : public Layer
{
    public:
        SpriteLayer();
        virtual ~SpriteLayer();

        void addImage(string path);
        Image* draw(Image* scene, int sceneX, int sceneY);
        void nextFrame();

        Sprite* getSprite() { return this->sprite; }
        int getWidth();
        int getHeight();
    protected:
    private:
        Sprite* sprite;
};

#endif // SPRITELAYER_H
