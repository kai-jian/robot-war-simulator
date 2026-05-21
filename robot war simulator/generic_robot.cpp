// *********************************************************
// Program: generic_robot.cpp
// Course: CCP6124 OOPDS
// Lecture Class: TC3L
// Tutorial Class: T12L
// Trimester: 2510
// Member_1: 242UC244PJ | LIM YI DE | LIM.YI.DE@sutdent.mmu.edu.my | 011-5982 6980
// Member_2: 242UC244SE | LIM REN LIANG | LIM.REN.LIANG@student.mmu.edu.my | 016-713 0425
// Member_3: 242UC244PG | TOH KAI JIAN | TOH.KAI.JIAN@student.mmu.edu.my | 012-479 2988
// Member_4: 242UC244F6 | WONG LEI | WONG.LEI@student.mmu.edu.my | 016-794 3908
// *********************************************************

#include "generic_robot.h"
#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;
//Base bot
GenericRobot::GenericRobot(string name, int x, int y) 
    : Robot(name, x, y, 'G'), bullet(10), upgradeCount(0),
      hasMovementUpgrade(false), hasAttackUpgrade(false), hasVisionUpgrade(false) {}

void GenericRobot::acting() {
    cout << name << " is acting like thinking..." << endl;
}

void GenericRobot::act(Battlefield& battlefield) {
    acting();
    
    if (bullet > 0 && rand() % 2 == 0) { // 50%change to attack 
        int dx = (rand() % 3); 
        dx = dx - 1; // position of x (-1,0,1)
        int dy = (rand() % 3);
        dy = dy - 1; // position of y (-1,0,1)
        if (dx != 0 || dy != 0) { //means that it can attack the 8 places surrounding
            attack(battlefield, dx, dy);
        }
    } else {
        moveRandomly(battlefield); //it can move randomly in 8 places surrounding 
    }
    
    checkForUpgrades(); //there has 10% chance to upgrade weapons movement and vision
}

void GenericRobot::attack(Battlefield& battlefield, int dx, int dy) {
    if (bullet <= 0) { 
        cout << name << " no bullet! gg!!" << endl; //if bullet is 0 it will cout
        return;
    }
    
    int targetX = getpositionX() + dx; //get the target position
    int targetY = getpositionY() + dy; //get the target position
    
    if (!battlefield.checkPositionValidation(targetX, targetY)) return; //if the target is invalid position and it will stop
    
    Robot* target = battlefield.getRobotType(targetX, targetY); // get the robot at the target position
    if (target && target != this) { //make sure is target and not itself
        cout << name << " fires at " << target->getName() << endl;
        attackProgress(target); //check is the attack is miss or not
        
        if (!target->isAlive()) {  //if target die
            battlefield.removeRobot(targetX, targetY); //remove it form the battlefield
        }
        bullet--; //discard one bullet
    }
}

void GenericRobot::attackProgress(Robot* target) {
    int shots = getMaxBullet();
    for (int i = 0; i < shots; i++) { //shoot one bullet only
        if (rand() % 100 < getHitProbability() * 100) { //the percentage that will hit the enemy
            target->takeDamage(); //give damage to enemy
            cout << "Hits! " << target->getName() << " deal thousand damage!!" << endl;
        } else {
            cout << "wc ! Miss!" << endl;
        }
    }
}

//move random in 8 places surrounding
void GenericRobot::moveRandomly(Battlefield& battlefield) { 
    int dx = (rand() % 3) - 1;
    int dy = (rand() % 3) - 1;
    int newX = getpositionX() + dx;
    int newY = getpositionY() + dy;
    battlefield.moveRobot(this, newX, newY);
}

//check can upgrade or not
void GenericRobot::checkForUpgrades() {
    if (rand() % 10 == 0) { // 10% chance
        vector<string> upgradeOptions;
        //check which upgrade that robot dont hace
        if (!hasMovementUpgrade) {
            upgradeOptions.push_back("movement");
        }
        if (!hasAttackUpgrade) {
            upgradeOptions.push_back("attack");
        }
        if (!hasVisionUpgrade) {
            upgradeOptions.push_back("vision");
        }

        if (upgradeOptions.size() > 0) { //pick a random upgrade 
            int randomIndex = rand() % upgradeOptions.size();
            string chosenUpgrade = upgradeOptions[randomIndex];

            applyUpgrade(chosenUpgrade); //applies the upgrade means that make it upgrade
        }
    }
}
    
void GenericRobot::applyUpgrade(string type) { 
    if (upgradeCount >= 3) return; // make the upgrade changes max is 3
    
    upgradeCount++; //upgrade changes ade one
    if (type == "movement") {
        upgradeMovement(); 
    } else if (type == "attack") {
        upgradeAttack();
    } else if (type == "vision") {
        upgradeVision();
    }
}

//upgrade movement to HideBot and JumpBot
void GenericRobot::upgradeMovement() {
    hasMovementUpgrade = true;
    cout << name << " upgraded movement!NOW I CAN RUN!!!!" << endl;
    int typeRoll = rand() % 2;
    if (typeRoll == 0) {
        symbol = 'h';  // HideBot
    } else {
        symbol = 'j';  // JumpBot
    }
}

//upgrade attack to LongShotBot,SemiAutoBot and ThirtyShotBot
void GenericRobot::upgradeAttack() {
    hasAttackUpgrade = true;
    cout << name << " upgraded weapons! NEW WEAPON!!" << endl;
    int roll = rand() % 3;
    if (roll == 0) {
        symbol = 'l';  // LongShotBot
    } else if (roll == 1) {
        symbol = 's';  // SemiAutoBot
    } else {
        symbol = 't';  // ThirtyShotBot
        bullet = 30;   // Load up 30 bullets!
    }
}

