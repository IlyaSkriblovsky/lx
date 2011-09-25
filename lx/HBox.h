#ifndef __LX__HBOX_H
#define __LX__HBOX_H

#include "Layout.h"

namespace lx
{


class HBox: public Layout
{
    public:
        virtual void layout(const Size& widgetSize, const LinkedList<Widget*>* childs);
};


}

#endif
