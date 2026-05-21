// *********************************************************
// Program: utils.h
// Course: CCP6124 OOPDS
// Lecture Class: TC3L
// Tutorial Class: T12L
// Trimester: 2510
// Member_1: 242UC244PJ | LIM YI DE | LIM.YI.DE@sutdent.mmu.edu.my | 011-5982 6980
// Member_2: 242UC244SE | LIM REN LIANG | LIM.REN.LIANG@student.mmu.edu.my | 016-713 0425
// Member_3: 242UC244PG | TOH KAI JIAN | TOH.KAI.JIAN@student.mmu.edu.my | 012-479 2988
// Member_4: 242UC244F6 | WONG LEI | WONG.LEI@student.mmu.edu.my | 016-794 3908
// *********************************************************

#ifndef UTILS_H
#define UTILS_H

#include "robot.h"
#include "simulation.h"
#include <fstream>
#include <memory>

using namespace std;

Simulation loadSimulationFromFile(const string& filename); //load the simulation from the file
unique_ptr<Robot> createRobot(const string& type, const string& name, int x, int y); //create a Robot of a specific type
void logOutput(ofstream& logFile, const string& message); //write a log message for loading the output

#endif // UTILS_H