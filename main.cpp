//
// Created by W0068332 on 11/21/2021.
//
//Example main.cpp
//This supposes that city->step() calls the move method of each organism in the city
//in a single pass causing each to perform all tasks that it can.

#include <iostream>
#include <chrono>
#include <thread>
#include "headers/Organism.h"
#include "headers/City.h"
#include "headers/GameSpecs.h"

using namespace std;

void ClearScreen()
{
    cout << flush;
    system ("CLS");
}

int main() {
    City *city = new City();
    city->populate();
    chrono:: milliseconds interval((int)(_GAMESPECS_H::PAUSE_SECONDS * 1000));

    while (city->hasDiversity()) { //while both humans and zombies exist
        this_thread::sleep_for(interval);
        ClearScreen();
        city->move(); //includes all actions
        city->reset(); //resets moved flags
        cout << *city; //prints city
        cout << "GENERATION " << city->getGeneration() << endl;
        cout << "HUMANS: " << city->getHumanCount() << endl;
        cout << "ZOMBIES: " << city->getZombieCount() << endl;
    }
    delete city;
}

