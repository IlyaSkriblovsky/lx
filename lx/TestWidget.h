#ifndef __LX__TESTWIDGET_H
#define __LX__TESTWIDGET_H

#include "Widget.h"

namespace lx
{


class TestWidget: public Widget
{
    public:
        TestWidget(Widget *parent);

    protected:
        virtual void paint(const Rect& rect);
};


}

#endif
