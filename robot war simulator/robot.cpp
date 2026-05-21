// *********************************************************
// Program: robot.cpp
// Course: CCP6124 OOPDS
// Lecture Class: TC3L
// Tutorial Class: T12L
// Trimester: 2510
// Member_1: 242UC244PJ | LIM YI DE | LIM.YI.DE@sutdent.mmu.edu.my | 011-5982 6980
// Member_2: 242UC244SE | LIM REN LIANG | LIM.REN.LIANG@student.mmu.edu.my | 016-713 0425
// Member_3: 242UC244PG | TOH KAI JIAN | TOH.KAI.JIAN@student.mmu.edu.my | 012-479 2988
// Member_4: 242UC244F6 | WONG LEI | WONG.LEI@student.mmu.edu.my | 016-794 3908
// *********************************************************

#include "robot.h"
#include "battlefield.h"

using namespace std;

Robot::Robot(string name, int x, int y, char sym)  //constructor
    : name(name), positionX(x), positionY(y), lives(3), hidden(false), symbol(sym) {}

void Robot::takeDamage() { //deal damage if the enemy not hidden
    if (!hidden) {
        lives--;
    }
}

char Robot::getSymbol() const { return hidden ? 'H' : symbol; } //show H if it is hidden
string Robot::getName() const { return name; } //return name
bool Robot::isAlive() const { return lives > 0; } //if the robot more than 0 hp is alive
int Robot::getpositionX() const { return positionX; } // return position
int Robot::getpositionY() const { return positionY; }// return position
int Robot::getLivesRemaining() const { return lives; } //returns robot live left

void Robot::setHidden(bool hide) { hidden = hide; } //set robot is it hide or visible
void Robot::setPosition(int x, int y) { positionX = x; positionY = y; }// set the position

bool Robot::seeAbility(int x, int y) const {
    return abs(x - positionX) <= 1 && abs(y - positionY) <= 1; //means that it can see the 3*3area for the vision
}

bool Robot::shootAbility(int x, int y) const { 
    return abs(x - positionX) <= 1 && abs(y - positionY) <= 1 && !(x == positionX && y == positionY); //means that can shoot 3*3 area but cannot shoot itself
}

int Robot::getMaxBullet() const { return 1; } //1 bullet per attack
float Robot::getHitProbability() const { return 0.7f; } // 70%of changes to hit the enemy

void Robot::trackRobot(int x, int y) { // track a robot positioin
    trackedRobots[{x, y}] = true;
}

bool Robot::isTracking(int x, int y) const { //check is anyone being track
    return trackedRobots.count({x, y}) > 0;
}