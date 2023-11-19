#include "Display.h"

#include <cstdio>

#include "Log.h"


namespace lx
{


Display::Display(const char *name)
{
    _dpy = XOpenDisplay(name);

    if (_dpy == 0)
        throw Exception("Cannot open display");

    _root = RootWindow(_dpy, DefaultScreen(_dpy));



    int scr = DefaultScreen(_dpy);
    _defaultColormap = DefaultColormap(_dpy, scr);
    _defaultVisual = DefaultVisual(_dpy, scr);
//    defaultFormat = XRenderFindVisualFormat(_dpy, defaultVisual);

    if (XMatchVisualInfo(_dpy, scr, 32, TrueColor, &_rgbaVisual) == 0)
        throw Exception("Cannot request RGBA visual");


    _rgbaColormap = XCreateColormap(_dpy, _root, _rgbaVisual.visual, AllocNone);

//    _rgbaPictFormat = XRenderFindVisualFormat(_dpy, _rgbaVisual.visual);
    _rgbPictFormat = XRenderFindStandardFormat(_dpy, PictStandardRGB24);
    _rgbaPictFormat = XRenderFindStandardFormat(_dpy, PictStandardARGB32);
}


Display::~Display()
{
    if (_dpy)
        XCloseDisplay(_dpy);
}



::Display* Display::xdisplay() const
{
    return _dpy;
}


::Window Display::root() const
{
    return _root;
}




Colormap Display::defaultColormap() const { return _defaultColormap; }
Colormap Display::rgbaColormap() const { return _rgbaColormap; }
Visual* Display::rgbaVisual() const { return _rgbaVisual.visual; }
Visual* Display::defaultVisual() const { return _defaultVisual; }

XRenderPictFormat* Display::rgbaPictFormat() const { return _rgbaPictFormat; }
XRenderPictFormat* Display::rgbPictFormat() const { return _rgbPictFormat; }



}
