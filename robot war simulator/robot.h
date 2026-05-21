// *********************************************************
// Program: robot.h
// Course: CCP6124 OOPDS
// Lecture Class: TC3L
// Tutorial Class: T12L
// Trimester: 2510
// Member_1: 242UC244PJ | LIM YI DE | LIM.YI.DE@sutdent.mmu.edu.my | 011-5982 6980
// Member_2: 242UC244SE | LIM REN LIANG | LIM.REN.LIANG@student.mmu.edu.my | 016-713 0425
// Member_3: 242UC244PG | TOH KAI JIAN | TOH.KAI.JIAN@student.mmu.edu.my | 012-479 2988
// Member_4: 242UC244F6 | WONG LEI | WONG.LEI@student.mmu.edu.my | 016-794 3908
// *********************************************************

#ifndef ROBOT_H
#define ROBOT_H

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <map>

using namespace std;

class Battlefield;

class Robot {
protected:
    string name; //robot name
    int positionX, positionY; //position
    int lives; //lives of robot
    bool hidden; // HideBot function
    char symbol; //robot symbol
    map<pair<int, int>, bool> trackedRobots; // a map for track to TrackBot
    
public:
    Robot(string name, int x, int y, char sym); //constructor
    virtual ~Robot() = default; //destructor
    
    virtual void acting() = 0; //means that must be implement to all class 
    virtual void act(Battlefield& battlefield) = 0; //means that must be implement to all class 
    
    virtual void takeDamage(); //mines the lives of robot
    
    char getSymbol() const; //return robot's symbol
    string getName() const; //return name
    bool isAlive() const; // check is the robot is allive
    int getpositionX() const; // return position
    int getpositionY() const; //return position
    int getLivesRemaining() const; //returns robot live left
    
    void setHidden(bool hide); //set robot is it hide or visible
    void setPosition(int x, int y); // set the position
    
    virtual bool seeAbility(int x, int y) const; //check if robot can see target
    virtual bool shootAbility(int x, int y) const; //check if the robot can shoot the target position 
    virtual int getMaxBullet() const; // returns max bullet that can robot has
    virtual float getHitProbability() const; // returns the hit and miss probability
    
    void trackRobot(int x, int y); //it will marks robot
    bool isTracking(int x, int y) const; //check is it tracking
    
    int respawnCount = 0; //respawen how many time
    bool inQueue = false;// respawn queue
};

#endif // ROBOT_H