#include "MainLoop.h"

#include "Display.h"
#include "Window.h"

#include <X11/Xlib.h>
#include <cstdio>


namespace lx
{


MainLoop::MainLoop(Display *display)
    : _display(display)
{
}

MainLoop::~MainLoop()
{
}


void MainLoop::run()
{
    while (true)
    {
        XEvent event;
        XNextEvent(_display->xdisplay(), &event);

        for (LinkedList<Window*>::Iter i = Window::windows()->head(); i; i++)
            if ((*i)->xwindow() == event.xany.window)
                (*i)->processXEvent(&event);
    }
}


}
