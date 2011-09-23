#ifndef __LX__BORDERIMAGE_H
#define __LX__BORDERIMAGE_H


#include "Rect.h"

namespace lx
{

class Display;
class Image;
class Canvas;

class BorderImage
{
    public:
        BorderImage(Display *display, const char *filename, bool rgba, int leftBorder, int topBorder = -1, int rightBorder = -1, int bottomBorder = -1);
        ~BorderImage();


        int leftBorder() const { return _leftBorder; }
        int topBorder() const { return _topBorder; }
        int rightBorder() const { return _rightBorder; }
        int bottomBorder() const { return _bottomBorder; }


        void drawOnCanvas(Canvas *canvas, const Rect& rect) const;


    private:
        Image* _image;

        int _leftBorder;
        int _rightBorder;
        int _topBorder;
        int _bottomBorder;
};


}


#endif
