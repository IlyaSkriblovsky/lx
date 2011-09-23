#include <lx/Display.h>
#include <lx/Window.h>
#include <lx/TestWidget.h>
#include <lx/Image.h>
#include <lx/BorderImage.h>
#include <lx/MainLoop.h>
#include <widgets/ScalableButtonStyle.h>
#include <widgets/ScalableButton.h>

#include <cstdio>



void sayhello()
{
    printf("Hello, World!\n");
}


int main(int argc, char *argv[])
{
    lx::Display display;

    lx::Window window(&display, true);
    window.show();
    window.setSize(600, 400);


    lx::BorderImage normalBg(&display, "button.png", true, 50);
    lx::BorderImage pressedBg(&display, "button-pressed.png", true, 4);
    lx::Image content(&display, "button-content.png", true);

    lx::ScalableButtonStyle style(&normalBg, &pressedBg, &content, lx::Point(0, 2));

    lx::ScalableButton button1(&window, &style);
    button1.setPosition(50, 50);
    button1.onClick = sayhello;
    button1.setSize(200, 100);

    lx::ScalableButton button2(&window, &style);
    button2.setPosition(300, 50);
    button2.onClick = sayhello;
    button2.setSize(200, 100);

    lx::ScalableButton button3(&window, &style);
    button3.setPosition(50, 200);
    button3.onClick = sayhello;
    button3.setSize(200, 100);

    lx::ScalableButton button4(&window, &style);
    button4.setPosition(300, 200);
    button4.onClick = sayhello;
    button4.setSize(200, 100);


    lx::MainLoop mainLoop(&display);
    mainLoop.run();
}
