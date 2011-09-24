#include <lx/Display.h>
#include <lx/Window.h>
#include <lx/TestWidget.h>
#include <lx/Image.h>
#include <lx/BorderImage.h>
#include <lx/MainLoop.h>
#include <widgets/ScalableButtonStyle.h>
#include <widgets/ScalableButton.h>
#include <widgets/SliderStyle.h>
#include <widgets/Slider.h>
#include <widgets/SimpleButton.h>

#include <cstdio>


class BlackWidget: public lx::Widget
{
    public:
        BlackWidget(Widget* parent): Widget(parent) { }

        virtual void paint(const lx::Rect& dirty)
        {
            fillRectangle(dirty.intersect(rect() - position()), 0xff000000);

            Widget::paint(dirty);
        }
};


lx::Slider *slider;


void onPrev() { slider->setValue(slider->value() - 0.1); }
void onNext() { slider->setValue(slider->value() + 0.1); }


int main(int argc, char *argv[])
{
    lx::Display display;

    lx::Window window(&display, true);
    window.show();
    window.setSize(480, 400);


    BlackWidget blackWidget(&window);
    blackWidget.setSize(480, 98);
    blackWidget.setPosition(0, 100);

    lx::SimpleButton playlists = lx::SimpleButton(&blackWidget, new lx::Image(&display, "playlists.png", true), new lx::Image(&display, "playlists-pressed.png", true));
    playlists.setPosition(0, 0);

    lx::SimpleButton prev = lx::SimpleButton(&blackWidget, new lx::Image(&display, "prev.png", true), new lx::Image(&display, "prev-pressed.png", true));
    prev.setPosition(96, 0);
    prev.onClick = onPrev;

    lx::SimpleButton play = lx::SimpleButton(&blackWidget, new lx::Image(&display, "play.png", true), new lx::Image(&display, "play-pressed.png", true));
    play.setPosition(192, 0);

    lx::SimpleButton next = lx::SimpleButton(&blackWidget, new lx::Image(&display, "next.png", true), new lx::Image(&display, "next-pressed.png", true));
    next.setPosition(288, 0);
    next.onClick = onNext;

    lx::SimpleButton rotate = lx::SimpleButton(&blackWidget, new lx::Image(&display, "rotate.png", true), new lx::Image(&display, "rotate-pressed.png", true));
    rotate.setPosition(384, 0);


    lx::Image sliderBackground(&display, "slider-background.png", true);
    lx::Image sliderButton(&display, "slider-button.png", true);
    lx::SliderStyle sliderStyle(&sliderBackground, &sliderButton, 12, 26);

    slider = new lx::Slider(&window, &sliderStyle);
    slider->setPosition(- sliderStyle.sideGap(), 56);
    slider->setSize(window.size().w + 2 * sliderStyle.sideGap(), slider->size().h);


    lx::MainLoop mainLoop(&display);
    mainLoop.run();

    delete slider;
}
