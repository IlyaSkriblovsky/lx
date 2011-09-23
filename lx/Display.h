#ifndef __LX__DISPLAY_H
#define __LX__DISPLAY_H

#include <X11/Xlib.h>
#include <X11/extensions/Xrender.h>

#include "Exception.h"

namespace lx
{

class Display
{
    public:
        Display(const char *name = 0) throw(Exception);
        virtual ~Display();


        ::Display* xdisplay() const;
        ::Window root() const;

        Colormap defaultColormap() const;
        Colormap rgbaColormap() const;
        Visual* defaultVisual() const;
        Visual* rgbaVisual() const;

        XRenderPictFormat* rgbaPictFormat() const;
        XRenderPictFormat* rgbPictFormat() const;


    private:
        ::Display* _dpy;
        ::Window _root;

        Colormap _defaultColormap;
        Colormap _rgbaColormap;
        Visual* _defaultVisual;
        XVisualInfo _rgbaVisual;

        XRenderPictFormat* _rgbaPictFormat;
        XRenderPictFormat* _rgbPictFormat;
};

}

#endif
