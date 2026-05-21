// *********************************************************
// Program: simulation.cpp
// Course: CCP6124 OOPDS
// Lecture Class: TC3L
// Tutorial Class: T12L
// Trimester: 2510
// Member_1: 242UC244PJ | LIM YI DE | LIM.YI.DE@sutdent.mmu.edu.my | 011-5982 6980
// Member_2: 242UC244SE | LIM REN LIANG | LIM.REN.LIANG@student.mmu.edu.my | 016-713 0425
// Member_3: 242UC244PG | TOH KAI JIAN | TOH.KAI.JIAN@student.mmu.edu.my | 012-479 2988
// Member_4: 242UC244F6 | WONG LEI | WONG.LEI@student.mmu.edu.my | 016-794 3908
// *********************************************************

#include "simulation.h"
#include "generic_robot.h"
#include <algorithm>
#include <random>
#include <iostream>
#include <map>
#include <ctime>

using namespace std;


Simulation::Simulation(int m, int n, int turns) 
    : battlefield(m, n), turns(turns) { // initialize the size and turn of battlefield
    srand(time(nullptr)); // random number generator for random position
}

void Simulation::addRobot(unique_ptr<Robot> robot, int x, int y) {
    if (x == -1 && y == -1) {
        findRandomPosition(x, y); // find a random empty position in battlefield for robot
    }
    battlefield.placeRobot(robot.get(), x, y); // place the robot in the postion given
    robots.push_back(move(robot)); // store the robot into simulation vector
}

void Simulation::findRandomPosition(int& x, int& y) {
    do {
        int maxX = battlefield.getWidth();
        int maxY = battlefield.getHeight();

        x = rand() % maxX; // generate a random position x in battlefield
        y = rand() % maxY; // generate a random position y in battlefield

    } while (battlefield.checkRobotPresence(x, y)); // ensure the position generated does not has robot
}

void Simulation::run() {
    cout << "Starting simulation with " << robots.size() << " robots" << endl ; // print the number of robot in the battlefield
    
    for (int i = 0; i < turns && countAliveRobots() > 1; i++) { // run the simulation until the turns given and there is only one robot alive in the battlefield
        cout << endl <<"--- Turn " << i + 1 << " ---" << endl; // print the number of current turn
        
        processRespawns(); 
        shuffleRobots();
        processTurns();
        
        battlefield.display();
    }
    
    cout << endl << "--- Simulation Complete ---" << endl;
    printResults();
}

void Simulation::processRespawns() { // define processRespawns function
    queueDestroyedRobots(); // add robot that is waiting for respawn into respawn queue
    
    if (!respawnQueue.empty()) { // if the respawn queue is not empty
        respawnNextRobot(); // respawn the next robot in the respawn queue
    }
}

void Simulation::queueDestroyedRobots() { // define queueDestroyedRobots function
    for (auto& robot : robots) {
        if (!robot->isAlive() && robot->respawnCount < 3 && !robot->inQueue) { // is robot is destruyed and the robot respawn count id less than 3 and the robot isn't the respawn queue
            prepareRespawn(robot.get()); // add the robot in the respawn queue
        }
    }
}

void Simulation::prepareRespawn(Robot* destroyedRobot) { // define prepareRespawn function
    destroyedRobot->inQueue = true; // mark the destroyed robot is in the respawn queue
    unique_ptr<GenericRobot> newRobot = make_unique<GenericRobot>( // generate a new robot in order to respawn
        destroyedRobot->getName(), -1, -1); // get the name of robot and set the position as (-1,-1)
    newRobot->respawnCount = destroyedRobot->respawnCount + 1; // increase the respawn count for the new robot
    respawnQueue.push(move(newRobot)); // add the new robot into respawn queue
}

void Simulation::respawnNextRobot() { // define respawnNextRobot function
    unique_ptr<Robot> robotToRespawn = move(respawnQueue.front()); // move the front robot out of the queue
    respawnQueue.pop(); // remove the robot from the queue
    
    int x, y;
    findRandomPosition(x, y); // find a random position in battlefield
    
    cout << robotToRespawn->getName() << "HAHA! I am back and respawned at ("
            << x << "," << y << ") (Attempt #" 
            << robotToRespawn->respawnCount << ")" << endl; // print out the name, position and number of being respawn of the robot
            
    addRobot(move(robotToRespawn), x, y); // add the robot back to simulation at the given position
}

void Simulation::shuffleRobots() { // define shuffleRobots function
    // Original: shuffle(robots.begin(), robots.end(), default_random_engine(rand()));
    for (size_t i = 0; i < robots.size(); ++i) { // 
        size_t j = i + rand() % (robots.size() - i); // get a random index
        
        //swap the position of i and j
        Robot* temp = robots[i].release(); // release robot at i 
        robots[i].reset(robots[j].release()); // reset robot at i to robot at j
        robots[j].reset(temp); // reset robot at j to original robot at i
    }
}


