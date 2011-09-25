#ifndef __LX__LAYOUT_H
#define __LX__LAYOUT_H

#include "Size.h"
#include "LinkedList.h"

namespace lx
{

class Widget;

class Layout
{
    public:
        virtual ~Layout();


        virtual void layout(const Size& widgetSize, const LinkedList<Widget*>* childs) = 0;
};


}

#endif
