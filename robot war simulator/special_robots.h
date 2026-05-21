// *********************************************************
// Program: special_robots.h
// Course: CCP6124 OOPDS
// Lecture Class: TC3L
// Tutorial Class: T12L
// Trimester: 2510
// Member_1: 242UC244PJ | LIM YI DE | LIM.YI.DE@sutdent.mmu.edu.my | 011-5982 6980
// Member_2: 242UC244SE | LIM REN LIANG | LIM.REN.LIANG@student.mmu.edu.my | 016-713 0425
// Member_3: 242UC244PG | TOH KAI JIAN | TOH.KAI.JIAN@student.mmu.edu.my | 012-479 2988
// Member_4: 242UC244F6 | WONG LEI | WONG.LEI@student.mmu.edu.my | 016-794 3908
// *********************************************************

#ifndef SPECIAL_ROBOTS_H
#define SPECIAL_ROBOTS_H

#include "robot.h"
#include "battlefield.h"

using namespace std;

class ArmorBot : public Robot 
{
private:
    int armor; //how many armor
    bool Isusingarmor() const; //think of using armor
    void UsingArmor(Battlefield& battlefield); //using armor
    void walk(Battlefield& battlefield); // only can walk 3*3 random

public:
    ArmorBot(string name, int x,int y); //constructor
    void acting() override; //think
    void act(Battlefield& battlefield) override; //using armor or attack or move
};

class HealthBot : public Robot 
{
private:
    int healthbag; //how many healthbag
    bool Isusinghealth() const; //think of using healthbag
    void usingHealth(Battlefield& battlefield); //using healthbag
    void walk(Battlefield& battlefield); // only can move 3*3 random in battlefield

public:
    HealthBot(string name, int x, int y); //constructor
    void acting() override; //think
    void act(Battlefield& battlefield) override; // using healthbag ,attack or move
};

class CarBot : public Robot {
private:
    void selectDirectionCar(int& Gx, int& Gy);
    void walkstraight(Battlefield& battlefield); //move up down left right only random and kill the enemy that same position with it 

public:
    CarBot(string name, int x, int y); //constructor
    void acting() override; //think
    void act(Battlefield& battlefield) override;//move and attack
};
#endif
