#include "ScalableButton.h"

#include <lx/Image.h>
#include <lx/BorderImage.h>

#include "ScalableButtonStyle.h"

namespace lx
{


ScalableButton::ScalableButton(Widget* parent, ScalableButtonStyle* style)
    : Widget(parent), _style(style), _pressed(false)
{
    setSize(
        _style->content()->size().w + style->normalBackground()->leftBorder() + style->normalBackground()->rightBorder(),
        _style->content()->size().h + style->normalBackground()->topBorder() + style->normalBackground()->bottomBorder()
    );
}



void ScalableButton::paint(const Rect& rect)
{
    if (_pressed)
        _style->pressedBackground()->drawOnCanvas(this, Rect(Point(), size()));
    else
        _style->normalBackground()->drawOnCanvas(this, Rect(Point(), size()));

    Image* content = _style->content();

    drawImage(content, Point(
        (size().w - content->size().w) / 2,
        (size().h - content->size().h) / 2
    ));
}


void ScalableButton::mousePress(const Point& point)
{
    _pressed = true;

    paint(Rect(Point(), size()));
}

void ScalableButton::mouseRelease(const Point& point)
{
    _pressed = false;

    paint(Rect(Point(), size()));

    if (onClick) onClick();
}


}
