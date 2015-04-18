#ifndef POSITION_H
#define POSITION_H


class Position
{
    public:
        Position();
        Position(int x, int y);
        virtual ~Position();

        int getPosX() { return this->posX; }
        void setPosX(int posX) { this->posX = posX; }
        int getPosY() { return this->posY; }
        void setPosY(int posY) { this->posY = posY; }
    protected:
    private:
        int posX;
        int posY;
};

#endif // POSITION_H
