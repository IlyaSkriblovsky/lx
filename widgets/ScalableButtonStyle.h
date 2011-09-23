#ifndef __LX__SCALABLEBUTTONSTYLE_H
#define __LX__SCALABLEBUTTONSTYLE_H

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
            Image* content
        ): _normalBackground(normalBackground),
           _pressedBackground(pressedBackground),
           _content(content)
        {
        }


        BorderImage* normalBackground() const { return _normalBackground; }
        BorderImage* pressedBackground() const { return _pressedBackground; }
        Image* content() const { return _content; }

    private:
        BorderImage* _normalBackground;
        BorderImage* _pressedBackground;
        Image* _content;
};


}

#endif
