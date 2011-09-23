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
    window.setSize(500, 300);


    lx::BorderImage normalBg(&display, "button.png", true, 4);
    lx::BorderImage pressedBg(&display, "button-pressed.png", true, 4);
    lx::Image content(&display, "button-content.png", true);

    lx::ScalableButtonStyle style(&normalBg, &pressedBg, &content);

    lx::ScalableButton button1(&window, &style);
    button1.setPosition(50, 50);
    button1.onClick = sayhello;

    lx::ScalableButton button2(&window, &style);
    button2.setPosition(250, 50);
    button2.onClick = sayhello;

    lx::ScalableButton button3(&window, &style);
    button3.setPosition(50, 150);
    button3.onClick = sayhello;

    lx::ScalableButton button4(&window, &style);
    button4.setPosition(250, 150);
    button4.onClick = sayhello;


    lx::MainLoop mainLoop(&display);
    mainLoop.run();
}
