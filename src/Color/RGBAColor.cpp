#include "RGBAColor.h"

RGBAColor::RGBAColor(unsigned r, unsigned g, unsigned b, unsigned a)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

RGBAColor::~RGBAColor()
{
    //dtor
}

unsigned RGBAColor::toARGB() {
    return ((this->a << 24) | (this->r << 16) | (this->g << 8) | this->b);
}
