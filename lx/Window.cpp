#include "Window.h"

#include "Exception.h"


namespace lx
{


LinkedList<Window*> Window::_windows;


Window::Window(Display *display, bool rgba)
    : Widget(0), _display(display), _rgba(rgba), _mouseGrabber(0)
{
    _windows.append(this);

    XSetWindowAttributes attrs;
    attrs.colormap = rgba ? _display->rgbaColormap() : _display->defaultColormap();
    attrs.background_pixel = 0;
    attrs.border_pixmap = 0;

    _xwindow = XCreateWindow(
        _display->xdisplay(), _display->root(),
        position().x, position().y, size().w, size().h,
        0,
        rgba ? 32 : 24,
        InputOutput,
        rgba ? _display->rgbaVisual() : _display->defaultVisual(),
        CWBackPixel | CWColormap | CWBorderPixel, &attrs
    );

    if (_xwindow == 0)
        throw Exception("Cannot create window");


    _xgc = XCreateGC(_display->xdisplay(), _xwindow, 0, 0);
    if (_xgc == 0)
        throw Exception("Cannot create GC");


    _xpicture = XRenderCreatePicture(
        _display->xdisplay(),
        _xwindow,
        rgba ? _display->rgbaPictFormat() : _display->rgbPictFormat(),
        0, 0
    );


    XSelectInput(
        _display->xdisplay(), _xwindow,
        ExposureMask | ButtonPressMask | ButtonReleaseMask | ButtonMotionMask | PointerMotionHintMask
    );
}


Window::~Window()
{
    XRenderFreePicture(_display->xdisplay(), _xpicture);

    XFreeGC(_display->xdisplay(), _xgc);

    XDestroyWindow(_display->xdisplay(), _xwindow);

    _windows.removeByValue(this);
}



::GC Window::xgc() const { return _xgc; }
::Drawable Window::xdrawable() const { return _xwindow; }
::Picture Window::xpicture() const { return _xpicture; }
bool Window::rgba() const { return _rgba; }



void Window::setVisible(bool visible)
{
    if (visible)
        XMapWindow(_display->xdisplay(), _xwindow);
    else
        XUnmapWindow(_display->xdisplay(), _xwindow);

    Widget::setVisible(visible);
}


void Window::setRect(const Rect& rect)
{
    XMoveResizeWindow(
        _display->xdisplay(), _xwindow,
        rect.origin.x, rect.origin.y,
        rect.size.w, rect.size.h
    );

    Widget::setRect(rect);
}




void Window::processXEvent(XEvent *event)
{
    switch (event->type)
    {
        case Expose:
        {
            Rect r = Rect(
                event->xexpose.x, event->xexpose.y,
                event->xexpose.width, event->xexpose.height
            );
            printf("Expose: "); r.print();
            paint(r);
            break;
        }

        case ButtonPress:
        {
            Point p = Point(event->xbutton.x, event->xbutton.y);
            Widget* child = childAt(p);
            child->mousePress(p - child->absolutePosition());

            _mouseGrabber = child;

            break;
        }

        case ButtonRelease:
        {
            Point p = Point(event->xbutton.x, event->xbutton.y);
            Widget* child = _mouseGrabber ? _mouseGrabber : childAt(p);
            child->mouseRelease(p - child->absolutePosition());
            break;
        }

        case MotionNotify:
        {
            Point p;
            ::Window rootXWin, childXWin;
            int rootx, rooty;
            unsigned int mask;
            XQueryPointer(
                _display->xdisplay(), _xwindow,
                &rootXWin, &childXWin,
                &rootx, &rooty,
                &p.x, &p.y,
                &mask
            );

            Widget* child = _mouseGrabber ? _mouseGrabber : childAt(p);
            child->mouseMove(p - child->absolutePosition());
            break;
        }
    }
}



void Window::paint(const Rect& rect)
{
    fillRect(rect, 0xff000000);
    printf("Window::paint "); rect.print();

    Widget::paint(rect);
}


}
