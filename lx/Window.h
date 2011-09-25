#ifndef __LX__WINDOW_H
#define __LX__WINDOW_H

#include "Widget.h"
#include "Display.h"
#include "LinkedList.h"

#include <X11/Xlib.h>

namespace lx
{

    class Image;

    class Window: public Widget
    {
        public:
            Window(Display *display, bool rgba = false);
            ~Window();

            virtual Display* display() const { return _display; }
            ::Window xwindow() const { return _xwindow; }

            static LinkedList<Window*>* windows() { return &_windows; }



            virtual void setVisible(bool visible);

            virtual void setRect(const Rect& rect);



            virtual void processXEvent(XEvent *event);

            virtual ::GC xgc() const;
            virtual ::Drawable xdrawable() const;
            virtual ::Picture xpicture() const;
            virtual bool rgba() const;

            virtual void paint(const Rect& rect);

            void blit(const Rect& rect);


            Color backgroundColor() const { return _backgroundColor; }
            void setBackgroundColor(const Color& color);

        private:
            static LinkedList<Window*> _windows;


            class RealCanvas: public Canvas
            {
                public:
                    RealCanvas();
                    RealCanvas(Window* window);

                    virtual ::GC xgc() const;
                    virtual ::Drawable xdrawable() const;
                    virtual ::Picture xpicture() const;
                    virtual Display* display() const;

                    virtual bool rgba() const;

                    virtual Point absolutePosition() const;

                private:
                    Window* _window;
            };


            RealCanvas _realCanvas;


            Display* _display;

            ::Window _xwindow;
            ::GC _xgc;
            ::Picture _xpicture;

            bool _rgba;

            Image* _buffer;

            Widget* _mouseGrabber;


            void recreateBuffer();


            Color _backgroundColor;
    };

}

#endif
