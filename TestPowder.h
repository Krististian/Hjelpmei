#pragma once

#include "Powder.h"
#include "std_lib_facilities.h"

int getGridWidth();
int getGridHeight();

void printSteps(FallingPowder p);

void dropPowderOnFloor();

TDT4102::AnimationWindow visiualizeGrid();

void dropPowderInGrid();
void vectorTester();
void dropSeveralPowders();


class TestWindow : public TDT4102::AnimationWindow
{
    public: 
    TestWindow();
    static constexpr int box_size = powW/2;
    TDT4102::Button nxt_btn{{this->width()-60,0}, 58, 20, "skp"};
	void colourGridOccupy();
    void cb_nxt();


    
    //buttons universal for all windows
    
};

