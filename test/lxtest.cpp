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


class MainWindow: public lx::Window
{
    public:
        MainWindow(lx::Display* display, bool rgba): lx::Window(display, rgba)
        {
            setBackgroundColor(lx::Color(0x3a, 0x59, 0xe7, 0x80));

            _buttonBox = new ColorWidget(this, lx::Color::black);
            _buttonBox->setLayout(new lx::HBox);


            new lx::SimpleButton(_buttonBox, new lx::Image(display, "playlists.png", true), new lx::Image(display, "playlists-pressed.png", true));

            lx::SimpleButton* prev = new lx::SimpleButton(_buttonBox, new lx::Image(display, "prev.png", true), new lx::Image(display, "prev-pressed.png", true));
            prev->onClick = lx::Delegate(this, &MainWindow::onPrev);

            new lx::SimpleButton(_buttonBox, new lx::Image(display, "play.png", true), new lx::Image(display, "play-pressed.png", true));

            lx::SimpleButton* next = new lx::SimpleButton(_buttonBox, new lx::Image(display, "next.png", true), new lx::Image(display, "next-pressed.png", true));
            next->onClick = lx::Delegate(this, &MainWindow::onNext);

            new lx::SimpleButton(_buttonBox, new lx::Image(display, "rotate.png", true), new lx::Image(display, "rotate-pressed.png", true));


            _sliderBackground = new lx::Image(display, "slider-background.png", true);
            _sliderButton = new lx::Image(display, "slider-button.png", true);
            _sliderStyle = new lx::SliderStyle(_sliderBackground, _sliderButton, 12, 26);

            _slider = new lx::Slider(this, _sliderStyle);
            _slider->onChange = lx::Delegate(this, &MainWindow::onSliderChange);

            setSize(480, 400);
        }

        ~MainWindow()
        {
            delete _sliderStyle;
            delete _sliderBackground;
            delete _sliderButton;
        }


        void onPrev()
        {
            _slider->setValue(_slider->value() - 0.1);
        }

        void onNext()
        {
            _slider->setValue(_slider->value() + 0.1);
        }


        void layout()
        {
            _buttonBox->setRect(lx::Rect(
                0, size().h - _buttonBox->size().h,
                size().w, _buttonBox->size().h
            ));

            _slider->setPosition(- _sliderStyle->sideGap(), _buttonBox->position().y - 44);
            _slider->setSize(size().w + 2 * _sliderStyle->sideGap(), _slider->size().h);
        }


        virtual void setRect(const lx::Rect& rect)
        {
            lx::Window::setRect(rect);

            layout();
        }

        void onSliderChange(float value)
        {
            int color = value * 255;
            setBackgroundColor(lx::Color(0x3a, 0x59, 0xe7, color));
        }



    private:
        ColorWidget* _buttonBox;
        lx::Slider* _slider;

        lx::Image* _sliderBackground;
        lx::Image* _sliderButton;
        lx::SliderStyle* _sliderStyle;
};



int main(int argc, char *argv[])
{
    lx::Display display;

    MainWindow window(&display, true);
    window.show();

    lx::MainLoop mainLoop(&display);
    mainLoop.run();
}
