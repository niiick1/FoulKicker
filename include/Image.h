#ifndef IMAGE_H
#define IMAGE_H


class Image
{
    public:
        Image(int w, int h);

        void setPixel(unsigned argb, int x, int y);

        unsigned getPixel(int x, int y) { return pixels[x+y*this->width]; };
        unsigned* getPixels() { return this->pixels; }
        int getWidth() { return this->width; }
        int getHeight() { return this->height; }

        virtual ~Image();

    private:
        unsigned* pixels;

        int width,
            height;
};

#endif // IMAGE_H
