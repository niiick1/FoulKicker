#include "Game.h"
#include <GL/gl.h>
#include <GL/glut.h>
#include "RGBAColor.h"

Game::Game()
{
    this->window = new Window(800, 600, "Foul Kicker");
//    this->layers = new Layer*[7];

    Layer* l0 = new Layer();
    RGBAColor color(255, 127, 0);
    l0->setImage("C:/Projects/OpenGL/FoulKicker/resources/img/stadium.ptm");
//    l0->fillColor(color, 800, 600);
    l0->setX(0);
    l0->setY(0);

    this->layers.push_back(l0);
    //this->layers[0] = l0;

    Layer* l1 = new Layer();
    l1->setImage("C:/Projects/OpenGL/FoulKicker/resources/img/bolaAnimadaPTM_T0.ptm");
    l1->setX(50);
    l1->setY(150);

    this->layers.push_back(l1);
//    this->layers[1] = l1;

    Layer* l2 = new Layer();
    l2->setImage("C:/Projects/OpenGL/FoulKicker/resources/img/bolaAnimadaPTM_T1.ptm");
    l2->setX(120);
    l2->setY(150);

    this->layers.push_back(l2);
//    this->layers[2] = l2;

    Layer* l3 = new Layer();
    l3->setImage("C:/Projects/OpenGL/FoulKicker/resources/img/bolaAnimadaPTM_T2.ptm");
    l3->setX(190);
    l3->setY(150);

    this->layers.push_back(l3);
//    this->layers[3] = l3;

    Layer* l4 = new Layer();
    l4->setImage("C:/Projects/OpenGL/FoulKicker/resources/img/bolaAnimadaPTM_T3.ptm");
    l4->setX(260);
    l4->setY(150);

    this->layers.push_back(l4);
//    this->layers[4] = l4;

    Layer* l5 = new Layer();
    l5->setImage("C:/Projects/OpenGL/FoulKicker/resources/img/bolaAnimadaPTM_T4.ptm");
    l5->setX(330);
    l5->setY(150);

    this->layers.push_back(l5);
//    this->layers[5] = l5;

    Layer* l6 = new Layer();
    l6->setImage("C:/Projects/OpenGL/FoulKicker/resources/img/bolaAnimadaPTM_T5.ptm");
    l6->setX(400);
    l6->setY(150);

    this->layers.push_back(l6);
//    this->layers[6] = l6;

    Layer* l7 = new Layer();
    l7->setImage("C:/Projects/OpenGL/FoulKicker/resources/img/bolaAnimadaPTM_T6.ptm");
    l7->setX(470);
    l7->setY(150);

    this->layers.push_back(l7);
//    this->layers[7] = l7;

    this->run();
}

Game::~Game()
{
    delete this->window;
}

void Game::animateBall() {
    Layer* ball = this->layers.at(1);
    ball->setX(ball->getX() + 20);
    this->run();
}

void Game::run() {
    if (!this->scene)
        this->scene = new Image(this->window->getWidth(), this->window->getHeight());

    for (int i = 0; i < 8; i++) {
        Layer* layer = this->layers.at(i);
        Image* img = layer->getImage();

        if (!img) continue;

        int height = img->getHeight(),
            width = img->getWidth();

        for (int y = 0; y < height; y++) {
            if (y + layer->getY() >= scene->getHeight()) break;

            for (int x = 0; x < width; x++) {
                if (x + layer->getX() >= scene->getWidth()) break;
                if (x + layer->getX() < 0) continue;

                unsigned scenePixel = scene->getPixel(x + layer->getX(), y + layer->getY()),
                    imgPixel = img->getPixel(x, y);

                if (((imgPixel >> 24) & 0xff) != 0) {
                    this->scene->setPixel(imgPixel, x + layer->getX(), y + layer->getY());
                }
            }
        }
    }
}

void Game::display(void) {
    glDrawPixels(scene->getWidth(), scene->getHeight(), GL_BGRA_EXT, GL_UNSIGNED_BYTE, scene->getPixels());

    glFlush();
}

