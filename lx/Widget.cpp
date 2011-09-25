#include "Widget.h"

#include "Layout.h"

namespace lx
{


Widget::Widget(Widget* parent)
    : _parent(parent), _rect(0, 0, 100, 100), _layout(0)
{
    if (_parent)
        _parent->addChild(this);
}


Widget::~Widget()
{
    delete _layout;

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

    if (_layout)
        _layout->layout(size(), &_childs);
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

    if (_layout)
        _layout->layout(_rect.size, &_childs);

    if (onSetRect) onSetRect();
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



Widget* Widget::childAt(const Point& point)
{
    for (LinkedList<Widget*>::Iter i = _childs.tail(); i; i--)
        if ((*i)->rect().contains(point))
            return (*i)->childAt(point - (*i)->position());

    return this;
}



void Widget::paint(const Rect& dirty)
{
    for (LinkedList<Widget*>::Iter i = _childs.head(); i; i++)
        if ((*i)->rect().intersects(dirty))
        {
            (*i)->paint(dirty - (*i)->position());
        }
}


void Widget::repaint()
{
    repaint(Rect(Point(0, 0), size()));
}

void Widget::repaint(const Rect& dirty)
{
    if (_parent)
        _parent->repaint(dirty + position());
    else
        paint(dirty);
}


void Widget::mousePress(const Point& point)
{
}


void Widget::mouseRelease(const Point& point)
{
}


void Widget::mouseMove(const Point& point)
{
}



void Widget::setLayout(Layout* layout)
{
    _layout = layout;
    _layout->layout(size(), &_childs);
}


}
