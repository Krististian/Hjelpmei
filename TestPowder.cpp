#include "TestPowder.h"

int getGridWidth(){return grid.at(0).size();}
int getGridHeight(){return grid.size();}

void printSteps(FallingPowder p){
    int velocity = p.getVel();
    int acceleration = p.getAcc();
    int y_position = p.getPosition().y;
    cout << "Powder current velocity:" << velocity << endl;
    velocity += acceleration;
    y_position += velocity*powH;        //burde hatt trycatch her.
    cout << "Powder next position if fall:" << y_position;
}


void dropPowderOnFloor(){
    cout << "simulationg floor and falling snow particle" << endl;
    vector<Powder> floor;                                           //Linked list?
    floor.reserve(10);
    for (int i=1; i < 10; i++){          
        floor.push_back({gridToScreen({i, 60})});               //Fuck the Destructor man!
    }   
    cout << "Are powder still in floor?" << endl;
    for (int i=0; i < floor.size(); i++){          //floor at grid spot 100
        cout << floor.at(i).getGridPosition().y << endl;             //Fill floor with non-falling powder
    }
    cout << "placing snow on top" << endl;
    cout << "ˇ" << endl;
    cout << ">" << grid.at(0).at(6) << endl;
    FallingPowder snow{gridToScreen({6,0})};              // snow is particle that is to be falling to floor
    cout << "something at" << snow.getGridPosition().x <<","<< snow.getGridPosition().y <<":"<<
         grid.at(snow.getGridPosition().y).at(snow.getGridPosition().x) << endl;
    cout << "^" << endl;
    int buffer = 0;                                       // Lets me count iterations
    while (true){                                         // Test does not require animation window
        int y_pos = snow.getGridPosition().y;
        cout << "snow at y-position " << y_pos << endl;
        cout << "if this is last sentence, fall crashes" << endl;
        snow.fall();                                     //INVestigate: if vel is beyond grid, and make powder land on object.
        cout << "after fall" << endl;
        cout << "It is empty under: " << snow.somethingUnder(snow.getVel()) << endl;
        cout << "have snow stopped? " << (y_pos == snow.getGridPosition().y) << endl;
        if (y_pos == snow.getGridPosition().y){            //Chech if snow stopped falling
            if (y_pos==99){
                cout << "snow reachesod ground" << endl;
                buffer +=1;
                if (buffer > 3){
                    cout << "snow must have stopped at ground" << endl;
                    return;
                }
            }else{
                cout << "snow halted at y_pos: " << y_pos << endl;
                buffer += 1;
                if (buffer > 3){
                    return;
                }
            }
        }
    }
}

void testButtons(){
    TestWindow window;
    window.wait_for_close();
}

TDT4102::AnimationWindow visiualizeGrid(){                          //Increase powder size to make this easier to see.
    double box_size = powW/2;
    cout << getGridWidth() <<", "<< getGridHeight() << endl;
    TDT4102::AnimationWindow Grid(50,50,box_size*getGridWidth(),box_size*getGridWidth(), "Grid");
    grid.at(3).at(3)=true;
    for (int i = 0; i<getGridWidth(); i++){     //iterate through rows
        for (int j = 0; j<getGridHeight(); j++){     //iterate through coloumns
            if (grid.at(j).at(i)){
                Grid.draw_rectangle(gridToScreen({i,j}),1*box_size+1,1*box_size+1, TDT4102::Color::red);    //Draw occupied spaces grey
            }else {
                Grid.draw_rectangle(gridToScreen({i,j}),1*box_size+1,1*box_size+1, TDT4102::Color::blue);    //Draw empty spaces blue
            }
            
        }
    }
    return Grid;
}

void dropPowderInGrid(){
    FallingPowder snow{gridToScreen({4,4})};
    TDT4102::AnimationWindow window = visiualizeGrid();
    TDT4102::Button nxt_stp{{window.width()-60,0}, 58, 20, "skp"};
    window.add(nxt_stp);
    int xPosition = 0;
    int stopPowder = 0;                         //Until i fixed fall out of edge
    while(!window.should_close()) {
        if (stopPowder<4){
            snow.fall();
            stopPowder+=1;
        }
        window.draw_rectangle(snow.getPosition(), powW, powH);
        window.next_frame();
    }
}

