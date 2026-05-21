// *********************************************************
// Program: simulation.h
// Course: CCP6124 OOPDS
// Lecture Class: TC3L
// Tutorial Class: T12L
// Trimester: 2510
// Member_1: 242UC244PJ | LIM YI DE | LIM.YI.DE@sutdent.mmu.edu.my | 011-5982 6980
// Member_2: 242UC244SE | LIM REN LIANG | LIM.REN.LIANG@student.mmu.edu.my | 016-713 0425
// Member_3: 242UC244PG | TOH KAI JIAN | TOH.KAI.JIAN@student.mmu.edu.my | 012-479 2988
// Member_4: 242UC244F6 | WONG LEI | WONG.LEI@student.mmu.edu.my | 016-794 3908
// *********************************************************

#ifndef SIMULATION_H
#define SIMULATION_H

#include "battlefield.h"
#include <vector>
#include <memory>
#include <queue>

using namespace std;

class Simulation {
private:
    Battlefield battlefield;
    vector<unique_ptr<Robot>> robots;
    queue<unique_ptr<Robot>> respawnQueue;
    int turns;
    void findRandomPosition(int& x, int& y);
    void processRespawns();
    void queueDestroyedRobots();
    void prepareRespawn(Robot* destroyedRobot);
    void respawnNextRobot();
    void shuffleRobots();
    void processTurns();
    int countAliveRobots() const;
    void printResults();
    void groupRobotsByName(map<string, vector<Robot*>>& groups);
    void printRobotSummary(const string& name, const vector<Robot*>& versions);
    Robot* getLatestVersion(const vector<Robot*>& versions) const;
    string getTypeName(char symbol) const;    
public:
    Simulation(int m, int n, int turns);
    void addRobot(unique_ptr<Robot> robot, int x, int y);
    void run();
};

#endif // SIMULATION_H