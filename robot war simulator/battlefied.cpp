// *********************************************************
// Program: battlefield.cpp
// Course: CCP6124 OOPDS
// Lecture Class: TC3L
// Tutorial Class: T12L
// Trimester: 2510
// Member_1: 242UC244PJ | LIM YI DE | LIM.YI.DE@sutdent.mmu.edu.my | 011-5982 6980
// Member_2: 242UC244SE | LIM REN LIANG | LIM.REN.LIANG@student.mmu.edu.my | 016-713 0425
// Member_3: 242UC244PG | TOH KAI JIAN | TOH.KAI.JIAN@student.mmu.edu.my | 012-479 2988
// Member_4: 242UC244F6 | WONG LEI | WONG.LEI@student.mmu.edu.my | 016-794 3908
// *********************************************************

#include "battlefield.h"
#include <iostream>

using namespace std;

//create 2 d vector of grid (width = rows,height = column)
Battlefield::Battlefield(int m, int n) : width(m), height(n) {
    grid.clear(); //clear the grid to avoid theres has a grid before
    for (int i = 0; i < width; ++i) {  //each loops create one row of grid
        vector<Robot*> row; 
        for (int j = 0; j < height; ++j) {
            row.push_back(nullptr); //fill in the row with the nullptr
        }
        grid.push_back(row); 
    }
}

//get the height and the column
int Battlefield::getWidth() const { 
    return width; 
    }
int Battlefield::getHeight() const { 
    return height; 
    }


//check the positions makesure the positions in it
bool Battlefield::checkPositionValidation(int x, int y) const {
    if ((x >= 0 && x < width) && (y >= 0 && y < height)) {
        return true;
    } else {
        return false;
    };
}

//check robot places and if no robot give the nullptr means that nothing at there
bool Battlefield::checkRobotPresence(int x, int y) const {
    if (checkPositionValidation(x, y) && grid[x][y] != nullptr) {
        return true;
    } else {
        return false;
    };
}

//put the robot in the valid places 
void Battlefield::placeRobot(Robot* robot, int x, int y) {
    if (checkPositionValidation(x, y)) {
        grid[x][y] = robot; //store the robot in the grid
        robot->setPosition(x, y); //tells the robot where should it is
    }
}

//change the robot places
void Battlefield::moveRobot(Robot* robot, int newpositionX, int newpositionY) {
    if (checkPositionValidation(newpositionX, newpositionY) && !checkRobotPresence(newpositionX, newpositionY)) { //make sure that no robot and places is valid
        grid[robot->getpositionX()][robot->getpositionY()] = nullptr; //clears the robot position to nullptr
        grid[newpositionX][newpositionY] = robot; //place the robot in a new position
        robot->setPosition(newpositionX, newpositionY); //update the robot's new position
    }
}

//remove robot when the robot die
void Battlefield::removeRobot(int x, int y) {
    if (checkPositionValidation(x, y)) {
        grid[x][y] = nullptr;  //turns the set of pointer in this grid to nullptr(delete it)
    }
}

// check is the places got a robot or not
Robot* Battlefield::getRobotType(int x, int y) const {
    if (checkPositionValidation(x, y)) {
        return grid[x][y]; //return what it store might be robot or be a nullptr
    }
    return nullptr;
}


//use for display the battlefield
void Battlefield::display() const {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (grid[x][y] != nullptr) {
                cout << grid[x][y]->getSymbol() << " "; //show the symmbol of the robot if it has robot pointer at the places
            } else {
                cout << ". "; //other from the robot means that nullptr show the . as a empty places
            }
        }
        cout << endl;
    }
}
