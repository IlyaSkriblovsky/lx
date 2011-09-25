#include "Window.h"

#include "Exception.h"
#include "Image.h"


namespace lx
{


LinkedList<Window*> Window::_windows;




Window::RealCanvas::RealCanvas(): _window(0) { }
Window::RealCanvas::RealCanvas(Window* window): _window(window) { }

GC       Window::RealCanvas::xgc() const { return _window->_xgc; }
Drawable Window::RealCanvas::xdrawable() const { return _window->_xwindow; }
Picture  Window::RealCanvas::xpicture() const { return _window->_xpicture; }
Display* Window::RealCanvas::display() const { return _window->_display; }
bool     Window::RealCanvas::rgba() const { return _window->_rgba; }
Point    Window::RealCanvas::absolutePosition() const { return Point(0, 0); }




Window::Window(Display *display, bool rgba)
    : Widget(0), _display(display), _rgba(rgba), _mouseGrabber(0), _backgroundColor(Color(0, 0, 0, 0))
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


    _realCanvas = RealCanvas(this);

    _buffer = 0;
    recreateBuffer();


    XSelectInput(
        _display->xdisplay(), _xwindow,
        ExposureMask | ButtonPressMask | ButtonReleaseMask
        | ButtonMotionMask | PointerMotionHintMask
        | StructureNotifyMask
    );
}


Window::~Window()
{
    delete _buffer;

    XRenderFreePicture(_display->xdisplay(), _xpicture);

    XFreeGC(_display->xdisplay(), _xgc);

    XDestroyWindow(_display->xdisplay(), _xwindow);

    _windows.removeByValue(this);
}



::GC Window::xgc() const { return _buffer->xgc(); }
::Drawable Window::xdrawable() const { return _buffer->xdrawable(); }
::Picture Window::xpicture() const { return _buffer->xpicture(); }
bool Window::rgba() const { return _rgba; }

Point Window::absolutePosition() const
{
    return Point(0, 0);
}



void Window::setVisible(bool visible)
{
    if (visible)
        XMapWindow(_display->xdisplay(), _xwindow);
    else
        XUnmapWindow(_display->xdisplay(), _xwindow);

    Widget::setVisible(visible);
}


void Window::recreateBuffer()
{
    delete _buffer;
    _buffer = new Image(_display, size(), _rgba);
}


void Window::setRect(const Rect& rect)
{
    if (rect != this->rect())
    {
        if (rect.size != this->size())
            XResizeWindow(
                _display->xdisplay(), _xwindow,
                rect.size.w, rect.size.h
            );

        Widget::setRect(rect);

        recreateBuffer();
    }
}




void Window::setBackgroundColor(const Color& color)
{
    _backgroundColor = color;
    repaint();
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

        case ConfigureNotify:
        {
            if (Size(
                    event->xconfigure.width, event->xconfigure.height
                ) != size())
                setRect(Rect(
                    Point(0, 0),
                    Size(event->xconfigure.width, event->xconfigure.height)
                ));

            break;
        }
    }
}



void Window::paint(const Rect& rect)
{
    fillRectangle(rect, _backgroundColor);

    Widget::paint(rect);

    blit(rect);
}

void Window::blit(const Rect& rect)
{
    _realCanvas.copyCanvas(_buffer, rect, rect.origin, true);
//    _realCanvas.copyRotatedCanvas(_buffer, Rect(Point(), _buffer->size()), Point());
}


}