//upgrade version to ScoutBot and TrackBot
void GenericRobot::upgradeVision() {
    hasVisionUpgrade = true;
    cout << name << " upgraded sensors! WOW NICE VISION!!" << endl;
    int typeRoll = rand() % 2;
    if (typeRoll == 0) {
        symbol = 'c';  // ScoutBot
    } else {
        symbol = 'k';  // TrackBot
    }
}

//it has a 33% to hide
bool HideBot::hideProbability() const {
    if (hideTimes > 0 && rand() % 3 == 0) {
        return true;
    } else {
        return false;
    }
}

//active the hide
void HideBot::activateHide() {
    setHidden(true);
    hideTimes--; //changes of hide mines 1
    cout << name << " haha i'm hidding!" << endl;
}    

//constructor
HideBot::HideBot(string name, int x, int y) 
    : GenericRobot(name, x, y), hideTimes(3) {
    symbol = 'h';
}

//using attack ,move or hide
void HideBot::act(Battlefield& battlefield) {
    if (hideProbability()) {
        activateHide();
    } else {
        GenericRobot::act(battlefield);
    }
}    

//there has 25% to successful jump
bool JumpBot::jumpProbability() const {
    return jumpTimes > 0 && rand() % 4 == 0;
}

//active the jump function
void JumpBot::activateJump(Battlefield& battlefield) {
    int newX, newY; //new position
    findValidJumpPosition(battlefield, newX, newY); //find the jump position is valid
    
    battlefield.moveRobot(this, newX, newY); //move the robot to a new position 
    jumpTimes--; //discarde one changes of jumping
    cout << name << "HAHA! I can jump to (" << newX << "," << newY << ")! and byebye losers!" << endl;
}
    
//find the valid positioin that in match 
void JumpBot::findValidJumpPosition(Battlefield& battlefield, int& x, int& y) {
    do {
        x = rand() % battlefield.getWidth();
        y = rand() % battlefield.getHeight();
    } while (battlefield.checkRobotPresence(x, y));
}

//constructor
JumpBot::JumpBot(string name, int x, int y) 
    : GenericRobot(name, x, y), jumpTimes(3) {
    symbol = 'j';
}

//using jump,attack or move
void JumpBot::act(Battlefield& battlefield) {
    if (jumpProbability()) {
        activateJump(battlefield);
    } else {
        GenericRobot::act(battlefield);
    }
}

//constructor
LongShotBot::LongShotBot(string name, int x, int y) 
    : GenericRobot(name, x, y) {
    symbol = 'l';
}

//make the Robot can shoot mostly far from 3 places in the battlefield
bool LongShotBot::shootAbility(int x, int y) const {
    int dx = abs(x - getpositionX());
    int dy = abs(y - getpositionY());
    return (dx + dy <= 3) && !(dx == 0 && dy == 0);
}




//constructor
SemiAutoBot::SemiAutoBot(string name, int x, int y) 
    : GenericRobot(name, x, y) {
    symbol = 's';
}

int SemiAutoBot::getMaxBullet() const{ 
    return 3; // Three shots per attack
}

//it has extra bullet
ThirtyShotBot::ThirtyShotBot(string name, int x, int y) 
    : GenericRobot(name, x, y) {
    symbol = 't';
    bullet = 30; // Extra ammo capacity
}


// there has 20% changes to using scout
bool ScoutBot::scoutProbability() const {
    return scoutTimes > 0 && rand() % 5 == 0;
}    

//constructor
ScoutBot::ScoutBot(string name, int x, int y) 
    : GenericRobot(name, x, y), scoutTimes(3) {
    symbol = 'c';
}

//can see the enemy or has scout changes
bool ScoutBot::seeAbility(int x, int y) const {
    return scoutTimes > 0 || GenericRobot::seeAbility(x, y); //scout changes more than 1 and can see the 3*3surrounding
}

//using scout or move or attack
void ScoutBot::act(Battlefield& battlefield) {
    if (scoutProbability()) {
        scoutTimes--;
        cout << name << " You guys cannot run!!! I can find u ~" << endl;
    }
    GenericRobot::act(battlefield);
}

//have 20% to put a track
bool TrackBot::PlaceTrackerProbability() const {
    return trackers > 0 && rand() % 5 == 0;
}

//
void TrackBot::placeTracker(Battlefield& battlefield) {
    for (int y = 0; y < battlefield.getHeight(); y++) {
        for (int x = 0; x < battlefield.getWidth(); x++) {
            Robot* target = battlefield.getRobotType(x, y); //get the pointer at position of the robot
            if (abilityPlaceTrackerOn(target, x, y)) {
                trackRobot(x, y);//marks the position
                trackers--;//track changes discard one 
                cout << name << " tagged " << target->getName() << "!\n";
                return;
            }
        }
    }
}

//returns if the robot and the tracker can see
bool TrackBot::abilityPlaceTrackerOn(Robot* target, int x, int y) const {
    return target && target != this && seeAbility(x, y);
}    

//constructor
TrackBot::TrackBot(string name, int x, int y) 
    : GenericRobot(name, x, y), trackers(3) {
    symbol = 'k';
}

//using track ,attack or move
void TrackBot::act(Battlefield& battlefield) {
    if (PlaceTrackerProbability()) {
        placeTracker(battlefield);
    }
    GenericRobot::act(battlefield);
}

//trackbot can see the places that place track before
bool TrackBot::seeAbility(int x, int y) const {
    return GenericRobot::seeAbility(x, y) || isTracking(x, y);
}

