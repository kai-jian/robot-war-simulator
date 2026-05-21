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

#include "robot.h"
#include "simulation.h"
#include "utils.h"
#include <fstream>
#include <iostream>

using namespace std;

int main() {
    ofstream logFile("battle_log.txt"); //openfile
    if (!logFile) {
        cerr << "Failed to create log file" << endl;
        return 1;
    }

    streambuf* originalCout = cout.rdbuf(logFile.rdbuf()); //redirected cout into the txt file

    cout << "--- ROBOT BATTLE START!!! ---" << endl;
    cout << "Loading battle configuration..." << endl;

    Simulation sim = loadSimulationFromFile("simulation.txt"); //load simulation data from file
    sim.run(); //run simulation

    cout << "--- BATTLE END! ---" << endl;

    cout.rdbuf(originalCout);
    return 0;
}