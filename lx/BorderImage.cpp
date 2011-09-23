#include "BorderImage.h"

#include "Image.h"
#include "Canvas.h"


namespace lx
{


BorderImage::BorderImage(Display *display, const char *filename, bool rgba, int leftBorder, int topBorder, int rightBorder, int bottomBorder)
{
    _image = new Image(display, filename, rgba);

    _leftBorder = leftBorder;

    if (topBorder == -1)
    {
        _topBorder = _leftBorder;
        _rightBorder = _leftBorder;
        _bottomBorder = _leftBorder;
    }
    else
    {
        _topBorder = topBorder;
        if (rightBorder == -1)
        {
            _rightBorder = _leftBorder;
            _bottomBorder = _topBorder;
        }
        else
        {
            _rightBorder = rightBorder;
            if (bottomBorder == -1)
                _bottomBorder = _topBorder;
            else
                _bottomBorder = bottomBorder;
        }
    }
}

BorderImage::~BorderImage()
{
    delete _image;
}


void BorderImage::drawOnCanvas(Canvas *canvas, const Rect& rect) const
{
    // left-top corner
    canvas->copyCanvas(_image, Rect(0, 0, _leftBorder, _topBorder), rect.origin);
    // right-top corner
    canvas->copyCanvas(_image, Rect(_image->size().w - _rightBorder, 0, _rightBorder, _topBorder), rect.origin + Point(rect.size.w - _rightBorder, 0));
    // left-bottom corner
    canvas->copyCanvas(_image, Rect(0, _image->size().h - _bottomBorder, _leftBorder, _bottomBorder), rect.origin + Point(0, rect.size.h - _bottomBorder));
    // right-bottom corner
    canvas->copyCanvas(_image, Rect(_image->size().w - _rightBorder, _image->size().h - _bottomBorder, _rightBorder, _bottomBorder), rect.origin + Point(rect.size.w - _rightBorder, rect.size.h - _bottomBorder));

    // top middle
    canvas->copyScaleCanvas(_image,
        Rect(_leftBorder, 0, _image->size().w - _leftBorder - _rightBorder, _topBorder),
        Rect(rect.origin.x + _leftBorder, rect.origin.y, rect.size.w - _leftBorder - _rightBorder, _topBorder)
    );

    // bottom middle
    canvas->copyScaleCanvas(_image,
        Rect(_leftBorder, _image->size().h - _bottomBorder, _image->size().w - _leftBorder - _rightBorder, _bottomBorder),
        Rect(rect.origin.x + _leftBorder, rect.origin.y + rect.size.h - _bottomBorder, rect.size.w - _leftBorder - _rightBorder, _bottomBorder)
    );

    // left middle
    canvas->copyScaleCanvas(_image,
        Rect(0, _topBorder, _leftBorder, _image->size().h - _topBorder - _bottomBorder),
        Rect(rect.origin.x, rect.origin.y + _topBorder, _leftBorder, rect.size.h - _topBorder - _bottomBorder)
    );

    // right middle
    canvas->copyScaleCanvas(_image,
        Rect(_image->size().w - _rightBorder, _topBorder, _rightBorder, _image->size().h - _topBorder - _bottomBorder),
        Rect(rect.origin.x + rect.size.w - _rightBorder, rect.origin.y + _topBorder, _rightBorder, rect.size.h - _topBorder - _bottomBorder)
    );

    // center
    canvas->copyScaleCanvas(_image,
        Rect(_leftBorder, _topBorder, _image->size().w - _leftBorder - _rightBorder, _image->size().h - _topBorder - _bottomBorder),
        Rect(rect.origin.x + _leftBorder, rect.origin.y + _topBorder, rect.size.w - _leftBorder - _rightBorder, rect.size.h - _topBorder - _bottomBorder)
    );
}

}