void Simulation::processTurns() { // define processTurns function
    for (unique_ptr<Robot>& robot : robots) {
        if (robot->isAlive()) {
            int beforeX = robot->getpositionX(); // get the initial position of x of the robot
            int beforeY = robot->getpositionY(); // get the initial position of y of the robot
            cout << robot->getName() << " at (" << beforeX << "," << beforeY << ") begins action.\n";
            
            robot->act(battlefield); // call the robot action
            
            int afterX = robot->getpositionX(); // get the new position of x of the robot after the action
            int afterY = robot->getpositionY(); // get the new position of y of the robot after the action
            cout << robot->getName() << " ended action at (" << afterX << "," << afterY << ").\n";
        }
    }
}

int Simulation::countAliveRobots() const { // define countAliveRobots function
    int aliveCount = 0; // initialize the number of alive robot

    for (size_t i = 0; i < robots.size(); ++i) { // add the number of alive robot if the robot is still alive until the end of the robot list
        if (robots[i]->isAlive()) {
            aliveCount++;
        }
    }

    return aliveCount;
}


void Simulation::printResults() { // define the function of printResults function
    cout << endl << "Final Standings:" << endl;
    cout << "----------------\n";
    
    map<string, vector<Robot*>> robotGroups; // create a map to group robots
    groupRobotsByName(robotGroups); // group the robots according to the name or type
    
    for (const pair<const string, vector<Robot*>>& pair : robotGroups) { // print the summary of robot in the group
        printRobotSummary(pair.first, pair.second); // print summary for each robot group
    }
}

void Simulation::groupRobotsByName(map<string, vector<Robot*>>& groups) { // define groupRobotsByName function
    for (size_t i = 0; i < robots.size(); ++i) {
        Robot* r = robots[i].get(); // get the pointer to the robot
        string name = r->getName(); // get the name of robot

        if (groups.find(name) == groups.end()) { // check whether the name of robot exist in the group or not
            groups[name] = vector<Robot*>(); // if not create a new vector
        }

        groups[name].push_back(r); // add the robot to the group
    }
}

void Simulation::printRobotSummary(const string& name, const vector<Robot*>& versions) { // define prontRobotSummary function
    Robot* latest = getLatestVersion(versions); // get the latest version of the robot

    string typeName;
    char symbol = latest->getSymbol();
    if (symbol == 'G') {
        typeName = "GenericRobot";
    } else if (symbol == 'j') {
        typeName = "JumpBot";
    } else if (symbol == 'h' || symbol == 'H') {
        typeName = "HideBot";
    } else if (symbol == 'l') {
        typeName = "LongShotBot";
    } else if (symbol == 's') {
        typeName = "SemiAutoBot";
    } else if (symbol == 't') {
        typeName = "ThirtyShotBot";
    } else if (symbol == 'c') {
        typeName = "ScoutBot";
    } else if (symbol == 'k') {
        typeName = "TrackBot";
    } else if (symbol == 'A') {
        typeName = "ArmorBot";
    } else if (symbol == 'E') {
        typeName = "HealthBot";
    } else if (symbol == 'C') {
        typeName = "CarBot";
    } else {
        typeName = "Unknown (" + string(1, symbol) + ")";
    }

    string status; // determine the status of the robot
    if (latest->isAlive()) {
        status = "Alive";
    } else {
        status = "Destroyed";
    }

    int livesUsed = latest->respawnCount; // determine the number of live used
    if (!latest->isAlive() && livesUsed < 3) {
        livesUsed += 1; // Adjust for final death
    }

    cout << name << ": " << status << " as " << typeName
         << " (" << symbol << ") | Lives used: " << livesUsed << endl;
}

Robot* Simulation::getLatestVersion(const vector<Robot*>& versions) const { // define getLatestVersion function
    Robot* latest = versions[0]; // set the initial version of the robot as the latest version
    for (Robot* r : versions) { // loop all the version of the robot
        if (r->respawnCount > latest->respawnCount) { //compare respawnCount to get the highest respawn count of the robot
            latest = r; // update the latest version of the robot
        }
    }
    return latest;
}

string Simulation::getTypeName(char symbol) const { // define getTypeName function
    string typeName;

    if (symbol == 'G') {
        typeName = "GenericRobot";
    } else if (symbol == 'j') {
        typeName = "JumpBot";
    } else if (symbol == 'h') {
        typeName = "HideBot";
    } else if (symbol == 'H') {
        typeName = "HideBot";
    } else if (symbol == 'l') {
        typeName = "LongShotBot";
    } else if (symbol == 's') {
        typeName = "SemiAutoBot";
    } else if (symbol == 't') {
        typeName = "ThirtyShotBot";
    } else if (symbol == 'c') {
        typeName = "ScoutBot";
    } else if (symbol == 'k') {
        typeName = "TrackBot";
    } else if (symbol == 'A') {
        typeName = "ArmorBot";
    } else if (symbol == 'E') {
        typeName = "HealthBot";
    } else if (symbol == 'C') {
        typeName = "CarBot";
    } else {
        typeName = "Unknown (" + string(1, symbol) + ")";
    }

    return typeName;
}