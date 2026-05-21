// *********************************************************
// Program: utils.cpp
// Course: CCP6124 OOPDS
// Lecture Class: TC3L
// Tutorial Class: T12L
// Trimester: 2510
// Member_1: 242UC244PJ | LIM YI DE | LIM.YI.DE@sutdent.mmu.edu.my | 011-5982 6980
// Member_2: 242UC244SE | LIM REN LIANG | LIM.REN.LIANG@student.mmu.edu.my | 016-713 0425
// Member_3: 242UC244PG | TOH KAI JIAN | TOH.KAI.JIAN@student.mmu.edu.my | 012-479 2988
// Member_4: 242UC244F6 | WONG LEI | WONG.LEI@student.mmu.edu.my | 016-794 3908
// *********************************************************\

#include "utils.h"
#include "generic_robot.h"
#include "special_robots.h"
#include <sstream>
#include <iostream>

using namespace std;

// Forward declaration for createRobot function
unique_ptr<Robot> createRobot(const string& type, const string& name, int x, int y);


Simulation loadSimulationFromFile(const string& filename) {
    ifstream file(filename); //open file
    if (!file.is_open()) { //if file couldnt open use this
        cerr << "Failed to open simulation file: " << filename << endl;
        exit(1);
    }

    string line; 
    getline(file, line); //read first line into a string line 
    size_t colon = line.find(":"); //find the position of ":"
    string dimensionStr = line.substr(colon + 1); //take the message after the colon
    istringstream dimStream(dimensionStr); //turns the string into a stream
    int width, height; 
    dimStream >> width >> height; //read the width and height

    getline(file, line);
    colon = line.find(":"); //read the number of simulation steps from the second line
    string stepsStr = line.substr(colon + 1);
    int steps = atoi(stepsStr.c_str());

    getline(file, line); //read the number robot from line 3
    colon = line.find(":");
    string robotCountStr = line.substr(colon + 1);
    int robotCount = atoi(robotCountStr.c_str());

    Simulation sim(width, height, steps); 

    for (int i = 0; i < robotCount; ++i) { //if no more line are available, break it
        if (!getline(file, line)) {
            break;
        }

        istringstream iss(line); //create a iss variable to store the type name and position 
        string type, name, posStr;
        int x = -1, y = -1;

        iss >> type >> name >> posStr; //read from the type name and position

        if (posStr != "random") { //if the position is not random change it to integer and pasrse the position
            x = atoi(posStr.c_str());
            iss >> y;
        }

        unique_ptr<Robot> robot(createRobot(type, name, x, y)); //create robot using createRobot function
        sim.addRobot(move(robot), x, y); //add the robot to the simulation
    }

    return sim;
}

// if type match it will show bellow
unique_ptr<Robot> createRobot(const string& type, const string& name, int x, int y) {
    if (type == "GenericRobot") {
        return make_unique<GenericRobot>(name, x, y);
    }
    if (type == "ArmorBot") {
        return make_unique<ArmorBot>(name, x, y);
    }
    if (type == "HealthBot") {
        return make_unique<HealthBot>(name, x, y);
    }
    if (type == "CarBot") {
        return make_unique<CarBot>(name, x, y);
    }
    if (type == "HideBot") {
        return make_unique<HideBot>(name, x, y);
    }
    if (type == "JumpBot") {
        return make_unique<JumpBot>(name, x, y);
    }
    if (type == "LongShotBot") {
        return make_unique<LongShotBot>(name, x, y);
    }
    if (type == "SemiAutoBot") {
        return make_unique<SemiAutoBot>(name, x, y);
    }
    if (type == "ThirtyShotBot") {
        return make_unique<ThirtyShotBot>(name, x, y);
    }
    if (type == "ScoutBot") {
        return make_unique<ScoutBot>(name, x, y);
    }
    if (type == "TrackBot") {
        return make_unique<TrackBot>(name, x, y);
    }
    cerr << "Unknown robot type: " << type << endl;
    exit(1);
}


void logOutput(ofstream& logFile, const string& message) { //it will write the same message to the log file
    cout << message << endl;
    logFile << message << endl;
}