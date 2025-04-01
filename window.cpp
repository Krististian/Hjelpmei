#include "window.h"


Window::Window(TDT4102::Point position, const std::string& title):
	// BEGIN 4a
    AnimationWindow{position.x, position.y, Wwidth, Wheight, title}
    {

    }

MenuWindow::MenuWindow(TDT4102::Point position, const std::string& title):
    Window{position, title}, //Er dette nødvendig?
    blankBtn{{(Wwidth-btW)/2,welc}, btW, btH, "Start blank"},
    loadBtn{{(Wwidth-btW)/2,welc+2*(btH+pad)}, btW, btH, "Load Game"},
    quitBtn{{(Wwidth-btW)/2,welc+4*(btH+pad)}, btW, btH, "Quit"}
{
    add(blankBtn);
    add(loadBtn);
    add(quitBtn);
}

GameWindow::GameWindow(TDT4102::Point position, const std::string& title):
    Window{position, title},
    menuBtn{{Wwidth-btW-pad,pad}, btW, btH, "Quit"}
    {
    add(menuBtn);
    //menuBtn.setCallback(std::bind(Window::cb_quit(),this));
    }

void Window::cb_quit(){
    close();
}

void Window::cb_blank(){
    std::cout << "new game started" << std::endl;
}

void Window::cb_load(){
    std::cout << "open load game" << std::endl;
}