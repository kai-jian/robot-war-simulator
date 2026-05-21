// *********************************************************
// Program: battlefield.h
// Course: CCP6124 OOPDS
// Lecture Class: TC3L
// Tutorial Class: T12L
// Trimester: 2510
// Member_1: 242UC244PJ | LIM YI DE | LIM.YI.DE@sutdent.mmu.edu.my | 011-5982 6980
// Member_2: 242UC244SE | LIM REN LIANG | LIM.REN.LIANG@student.mmu.edu.my | 016-713 0425
// Member_3: 242UC244PG | TOH KAI JIAN | TOH.KAI.JIAN@student.mmu.edu.my | 012-479 2988
// Member_4: 242UC244F6 | WONG LEI | WONG.LEI@student.mmu.edu.my | 016-794 3908
// *********************************************************

#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H

#include "robot.h"
#include <vector>

using namespace std;

class Battlefield {
private:
    int width, height; //setheight and width
    vector<vector<Robot*>> grid; //2d map
    
public:
    Battlefield(int m, int n); //constructor
    
    int getWidth() const; 
    int getHeight() const;
    
    bool checkPositionValidation(int x, int y) const; //check is valid position 
    bool checkRobotPresence(int x, int y) const; // is the robot on the places
    
    void placeRobot(Robot* robot, int x, int y); 
    void moveRobot(Robot* robot, int newpositionX, int newpositionY);
    void removeRobot(int x, int y);
    Robot* getRobotType(int x, int y) const; //get robot places.if np robot return nullptr
    
    void display() const;
};

#endif // BATTLEFIELD_H