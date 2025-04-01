#pragma once

#include "AnimationWindow.h"
#include "widgets/TextInput.h"
#include "widgets/DropdownList.h"
#include "widgets/Button.h"


#include <std_lib_facilities.h>
#include <ostream>
#include <string>
#include <vector>
#include <functional>
//Det er vanskelig å gi muligheten for valgfritt størrelse på vindauge. Dette kan prøvast å gjere seinare, men no definerer eg det her
static constexpr int Wwidth = 1000;
static constexpr int Wheight= 700;

class Window : public TDT4102::AnimationWindow
{
    public: 
    //To make it look clean all button are equal size
    static constexpr int pad = 10;
	static constexpr int btW = 200;
	static constexpr int btH = 10;
	static constexpr int fieldW = 30;
	static constexpr int fieldH = 30;



    //callbackfunctions
    void cb_blank(); //can be used for reset and new blank game
    void cb_load();
    void cb_quit();

    Window(TDT4102::Point position, const std::string& title);
};

class MenuWindow : public Window
{
    public:
    MenuWindow(TDT4102::Point position, const std::string& title);

    // Extra GUI spaces 
    static constexpr int welc = 300;
    
    //clickable buttons on the menu
    TDT4102::Button blankBtn;
    TDT4102::Button loadBtn;
    TDT4102::Button quitBtn;


    //callback functions for the buttons
    private:
};

class GameWindow : public Window
{
    public:
    GameWindow(TDT4102::Point position, const std::string& title);

    //Menu button on top right corner
    TDT4102::Button menuBtn;

    private:
};

class LoadWindow : public Window
{
    public:
    LoadWindow(TDT4102::Point position, const std::string& title);
    private:
};
