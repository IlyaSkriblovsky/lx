#include "Slider.h"

#include "SliderStyle.h"
#include <lx/Image.h>

namespace lx
{


Slider::Slider(Widget* parent, const SliderStyle* style)
    : Widget(parent), _style(style), _value(0.5), _dragging(false)
{
    setSize(200, _style->button()->size().h);
}


void Slider::paint(const Rect& dirty)
{
    Image* background = _style->background();

    int y = (size().h - background->size().h) / 2;
    int bw = background->size().w;
    int bh = background->size().h;

    int gap = _style->sideGap();

    int buttonX = (int)(_value * (size().w - 2 * _style->buttonRadius())) + _style->buttonRadius();

    copyCanvas(background,
        Rect(0, 0, _style->borderWidth(), bh),
        Point(gap, y)
    );

    copyCanvas(background,
        Rect(bw - _style->borderWidth(), 0, _style->borderWidth(), bh),
        Point(size().w - gap - _style->borderWidth(), y)
    );

    copyScaleCanvas(background,
        Rect(
            _style->borderWidth(), 0,
            _style->fillerWidth(), bh
        ),
        Rect(
            gap + _style->borderWidth(), y,
            buttonX - gap - _style->borderWidth(), bh
        )
    );

    copyScaleCanvas(background,
        Rect(
            _style->borderWidth() + _style->fillerWidth(), 0,
            _style->fillerWidth(), bh
        ),
        Rect(
            buttonX, y,
            size().w - gap - _style->borderWidth() - buttonX, bh
        )
    );


    Image* button = _style->button();

    drawImage(button,
        Point(
            buttonX - button->size().w / 2,
            (size().h - button->size().h) / 2
        )
    );
}



void Slider::mousePress(const Point& point)
{
    setValue((double)(point.x - _style->buttonRadius()) / (size().w - 2 * _style->buttonRadius()));

    _dragging = true;
}

void Slider::mouseRelease(const Point& point)
{
    _dragging = false;
}

void Slider::mouseMove(const Point& point)
{
    if (_dragging)
        setValue((double)(point.x - _style->buttonRadius()) / (size().w - 2 * _style->buttonRadius()));
}


void Slider::setValue(double value)
{
    _value = value;
    if (_value < 0) _value = 0;
    if (_value > 1) _value = 1;
    repaint();
}


}
