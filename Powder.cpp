#include "Powder.h"

TDT4102::Point screenToGrid(TDT4102::Point screen_position){
    return {screen_position.x/powW, screen_position.y/powH};
}
TDT4102::Point gridToScreen(TDT4102::Point grid_position){
    return {grid_position.x*powW, grid_position.y*powH};
}



Powder::Powder(TDT4102::Point screen_position): grid_position{screenToGrid(screen_position)}{
    occupyGrid();             //Its okay if it is only filled with pointers.
}

FallingPowder::FallingPowder(TDT4102::Point position): Powder(position){
    //all_falling_powder.push_back(*this);
    //velocity = 0; //vil barn også gjere dette?        //If i want this, i need to change the copy constructor
    //FallPowders.push_back(this);
}

FallingPowder::~FallingPowder(){
    //all_falling_powder.erase(std::remove(all_falling_powder.begin(), all_falling_powder.end(), this), all_falling_powder.end());    //Dette går treigt
};

void Powder::occupyGrid(){
    try{
        if (!(grid.at(grid_position.y).at(grid_position.x))){
            cout << "occupy (" << grid_position.x << "," << grid_position.y <<")" << endl;
            grid.at(grid_position.y).at(grid_position.x) = true;
        } else{throw 505;}
    }
    catch(int errorcode){
        cout << "Warning: particle is being placed into already occupied grid-space" << endl;
    }
}

void Powder::leaveGrid(){
    try{
        if (grid.at(grid_position.y).at(grid_position.x)){
            cout << "deoccupy!" << endl;
            grid.at(grid_position.y).at(grid_position.x) = false;
        } else{throw 505;}
    }
    catch(int errorcode){
        cout << "Warning: particle not occupying grid is being removed from grid" << endl;
    }
    

}

int FallingPowder::somethingUnder(const int stepsize){                          //Should cast same way as y+=vel
    for(int i=1; i<=stepsize; i++ ){
        std::cout << "next position: " << getGridPosition().y+i << std::endl;
        std::cout << "grid size: " << grid.size() << std::endl;
        if (getGridPosition().y+i>=grid.size()) {
            cout<<"OB"<<endl;
            return -1;}                     //returns -1 if fallen out of grid
        if (grid.at(getGridPosition().y+i).at(getGridPosition().x)){return i;}   
    }
    return 0;                                                                   //returns 0 if nothing under
}

void FallingPowder::fall(){
    cout << "current grid position: " << grid_position.y << std::endl;
    cout << "velocity: " << velocity <<  endl;
    velocity += acceleration;
    cout << "velocity: " << velocity <<  endl;
    int obsticle = somethingUnder(velocity);
    std::cout << "obsticle: " << obsticle << std::endl;
    if (!obsticle){
        std::cout << "it was empty under" << std::endl;
        leaveGrid();
        grid_position.y += velocity;        //burde hatt trycatch her.
        std::cout << "new grid y-pos: " << grid_position.y << std::endl;
        std::cout << "new speed: " << velocity << std::endl;
        occupyGrid();
    }else if(obsticle == -1){
        leaveGrid();
        this->~FallingPowder();
    }else if(obsticle == 1){}
    else{
        leaveGrid();
        grid_position.y+obsticle-1;
        occupyGrid();
        velocity = 0;
    }
}

void FallingPowder::removeFromVector(FallingPowder p){
    FallingPowder::adjustVecLen(-1);
    //following method should be faster than erase. Also veclen should never be zero here
    //Basicly swaps out the current powder with the last one and then remove the last one in the vector
    try{
        if (FallingPowders.empty()){
            throw("empty vector");
        }else{
            FallingPowders.back().setRoomNumber(p.getRoomNumber());
            FallingPowders.at(p.getRoomNumber())=FallingPowders.back();
            FallingPowders.pop_back();
        }
    }
    catch(string errorcode) {
        cout << errorcode << endl;
    }
    p.setRoomNumber(-1);
}

void FallingPowder::setRoomNumber(int room_num){
    room_number=room_num;
}
