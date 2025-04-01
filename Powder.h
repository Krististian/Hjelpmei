#pragma once

#include "std_lib_facilities.h"
#include "window.h"

static constexpr int powH = 10;                             // Denne kjemer litt ann på screen size. Men eg vil ikkje ha screen ting her. 
static constexpr int powW = powH;

//inline var eit tips frå claude. Første bruk av AI.
inline std::vector<std::vector<bool>> grid(Wheight/powH,vector<bool>(Wwidth/powW,false)); //Kjeme veldig ann på screen size. 

TDT4102::Point screenToGrid(TDT4102::Point screen_position);
TDT4102::Point gridToScreen(TDT4102::Point grid_position);

class Powder {
    public:
    Powder(TDT4102::Point position);
    ~Powder(){cout << "powder destructor called" << endl;}
    void occupyGrid(); //I must also leave grid But can do this at every new frame...
    void leaveGrid();                                                        //Must be used after chech and before move
    TDT4102::Point getPosition() const {return gridToScreen(grid_position);} //Screen position
    TDT4102::Point getGridPosition() const {return grid_position;}     //Should override operation here
    

    protected:
    TDT4102::Point grid_position; //Is it fine to define a little bit in header? 
                                        //Kan eg stole på at denne endrer seg når position endrer seg? Vil position endre seg når denne endrer seg? Neppe.
    //Should i include pointer to Grid?
};

class FallingPowder : public Powder{
    public:
    FallingPowder(TDT4102::Point position); //+ one overload
    ~FallingPowder();       //Kanksje peikaren vil slette seg sjølv?
    //static std::vector<FallingPowder> all_falling_powder;
    int somethingUnder(const int stepsize);
    void fall();

    // should exist for all usable types
    static int getVecLen(){
        return vec_len;
    }
    static void adjustVecLen(int change){
        vec_len += change;
    }
    FallingPowder getPowder(){return *this;}
    int getRoomNumber(){return room_number;}  //Could remove this->
    void setRoomNumber(int room_number);
    inline static void insertToVector(FallingPowder p) {        // If it works then it works right?
        FallingPowder::adjustVecLen(1);
        p.setRoomNumber(FallingPowder::getVecLen()-1);
        FallingPowders.push_back(p);
    }
    void occupyVector(){insertToVector(*this);}
    static void removeFromVector(FallingPowder p);
    void leaveVector(){removeFromVector(*this);}
    static FallingPowder givePowderFromVector(int room_num){return FallingPowder::FallingPowders.at(room_num);} //dangerous, can adjust powder
    

                                  //Inline løyse alt!

    //For testing
    void setVel(int vel){velocity = vel;}
    double getVel() const {return velocity;}
    double getAcc() const {return acceleration;}

    private:
    inline static vector<FallingPowder> FallingPowders;
    inline static int vec_len;                    // keeps track of vector size. Should be set to vector size in start of game.
    int room_number;                                //Keeps track of powder place in vector.
    double velocity;
    static constexpr double acceleration = 2;
};

//std::vector<FallingPowder*> FallPowders;