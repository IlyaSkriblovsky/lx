#ifndef __LX__SCALABLEBUTTON_H
#define __LX__SCALABLEBUTTON_H

#include <lx/Widget.h>
#include <lx/Delegate.h>

namespace lx
{

class ScalableButtonStyle;

class ScalableButton: public Widget
{
    public:
        ScalableButton(Widget* parent, ScalableButtonStyle* style);

        Delegate0<> onClick;

    protected:
        virtual void paint(const Rect& rect);

        virtual void mousePress(const Point& point);
        virtual void mouseRelease(const Point& point);

    private:
        ScalableButtonStyle* _style;

        bool _pressed;
};


}

#endif
