#ifndef __LX__WIDGET_H
#define __LX__WIDGET_H

#include "LinkedList.h"
#include "Rect.h"
#include "Canvas.h"

namespace lx
{

class Display;
class DrawContext;

class Widget: public Canvas
{
    public:
        Widget(Widget *parent);
        virtual ~Widget();


        virtual Display* display() const;


        Widget* parent() { return _parent; }
        const Widget* parent() const { return _parent; }


        void addChild(Widget *child);
        void removeChild(Widget *child);


        void show() { setVisible(true); }
        void hide() { setVisible(false); }
        virtual void setVisible(bool visible);
        bool visible() const { return _visible; }


        inline Rect rect() const { return _rect; }
        virtual void setRect(const Rect& rect);

        inline Size size() const { return _rect.size; }
        inline void setSize(const Size& size) { setRect(Rect(_rect.origin, size)); }
        inline void setSize(int w, int h) { setRect(Rect(_rect.origin, Size(w, h))); }

        inline Point position() const { return _rect.origin; }
        inline void setPosition(const Point& position) { setRect(Rect(position, _rect.size)); }
        inline void setPosition(int x, int y) { setRect(Rect(Point(x, y), _rect.size)); }

        Rect absoluteRect() const;
        virtual Point absolutePosition() const;


        virtual ::GC xgc() const;
        virtual ::Drawable xdrawable() const;
        virtual ::Picture xpicture() const;

        virtual bool rgba() const;

        Widget* childAt(const Point& point);



        virtual void paint(const Rect& dirty);
        virtual void mousePress(const Point& point);
        virtual void mouseRelease(const Point& point);
        virtual void mouseMove(const Point& point);


    private:
        Widget *_parent;
        LinkedList<Widget*> _childs;

        bool _visible;

        Rect _rect;
};

}

#endif
