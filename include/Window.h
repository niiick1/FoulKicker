#ifndef WINDOW_H
#define WINDOW_H

#include <string>

using std::string;

class Window
{
    public:
        Window(unsigned w, unsigned h, string title = "Window");
        virtual ~Window();

        unsigned getWidth() { return this->width; }
        unsigned getHeight() { return this->height; }
        string getTitle() { return this->title; }
        void setTitle(string title) { this->title = title; }
    protected:
    private:
        void startGlut();

        unsigned height;
        unsigned width;
        string title;
};

#endif // WINDOW_H
