#ifndef __LX__CANVAS_H
#define __LX__CANVAS_H

#include <X11/Xlib.h>
#include <X11/extensions/Xrender.h>

#include "Rect.h"
#include "Color.h"

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

        void drawImage(const Image* image, const Point& origin, bool copyAlpha = false);

        void copyCanvas(const Canvas* canvas, const Rect& src, const Point& origin, bool copyAlpha = false);
        void copyScaleCanvas(const Canvas* canvas, const Rect& src, const Rect& dst);
        void copyRotatedCanvas(const Canvas* canvas, const Rect& src, const Point& origin);

        void drawRectangle(const Rect& rect, const Color& color);
        void fillRectangle(const Rect& rect, const Color& color);
};


}

#endif
