#ifndef __LX__SCALABLEBUTTONSTYLE_H
#define __LX__SCALABLEBUTTONSTYLE_H

#include <lx/Point.h>

#include "WidgetStyle.h"

namespace lx
{

class Image;
class BorderImage;


class ScalableButtonStyle: public WidgetStyle
{
    public:
        ScalableButtonStyle(
            BorderImage* normalBackground,
            BorderImage* pressedBackground,
            Image* content,
            const Point& contentOffset = Point()
        ): _normalBackground(normalBackground),
           _pressedBackground(pressedBackground),
           _content(content), _contentOffset(contentOffset)
        {
        }


        BorderImage* normalBackground() const { return _normalBackground; }
        BorderImage* pressedBackground() const { return _pressedBackground; }
        Image* content() const { return _content; }
        Point contentOffset() const { return _contentOffset; }

    private:
        BorderImage* _normalBackground;
        BorderImage* _pressedBackground;
        Image* _content;
        Point _contentOffset;
};


}

#endif
