#include "TestWidget.h"

namespace lx
{


TestWidget::TestWidget(Widget *parent)
    : Widget(parent)
{
}



void TestWidget::paint(const Rect& rect)
{
    drawLine(Point(0, 0), Point(size().w, size().h));
}


}
