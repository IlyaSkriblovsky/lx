#include "Canvas.h"

#include <cstdio>

#include "Display.h"
#include "Image.h"

namespace lx
{


void Canvas::drawLine(const Point& a, const Point& b)
{
    XSetForeground(display()->xdisplay(), xgc(), 0xffffff);

    Point offset = absolutePosition();

    XDrawLine(
        display()->xdisplay(), xdrawable(), xgc(),
        a.x + offset.x, a.y + offset.y,
        b.x + offset.x, b.y + offset.y
    );
}


void Canvas::drawImage(const Image* image, const Point& origin, bool copyArea)
{
    copyCanvas(image, Rect(Point(0, 0), image->size()), origin, copyArea);
}


void Canvas::copyCanvas(const Canvas* canvas, const Rect& src, const Point& origin, bool copyAlpha)
{
    Point offset = absolutePosition();

    if (
        (rgba() == false && canvas->rgba() == false) ||
        (rgba() == true && canvas->rgba() == true && copyAlpha)
       )
    {
        XCopyArea(
            display()->xdisplay(),
            canvas->xdrawable(), xdrawable(),
            xgc(),
            src.origin.x, src.origin.y,
            src.size.w, src.size.h,
            origin.x + offset.x, origin.y + offset.y
        );
    }
    else
    {
        XRenderComposite(
            display()->xdisplay(), PictOpOver,
            canvas->xpicture(), None, xpicture(),
            src.origin.x, src.origin.y,
            0, 0,
            origin.x + offset.x, origin.y + offset.y,
            src.size.w, src.size.h
        );
    }
}


void Canvas::copyScaleCanvas(const Canvas* canvas, const Rect& src, const Rect& dst)
{
    if (src.size == dst.size)
    {
        copyCanvas(canvas, src, dst.origin);
        return;
    }

    if (dst.size.w <= 0 || dst.size.h <= 0)
        return;

    XTransform xform = {{
        { XDoubleToFixed((double)src.size.w / dst.size.w), XDoubleToFixed(0), XDoubleToFixed(src.origin.x) },
        { XDoubleToFixed(0), XDoubleToFixed((double)src.size.h / dst.size.h), XDoubleToFixed(src.origin.y) },
        { XDoubleToFixed(0), XDoubleToFixed(0), XDoubleToFixed(1) },
    }};
    XRenderSetPictureTransform(display()->xdisplay(), canvas->xpicture(), &xform);

    Point offset = absolutePosition();

    XRenderComposite(
        display()->xdisplay(), PictOpOver,
        canvas->xpicture(), None, xpicture(),
        0, 0,
        0, 0,
        dst.origin.x + offset.x, dst.origin.y + offset.y,
        dst.size.w, dst.size.h
    );

    XTransform identity = {{
        { XDoubleToFixed(1), XDoubleToFixed(0), XDoubleToFixed(0) },
        { XDoubleToFixed(0), XDoubleToFixed(1), XDoubleToFixed(0) },
        { XDoubleToFixed(0), XDoubleToFixed(0), XDoubleToFixed(1) },
    }};
    XRenderSetPictureTransform(display()->xdisplay(), canvas->xpicture(), &identity);
}


void Canvas::copyRotatedCanvas(const Canvas* canvas, const Rect& src, const Point& origin)
{
    XTransform xform = {{
        { XDoubleToFixed(0), XDoubleToFixed(-1), XDoubleToFixed(0) },
        { XDoubleToFixed(1), XDoubleToFixed(0), XDoubleToFixed(0) },
        { XDoubleToFixed(0), XDoubleToFixed(0), XDoubleToFixed(1) },
    }};
    XRenderSetPictureTransform(display()->xdisplay(), canvas->xpicture(), &xform);

    Point offset = absolutePosition();

    XRenderComposite(
        display()->xdisplay(), PictOpOver,
        canvas->xpicture(), None, xpicture(),
//        src.origin.x, src.origin.y,
//        0, 0,
//        origin.x + offset.x, origin.y + offset.y,
//        src.size.w, src.size.h
        src.origin.x, -src.size.w,
        0, 0,
        origin.x + offset.x, origin.y + offset.y,
        src.size.w, src.size.h
    );

    XTransform identity = {{
        { XDoubleToFixed(1), XDoubleToFixed(0), XDoubleToFixed(0) },
        { XDoubleToFixed(0), XDoubleToFixed(1), XDoubleToFixed(0) },
        { XDoubleToFixed(0), XDoubleToFixed(0), XDoubleToFixed(1) },
    }};
    XRenderSetPictureTransform(display()->xdisplay(), canvas->xpicture(), &identity);
}


void Canvas::drawRectangle(const Rect& rect, const Color& color)
{
    Point offset = absolutePosition();

    XSetForeground(display()->xdisplay(), xgc(), color.uint());

    XDrawRectangle(
        display()->xdisplay(), xdrawable(), xgc(),
        rect.origin.x + offset.x, rect.origin.y + offset.y,
        rect.size.w, rect.size.h
    );
}


void Canvas::fillRectangle(const Rect& rect, const Color& color)
{
    Point offset = absolutePosition();

    XSetForeground(display()->xdisplay(), xgc(), color.uint());

    XFillRectangle(
        display()->xdisplay(), xdrawable(), xgc(),
        rect.origin.x + offset.x, rect.origin.y + offset.y,
        rect.size.w, rect.size.h
    );
}

}
