#ifndef __LX__CANVAS_H
#define __LX__CANVAS_H

#include <X11/Xlib.h>
#include <X11/extensions/Xrender.h>

#include "Rect.h"

namespace lx
{

class Display;
class Image;

class Canvas
{
    public:
        virtual ::GC xgc() const = 0;
        virtual ::Drawable xdrawable() const = 0;
        virtual ::Picture xpicture() const = 0;
        virtual Display* display() const = 0;

        virtual bool rgba() const = 0;

        virtual Point absolutePosition() const = 0;

        void drawLine(const Point& a, const Point& b);

        void drawImage(const Image* image, const Point& origin);

        void copyCanvas(const Canvas* canvas, const Rect& src, const Point& origin);

        void copyScaleCanvas(const Canvas* canvas, const Rect& src, const Rect& dst);

        void fillRect(const Rect& rect, unsigned int color);
};


}

#endif
