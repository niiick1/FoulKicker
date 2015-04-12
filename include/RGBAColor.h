#ifndef RGBACOLOR_H
#define RGBACOLOR_H


class RGBAColor
{
    public:
        RGBAColor(unsigned r = 0, unsigned g = 0, unsigned b = 0, unsigned a = 255);
        virtual ~RGBAColor();

        unsigned toARGB();

        unsigned getR() { return r; }
        void setR(unsigned val) { r = val; }
        unsigned getG() { return g; }
        void setG(unsigned val) { g = val; }
        unsigned getB() { return b; }
        void setB(unsigned val) { b = val; }
        unsigned getA() { return a; }
        void setA(unsigned val) { a = val; }
    protected:
    private:
        unsigned r;
        unsigned g;
        unsigned b;
        unsigned a;
};

#endif // RGBACOLOR_H
