#include "SimpleButton.h"

#include <lx/Image.h>

namespace lx
{


SimpleButton::SimpleButton(Widget* parent, Image* normalBg, Image* pressedBg)
    : Widget(parent), _normalBg(normalBg), _pressedBg(pressedBg), _pressed(false)
{
    setSize(normalBg->size());
}

SimpleButton::~SimpleButton()
{
    delete _normalBg;
    delete _pressedBg;
}



void SimpleButton::paint(const Rect& dirty)
{
    Image* image = _pressed ? _pressedBg : _normalBg;

    drawImage(image, Point(
        (size().w - image->size().w) / 2,
        (size().h - image->size().h) / 2
    ));
}


void SimpleButton::mousePress(const Point& point)
{
    _pressed = true;

    repaint();
}

void SimpleButton::mouseRelease(const Point& point)
{
    _pressed = false;

    repaint();

    if (onClick) onClick();
}


}