//This is a bit absurd
TestWindow::TestWindow():
	// BEGIN 4a
    AnimationWindow{2,2,box_size*getGridWidth(),box_size*getGridHeight(), "Grid"}
    {
        grid.at(3).at(3)=true;
        nxt_btn.setCallback(bind(&TestWindow::cb_nxt, this));
        add(nxt_btn);
        
    }
void TestWindow::colourGridOccupy(){
    for (int i = 0; i<getGridWidth(); i++){     //iterate through rows
        for (int j = 0; j<getGridHeight(); j++){     //iterate through coloumns
            if (grid.at(j).at(i)){
                this->draw_rectangle(gridToScreen({i,j}),1*box_size+1,1*box_size+1, TDT4102::Color::red);    //Draw occupied spaces grey
            }else {
                this->draw_rectangle(gridToScreen({i,j}),1*box_size+1,1*box_size+1, TDT4102::Color::blue);    //Draw empty spaces blue
            }
            
        }
    }
}
void TestWindow::cb_nxt(){
    close();
    //cout << "skip button was clicked" << endl;
}

void vectorTester(){
    cout << "Testing of filling and emptying the vector fallingpowders:" << endl;
    /*Each time a powder is created it must be added to the vector FallingPowders*/
    FallingPowder snow{gridToScreen({5,5})};
    snow.occupyVector();
    cout << "After inserting one powder, size of vector is: " << FallingPowder::getVecLen() << endl;
    FallingPowder rain_drop{gridToScreen({5,3})};
    rain_drop.occupyVector();
    cout << "After inserting two powder, size of vector is: " << FallingPowder::getVecLen() << endl;
    cout << "snow place in vector is: " << FallingPowder::givePowderFromVector(0).getRoomNumber() << ", while raindrop place in vector is: "  //First of, Why does destructor get called
         << FallingPowder::givePowderFromVector(1).getRoomNumber() << endl;                                                                   //Second. Im such an idiot
    cout << "snow place in vector is: " << FallingPowder::givePowderFromVector(0).getRoomNumber() << ", while raindrop place in vector is: "  //First of, Why does destructor get called
    << FallingPowder::givePowderFromVector(1).getRoomNumber() << endl;     
    cout << "to properly test the leave function we make vector of 6 snow-flakes, and delete middle one and see what happens" << endl;
    for (int i=0; i<6; i++){
        FallingPowder snowflake{gridToScreen({5,5+i})};
        snowflake.occupyVector();
    }
    FallingPowder::givePowderFromVector(3).leaveVector();
    for (int i=0; i<FallingPowder::getVecLen(); i++){
        cout << "snowflake in position" << i << "has room number " << FallingPowder::givePowderFromVector(i).getRoomNumber() << endl;
    }
    cout << "vector is suddenly this long: " << FallingPowder::getVecLen() << endl;

    /*conclusion: To sucsessfully use the vector of falling powder, i must first make object, and then add object to vector. To remove, i must simply 
        use leaveVector function on the right element in the vector.*/

}
void dropSeveralPowders(){
    cout << "to test several powder dropping i will make floor, and simulate dropping" << endl;
    Powder floor{gridToScreen({5,50})};      //This will probably destruct anytime
    floor.occupyGrid();
    for (int i=0; i<40; i++){
        cout << "iterate through falling powders and do action.. mostly falling" << endl;
        for (int j=0; j<FallingPowder::getVecLen(); j++){
            FallingPowder snow = FallingPowder::givePowderFromVector(j);                  //IT MUST BE A REFERENCE. The deleting is unbearable 
            snow.fall();
            FallingPowder::givePowderFromVector(j) = snow; 
        }
        if (i==4){
            cout << "spawn snowflake at height y=10" << endl;
            FallingPowder snowflake({5,10});
            snowflake.setVel(0);
            snowflake.occupyVector();
        }
        cout << i << " seconds have passed." << endl;
    }
    cout << "to examine can be to check which grid is occupied" << endl;
}