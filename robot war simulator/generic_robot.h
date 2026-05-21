// *********************************************************
// Program: generic_robot.h
// Course: CCP6124 OOPDS
// Lecture Class: TC3L
// Tutorial Class: T12L
// Trimester: 2510
// Member_1: 242UC244PJ | LIM YI DE | LIM.YI.DE@sutdent.mmu.edu.my | 011-5982 6980
// Member_2: 242UC244SE | LIM REN LIANG | LIM.REN.LIANG@student.mmu.edu.my | 016-713 0425
// Member_3: 242UC244PG | TOH KAI JIAN | TOH.KAI.JIAN@student.mmu.edu.my | 012-479 2988
// Member_4: 242UC244F6 | WONG LEI | WONG.LEI@student.mmu.edu.my | 016-794 3908
// *********************************************************

#ifndef GENERIC_ROBOT_H
#define GENERIC_ROBOT_H

#include "robot.h"
#include "battlefield.h"
using namespace std;


//base robot
class GenericRobot : public Robot {
protected:
    int bullet; //set bullet
    int upgradeCount; //set the upgrade changes
    bool hasMovementUpgrade, hasAttackUpgrade, hasVisionUpgrade; //is the robot upgrade?
    
public:
    GenericRobot(string name, int x, int y); //constructor
    
    void acting() override; //more like thinking
    void act(Battlefield& battlefield) override; //choose is moving or doing attack 
    
    void attack(Battlefield& battlefield, int dx, int dy); //attack the enemy
    void attackProgress(Robot* target); //check if the attack is miss or hit the enemy(cause have )
    void moveRandomly(Battlefield& battlefield); //make the robot can move random 
    void checkForUpgrades(); //check is the robot can upgrade 
    void applyUpgrade(string type); // apply upgrade to movement,attack and vision
    
    void upgradeMovement(); 
    void upgradeAttack();
    void upgradeVision();
};

//Hidebot
class HideBot : public GenericRobot {
private:
    int hideTimes; //turns that can hide
    bool hideProbability() const; //it have 33% to hidden
    void activateHide();  //mark the robot is hidden
public:
    HideBot(string name, int x, int y); //constructor
    void act(Battlefield& battlefield) override; //using hide or move or attack
};


//Jumpbot
class JumpBot : public GenericRobot {
private:
    int jumpTimes; //changes to jump
    bool jumpProbability() const; //there has 25% to jump
    void activateJump(Battlefield& battlefield); //jump to another destination
    void findValidJumpPosition(Battlefield& battlefield, int& x, int& y); //find the valid position thats mean that no robot and valid in battlefield
public:
    JumpBot(string name, int x, int y); //constructor
    void act(Battlefield& battlefield) override;//using jump,attack or move
};

//longshotbot
class LongShotBot : public GenericRobot {
public:
    LongShotBot(string name, int x, int y); //constructor
    bool shootAbility(int x, int y) const override; // it can shoot the enemy or the robot that far from 3 places 
};

//semiautobot
class SemiAutoBot : public GenericRobot {
public:
    SemiAutoBot(string name, int x, int y); //constructor
    int getMaxBullet() const override; //it can shoot the robot 3 times per turns
};

//
class ThirtyShotBot : public GenericRobot {
public:
    ThirtyShotBot(string name, int x, int y); //constructor
};

class ScoutBot : public GenericRobot {
private:
    int scoutTimes; //changes of scout
    bool scoutProbability() const; //20% to scout
    
public:
    ScoutBot(string name, int x, int y); //constructor
    bool seeAbility(int x, int y) const override; //can see a target if has change
    void act(Battlefield& battlefield) override; //scout , move or attack
};

class TrackBot : public GenericRobot {
private:
    int trackers; //how many tracks
    bool PlaceTrackerProbability() const; //20% to put the track
    void placeTracker(Battlefield& battlefield); //place a track on a enemy 
    bool abilityPlaceTrackerOn(Robot* target, int x, int y) const; //return if others robot and trackbots can see

public:
    TrackBot(string name, int x, int y); //constructor
    void act(Battlefield& battlefield) override; //place track, attack,move
    bool seeAbility(int x, int y) const override; //trackbot can see the places that place track before

};


#endif // GENERIC_ROBOT_H