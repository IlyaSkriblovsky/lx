#ifndef __LX__SIMPLEBUTTON_H
#define __LX__SIMPLEBUTTON_H

#include <lx/Widget.h>
#include <lx/Delegate.h>

namespace lx
{

class Image;

class SimpleButton: public Widget
{
    public:
        SimpleButton(
            Widget* parent,
            Image* normalBg,  // takes ownership
            Image* pressedBg  // takes ownership
        );
        ~SimpleButton();


        virtual void paint(const Rect& dirty);

        virtual void mousePress(const Point& point);
        virtual void mouseRelease(const Point& point);


        Delegate0<> onClick;

    private:
        Image* _normalBg;
        Image* _pressedBg;

        bool _pressed;
};

}

#endif
