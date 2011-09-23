#ifndef __LX__IMAGE_H
#define __LX__IMAGE_H

#include <X11/Xlib.h>
#include <X11/extensions/Xrender.h>

#include "Size.h"
#include "Canvas.h"

namespace lx
{

class Display;

class Image: public Canvas
{
    public:
        Image(Display *display, const char *filename, bool rgba = false);
        ~Image();


        Size size() const;


        virtual Display* display() const;
        virtual ::GC xgc() const;
        virtual ::Drawable xdrawable() const;
        virtual ::Picture xpicture() const;
        virtual bool rgba() const;


    protected:
        virtual Point absolutePosition() const;


    private:
        Display *_display;

        ::GC _xgc;
        ::Pixmap _xpixmap;
        ::Picture _xpicture;
        bool _rgba;

        Size _size;
};


}

#endif
