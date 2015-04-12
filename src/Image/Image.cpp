#include "Image.h"
#include <iostream>

Image::Image(int w, int h) :
    width(w), height(h), pixels(new unsigned[w*h])
{}

void Image::setPixel(unsigned argb, int x, int y)
{
    pixels[x+y*this->width] = argb;
}

Image::~Image()
{
    delete this->pixels;
}
