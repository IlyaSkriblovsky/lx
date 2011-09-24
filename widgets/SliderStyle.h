#ifndef __LX__SLIDERSTYLE_H
#define __LX__SLIDERSTYLE_H

#include <lx/Image.h>

#include "WidgetStyle.h"

namespace lx
{

class SliderStyle: public WidgetStyle
{
    public:
        SliderStyle(
            Image* background,
            Image* button,
            int borderWidth,
            int sideGap = -1
        ): _background(background), _button(button),
           _borderWidth(borderWidth), _sideGap(sideGap)
        {
            _fillerWidth = (background->size().w - 2 * _borderWidth) / 2;

            _buttonRadius = _button->size().w / 2;

            if (_sideGap == -1)
                _sideGap = _buttonRadius;
        }


        Image* background() const { return _background; }
        Image* button() const { return _button; }

        int borderWidth() const { return _borderWidth; }
        int fillerWidth() const { return _fillerWidth; }

        int sideGap() const { return _sideGap; }
        int buttonRadius() const { return _buttonRadius; }

    private:
        Image* _background;
        Image* _button;

        int _borderWidth;
        int _fillerWidth;
        int _buttonRadius;
        int _sideGap;
};


}

#endif
