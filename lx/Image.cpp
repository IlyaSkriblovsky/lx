#include "Image.h"

#include "Display.h"
#include "Exception.h"

#include <Imlib2.h>


namespace lx
{


Image::Image(Display *display, const char *filename, bool rgba)
    : _display(display), _rgba(rgba)
{
    Imlib_Image image = imlib_load_image(filename);
    if (image == 0)
        throw Exception::format("Cannot load image: %s\n", filename);

    imlib_context_set_image(image);
    _size = Size(imlib_image_get_width(), imlib_image_get_height());



    Imlib_Image premul = imlib_create_image(_size.w, _size.h);
    imlib_context_set_image(premul);
    imlib_context_set_color(0, 0, 0, 255);
    imlib_image_fill_rectangle(0, 0, _size.w, _size.h);
    imlib_context_set_blend(1);
    imlib_blend_image_onto_image(image, 0, 0, 0, _size.w, _size.h, 0, 0, _size.w, _size.h);
    imlib_image_copy_alpha_to_image(image, 0, 0);

    _xpixmap = XCreatePixmap(
        _display->xdisplay(), _display->root(),
        _size.w, _size.h,
        _rgba ? 32 : 24
    );
    if (_xpixmap == 0)
        throw Exception("Cannot create pixmap");

    _xgc = XCreateGC(_display->xdisplay(), _xpixmap, 0, 0);

    imlib_context_set_display(_display->xdisplay());
    imlib_context_set_colormap(_rgba ? _display->rgbaColormap() : _display->defaultColormap());
    imlib_context_set_visual(_rgba ? _display->rgbaVisual() : _display->defaultVisual());
    imlib_context_set_drawable(_xpixmap);
    imlib_context_set_blend(0);
    imlib_render_image_on_drawable(0, 0);

    imlib_free_image();
    imlib_context_set_image(image);
    imlib_free_image();

    _xpicture = XRenderCreatePicture(
        _display->xdisplay(), _xpixmap,
        _rgba ? _display->rgbaPictFormat() : _display->rgbPictFormat(),
        0, 0
    );
    if (_xpicture == 0)
        throw Exception("Cannot create picture");
}


Image::Image(Display* display, const Size& size, bool rgba)
    : _display(display), _size(size), _rgba(rgba)
{
    _xpixmap = XCreatePixmap(
        _display->xdisplay(), _display->root(),
        _size.w, _size.h,
        rgba ? 32 : 24
    );

    _xgc = XCreateGC(_display->xdisplay(), _xpixmap, 0, 0);

    _xpicture = XRenderCreatePicture(
        _display->xdisplay(), _xpixmap,
        _rgba ? _display->rgbaPictFormat() : _display->rgbPictFormat(),
        0, 0
    );
}



Image::~Image()
{
    XRenderFreePicture(_display->xdisplay(), _xpicture);
    XFreeGC(_display->xdisplay(), _xgc);
    XFreePixmap(_display->xdisplay(), _xpixmap);
}


Display* Image::display() const { return _display; }
::GC Image::xgc() const { return _xgc; }
::Drawable Image::xdrawable() const { return _xpixmap; }
::Picture Image::xpicture() const { return _xpicture; }
bool Image::rgba() const { return _rgba; }


Size Image::size() const { return _size; }
Point Image::absolutePosition() const { return Point(0, 0); }


}
