#include "HBox.h"

#include "Widget.h"


namespace lx
{


void HBox::layout(const Size& widgetSize, const LinkedList<Widget*>* childs)
{
    int n = 0;
    double width = (double)widgetSize.w / childs->size();
    for (LinkedList<Widget*>::Iter i = childs->head(); i; i++, n++)
    {
        (*i)->setRect(Rect(
            width * n, 0,
            width, widgetSize.h
        ));
    }
}


}
