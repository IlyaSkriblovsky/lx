#include "Display.h"
#include "Window.h"
#include "TestWidget.h"
#include "Image.h"
#include "BorderImage.h"
#include "MainLoop.h"

#include <cstdio>


class Button: public lx::Widget
{
    public:
        Button(lx::Widget *parent)
            : lx::Widget(parent), _pressed(false)
        {
            _normalBg = new lx::BorderImage(display(), "button.png", true, 4);
            _pressedBg = new lx::BorderImage(display(), "button-pressed.png", true, 4);
            _content = new lx::Image(display(), "button-content.png", true);

            setSize(200, 50);
        }

        ~Button()
        {
            delete _normalBg;
            delete _pressedBg;
            delete _content;
        }


    protected:
        virtual void paint(const lx::Rect& rect)
        {
            (_pressed ? _pressedBg : _normalBg)->drawOnCanvas(this, lx::Rect(lx::Point(), size()));

            drawImage(_content, lx::Point(
                (size().w - _content->size().w) / 2,
                (size().h - _content->size().h) / 2 + (_pressed ? 1 : 0)
            ));
        }

        virtual void mousePress(const lx::Point& point)
        {
            printf("Button pressed! "); point.print();
            _pressed = true;
            parent()->paint(rect());
        }

        virtual void mouseRelease(const lx::Point& point)
        {
            printf("Button released! "); point.print();
            _pressed = false;
            parent()->paint(rect());
        }

    private:
        lx::BorderImage* _normalBg;
        lx::BorderImage* _pressedBg;
        lx::Image* _content;

        bool _pressed;
};


int main(int argc, char *argv[])
{
    lx::Display display;

    lx::Window window(&display, true);
    window.show();
    window.setSize(400, 400);

    Button button(&window);
    button.setPosition(100, 100);


    lx::MainLoop mainLoop(&display);
    mainLoop.run();
}
