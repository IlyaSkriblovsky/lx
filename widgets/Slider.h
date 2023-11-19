#ifndef __LX__SLIDER_H
#define __LX__SLIDER_H

#include <lx/Widget.h>

namespace lx
{

class SliderStyle;

class Slider: public Widget
{
    public:
        Slider(Widget* parent, const SliderStyle* style);

        virtual void paint(const Rect& rect);

        virtual void mousePress(const Point& point);
        virtual void mouseRelease(const Point& point);
        virtual void mouseMove(const Point& point);


        double value() const { return _value; }
        void setValue(double value);

        Delegate1<float> onChange;

    private:
        const SliderStyle* _style;

        double _value;
        bool _dragging;
};

}

#endif
