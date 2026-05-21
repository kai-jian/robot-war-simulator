// *********************************************************
// Program: special_robots.cpp
// Course: CCP6124 OOPDS
// Lecture Class: TC3L
// Tutorial Class: T12L
// Trimester: 2510
// Member_1: 242UC244PJ | LIM YI DE | LIM.YI.DE@sutdent.mmu.edu.my | 011-5982 6980
// Member_2: 242UC244SE | LIM REN LIANG | LIM.REN.LIANG@student.mmu.edu.my | 016-713 0425
// Member_3: 242UC244PG | TOH KAI JIAN | TOH.KAI.JIAN@student.mmu.edu.my | 012-479 2988
// Member_4: 242UC244F6 | WONG LEI | WONG.LEI@student.mmu.edu.my | 016-794 3908
// *********************************************************

#include "special_robots.h"
#include <iostream>
#include <cstdlib>

using namespace std;

bool ArmorBot::Isusingarmor() const { //return if the armor more than one means that still have armor can use
    return armor > 0;
}

void ArmorBot :: UsingArmor(Battlefield& battlefield){ //using armor
    if(armor > 0){
        armor -- ; //armor changes mines one
        cout << "armor defend damage!!!"; //cout when there has an armor
    }else{
        cout << "armor finish!"; //cout when the armor changes is 0 means that already finishi
    }
};

//wallk this is the same movement as the random movement on the robot.cpp
void ArmorBot :: walk(Battlefield& battlefield){
    int Gx = rand() % 3;//(0,1,2)
    Gx = Gx - 1;// position x will(-1,0,1)

    int Gy = rand() % 3;// (0,1,2)
    Gy = Gy - 1;// position y will (-1, 0 ,1)
    battlefield.moveRobot(this,getpositionX() + Gx, getpositionY() + Gy); //it can move the rbot to the new poosition
};

ArmorBot :: ArmorBot (string name,int x, int y)//construcctor
    : Robot(name, x, y, 'A'), armor(3){};

void ArmorBot :: acting(){ //thinking
    cout << name << " blink!" << endl;
};

//using armor,move and attack
void ArmorBot :: act(Battlefield& battlefield){
    acting(); //thinkings

    if(Isusingarmor()){ //if armor left using armor
        UsingArmor(battlefield); //used the armor
    }
    else{
        walk(battlefield); //walk 
    }
};

//returns if still have healthbag
bool HealthBot :: Isusinghealth() const {
    return healthbag > 0 ;
};

//use when the health is less tahn 3.it will discard 1 healthbag and inccrease the lives
void HealthBot :: usingHealth(Battlefield& battlefield){
    if(lives < 3){ //if the robot lives less than 3
        healthbag -- ; //the healthbag discard one 
        cout << "healthbag used dedengdedeng!!!" << endl;
        lives ++ ;//the lives become full
    }else{
        cout << name << "your health is full" << endl; //cout when your health is full
    }
}

//walk as a random 8places surround
void HealthBot :: walk(Battlefield& battlefield){
    int Gx = rand() % 3;
    Gx = Gx - 1; //random x

    int Gy = rand() % 3;
    Gy = Gy - 1; //random y
    battlefield.moveRobot(this,getpositionX() + Gx, getpositionY() + Gy); //move the robot
};

//constructor
HealthBot :: HealthBot (string name,int x, int y)
    : Robot(name, x, y, 'E'), healthbag(1){};

//thinking
void HealthBot :: acting(){
    cout << name << " blink!" << endl;
};

//thinks is using aromor ,move or attack
void HealthBot :: act(Battlefield& battlefield){
    acting(); //thinking

    if(Isusinghealth()){ // if the healthbag still have
        usingHealth(battlefield); // using the healthbag
    }else{
        walk(battlefield); //move or walk
    }
};


//select the direction of the car means that left right up and down only
void CarBot :: selectDirectionCar(int& Gx, int& Gy){
    int direction = rand() % 4; // direction has 25% of each direction

    if (direction == 0) {
        Gx = 1; Gy = 0;  // Right
    } else if (direction == 1) {
        Gx = -1; Gy = 0; // Left
    } else if (direction == 2) {
        Gx = 0; Gy = 1;  // Down
    } else {
        Gx = 0; Gy = -1; // Up
    }
}

//walk straight and kill the enemy when it same position with them
void CarBot :: walkstraight(Battlefield& battlefield){
    int Gx = 0;
    int Gy = 0;
    selectDirectionCar(Gx,Gy);
    int newGx = getpositionX() + Gx;
    int newGy = getpositionY() + Gy;

    if(!battlefield.checkPositionValidation(newGx,newGy)){  //using it when you reach the end of the battlefield mean that no valid position
        cout << "pls reverse, you have reach the dead ends"<< endl;
        return;
    }

    //check if the target is in the places or not
    Robot* target = battlefield.getRobotType(newGx,newGy);
        if (target && target != this){ //check if there is a valid target and not itself
            cout << "crashed " << target->getName() << "and bomb!!" << endl; //it will crashhed!!! the enemy
            battlefield.removeRobot(newGx,newGy); //it can remove the robot means that kill the robot
            battlefield.moveRobot(this,newGx,newGy);//move the robot to the new places
            takeDamage(); //it will takedamage when crashed the enemy
        }

        battlefield.moveRobot(this,newGx,newGy);//move the robot to the new places
        cout << "gogogo and go to (" << newGx << "," << newGy << ") " ;
        
    }

//constructor
CarBot :: CarBot(string name, int x , int y)
    : Robot(name, x , y , 'C'){}

//thinking
void CarBot :: acting(){
    cout << name << "Wonk!" << endl;
};

//thinking is walk or walk hahahaha
void CarBot :: act(Battlefield& battlefield){
    acting();
    walkstraight(battlefield); //walk function means that walk unti meet the same position with enmey and walk and kill them
};
