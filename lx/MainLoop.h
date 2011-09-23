#ifndef __LX__MAINLOOP_H
#define __LX__MAINLOOP_H

namespace lx
{


class Display;


class MainLoop
{
    public:
        MainLoop(Display *display);
        virtual ~MainLoop();


        virtual void run();


    private:
        Display *_display;
};


}

#endif
