#ifndef POSITION_H
#define POSITION_H


class Position
{
    public:
        Position();
        Position(int x, int y);
        virtual ~Position();

        int getPosX() const { return this->posX; }
        void setPosX(int posX) { this->posX = posX; }
        int getPosY() const { return this->posY; }
        void setPosY(int posY) { this->posY = posY; }
        int getHeight() const { return height; }
        void setHeight(int h) { height = h; }
        int getWidth() const { return width; }
        void setWidth(int w) { width = w; }
    protected:
    private:
        int posX;
        int posY;
        int height;
        int width;
};

#endif // POSITION_H
