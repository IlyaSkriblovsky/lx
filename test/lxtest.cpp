#include <lx/Display.h>
#include <lx/Window.h>
#include <lx/TestWidget.h>
#include <lx/Image.h>
#include <lx/BorderImage.h>
#include <lx/Color.h>
#include <lx/MainLoop.h>
#include <lx/HBox.h>
#include <widgets/ScalableButtonStyle.h>
#include <widgets/ScalableButton.h>
#include <widgets/SliderStyle.h>
#include <widgets/Slider.h>
#include <widgets/SimpleButton.h>

#include <cstdio>


class ColorWidget: public lx::Widget
{
    public:
        ColorWidget(Widget* parent, lx::Color color): Widget(parent), _color(color) { }

        virtual void paint(const lx::Rect& dirty)
        {
            fillRectangle(dirty.intersect(rect() - position()), _color);

            Widget::paint(dirty);
        }

    private:
        lx::Color _color;
};


lx::Window *window;
ColorWidget *colorWidget;
lx::SliderStyle *sliderStyle;
lx::Slider *slider;


void onPrev() { slider->setValue(slider->value() - 0.1); }
void onNext() { slider->setValue(slider->value() + 0.1); }


void onResize()
{
    colorWidget->setSize(window->size().w, colorWidget->size().h);
    slider->setSize(window->size().w + 2 * sliderStyle->sideGap(), slider->size().h);
}


int main(int argc, char *argv[])
{
    lx::Display display;


    printf("%08x\n", lx::Color(255, 0, 0, 128).uint());


    window = new lx::Window(&display, true);
    window->show();
    window->setSize(480, 400);
    window->setBackgroundColor(lx::Color::transparent);
    window->onSetRect = onResize;


    colorWidget = new ColorWidget(window, lx::Color::black);
    colorWidget->setSize(480, 98);
    colorWidget->setPosition(0, 200);
    colorWidget->setLayout(new lx::HBox);

    lx::SimpleButton playlists = lx::SimpleButton(colorWidget, new lx::Image(&display, "playlists.png", true), new lx::Image(&display, "playlists-pressed.png", true));

    lx::SimpleButton prev = lx::SimpleButton(colorWidget, new lx::Image(&display, "prev.png", true), new lx::Image(&display, "prev-pressed.png", true));
    prev.onClick = onPrev;

    lx::SimpleButton play = lx::SimpleButton(colorWidget, new lx::Image(&display, "play.png", true), new lx::Image(&display, "play-pressed.png", true));

    lx::SimpleButton next = lx::SimpleButton(colorWidget, new lx::Image(&display, "next.png", true), new lx::Image(&display, "next-pressed.png", true));
    next.onClick = onNext;

    lx::SimpleButton rotate = lx::SimpleButton(colorWidget, new lx::Image(&display, "rotate.png", true), new lx::Image(&display, "rotate-pressed.png", true));


    lx::Image sliderBackground(&display, "slider-background.png", true);
    lx::Image sliderButton(&display, "slider-button.png", true);
    sliderStyle = new lx::SliderStyle(&sliderBackground, &sliderButton, 12, 26);

    slider = new lx::Slider(window, sliderStyle);
    slider->setPosition(- sliderStyle->sideGap(), 156);
    slider->setSize(window->size().w + 2 * sliderStyle->sideGap(), slider->size().h);


    lx::MainLoop mainLoop(&display);
    mainLoop.run();

    delete window;
    delete sliderStyle;
}
