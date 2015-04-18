#ifndef GAME_H
#define GAME_H

#include <vector>
#include "Window.h"
#include "Layer.h"

class Game
{
    public:
        Game();
        virtual ~Game();

        void run();
        void animateBall();
        void display(void);

        Window* getWindow() { return this->window; }
    protected:
    private:
        Window* window;
        Image* scene;
        std::vector<Layer*> layers;
};

#endif // GAME_H