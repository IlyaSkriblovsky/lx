#include "Widget.h"

namespace lx
{


Widget::Widget(Widget* parent)
    : _parent(parent), _rect(0, 0, 100, 100)
{
    if (_parent)
        _parent->addChild(this);
}


Widget::~Widget()
{
    for (LinkedList<Widget*>::Iter i = _childs.head(); i; i++)
        delete *i;
}



Display* Widget::display() const
{
    if (_parent)
        return _parent->display();

    return 0;
}



void Widget::addChild(Widget *child)
{
    _childs.append(child);
}

void Widget::removeChild(Widget *child)
{
    _childs.removeByValue(child);
}



void Widget::setVisible(bool visible)
{
    _visible = visible;
}


void Widget::setRect(const Rect& rect)
{
    _rect = rect;
}


Rect Widget::absoluteRect() const
{
    if (_parent)
        return _parent->absoluteRect() + _rect.origin;

    return _rect;
}

Point Widget::absolutePosition() const
{
    return absoluteRect().origin;
}


::GC Widget::xgc() const
{
    if (_parent) return _parent->xgc();
    return 0;
}

::Drawable Widget::xdrawable() const
{
    if (_parent) return _parent->xdrawable();
    return 0;
}

::Picture Widget::xpicture() const
{
    if (_parent) return _parent->xpicture();
    return 0;
}

bool Widget::rgba() const
{
    if (_parent) return _parent->rgba();
    return false;
}



void Widget::paint(const Rect& dirty)
{
    for (LinkedList<Widget*>::Iter i = _childs.head(); i; i++)
        if ((*i)->rect().intersects(dirty))
        {
            (*i)->paint(dirty - (*i)->position());
        }
}


void Widget::mousePress(const Point& point)
{
    for (LinkedList<Widget*>::Iter i = _childs.tail(); i; i--)
        if ((*i)->rect().contains(point))
        {
            (*i)->mousePress(point - (*i)->position());
            break;
        }
}


void Widget::mouseRelease(const Point& point)
{
    for (LinkedList<Widget*>::Iter i = _childs.tail(); i; i--)
        if ((*i)->rect().contains(point))
        {
            (*i)->mouseRelease(point - (*i)->position());
            break;
        }
}


void Widget::mouseMove(const Point& point)
{
    for (LinkedList<Widget*>::Iter i = _childs.tail(); i; i--)
        if ((*i)->rect().contains(point))
        {
            (*i)->mouseMove(point - (*i)->position());
            break;
        }
}


}
