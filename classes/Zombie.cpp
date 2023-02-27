//
// Created by samsi on 2022-12-03.
//

#include <random>
#include <algorithm>
#include "../headers/Zombie.h"
#include "../headers/GameSpecs.h"
#include "../headers/City.h"




//default constructor


//constructor
Zombie::Zombie(City *city, int width, int height)
        : Organism(city, width, height) {

    this->city = city;
    this->width = width;
    this->height = height;
    this->species = _GAMESPECS_H::ZOMBIE_CH;

}

//destructor
Zombie::~Zombie() {

    this->city = nullptr;
}

//function to check if the zombie has moved yet, if not,
// call move, checkAllyCreation, and checkStarving
void Zombie::turn() {

    if (!moved) {
        move();
        checkAllyCreation();
        checkForStarving();
    }
}

//function to attempt to move the zombie
void Zombie::move() {

    checkPossibleDirections();
    if (!this->humansNear.empty()) {
        shuffleEatOptions();
        eat();
        this->stepsWithoutFood = 0;
    } else if (!this->posDir.empty()) {
        shuffleDirectionOptions();
        moveDirection();
        this->stepsWithoutFood++;
    } else {
        this->stepsWithoutFood++;
    }
    clearTargetingOptions();
    this->moved = true;

}

//function to check if the zombie can breed,
// and increment the humans time steps
void Zombie::checkAllyCreation() {

    if (this->steps > _GAMESPECS_H::ZOMBIE_BREED) {
        createAlly();
        clearTargetingOptions();
    }
    this->steps++;
}

//function to check which available directions are empty,
// and which ones have humans in them
void Zombie::checkPossibleDirections() {

    //check north
    if (this->y >= 1) {

        //if its empty add it to the posDir array
        if (this->city->isEmpty(this->x, (this->y - 1))) {
            this->posDir.push_back(NORTH);
        }
            //else if it's a human add it to the humansNear array
        else if (this->city->getOrganism(this->x, (this->y - 1))->
                getSpecies() == _GAMESPECS_H::HUMAN_CH) {

            this->humansNear.push_back(NORTH);
        }
    }

    //check south
    if (this->y <= (_GAMESPECS_H::GRIDSIZE - 2)) {

        //if its empty add it to the posDir array
        if (this->city->isEmpty(this->x, (this->y + 1))) {
            this->posDir.push_back(SOUTH);
        }
            //else if it's a human add it to the humansNear array
        else if (this->city->getOrganism(this->x, (this->y + 1))->
                getSpecies() == _GAMESPECS_H::HUMAN_CH) {

            this->humansNear.push_back(SOUTH);
        }
    }

    //check west
    if (this->x >= 1) {

        //if its empty add it to the posDir array
        if (this->city->isEmpty((this->x - 1), this->y)) {
            this->posDir.push_back(WEST);
        }
            //else if it's a human add it to the humansNear array
        else if (this->city->getOrganism((this->x - 1), this->y)->
                getSpecies() == _GAMESPECS_H::HUMAN_CH) {

            this->humansNear.push_back(WEST);
        }
    }

    //check east
    if (this->x <= (_GAMESPECS_H::GRIDSIZE - 2)) {

        //if its empty add it to the posDir array
        if (this->city->isEmpty((this->x + 1), this->y)) {
            this->posDir.push_back(EAST);
        }
            //else if it's a human add it to the humansNear array
        else if (this->city->getOrganism((this->x + 1), this->y)->
                getSpecies() == _GAMESPECS_H::HUMAN_CH) {

            this->humansNear.push_back(EAST);
        }
    }

    //check north-east
    if (this->x <= (_GAMESPECS_H::GRIDSIZE - 2) && this->y >= 1) {

        //if its empty add it to the posDir array
        if (this->city->isEmpty((this->x + 1), (this->y - 1))) {
            this->posDir.push_back(NEAST);
        }
            //else if it's a human add it to the humansNear array
        else if (this->city->getOrganism((this->x + 1), (this->y - 1))->
                getSpecies() == _GAMESPECS_H::HUMAN_CH) {
            this->humansNear.push_back(NEAST);
        }
    }

    //check north-west
    if (this->x >= 1 && this->y >= 1) {

        //if its empty add it to the posDir array
        if (this->city->isEmpty((this->x - 1), (this->y - 1))) {
            this->posDir.push_back(NWEST);
        }
            //else if it's a human add it to the humansNear array
        else if (this->city->getOrganism((this->x - 1), (this->y - 1))->
                getSpecies() == _GAMESPECS_H::HUMAN_CH) {

            this->humansNear.push_back(NWEST);
        }
    }

    //check south-east
    if (this->x <= (_GAMESPECS_H::GRIDSIZE - 2) &&
        this->y <= (_GAMESPECS_H::GRIDSIZE - 2)) {

        //if its empty add it to the posDir array
        if (this->city->isEmpty((this->x + 1), (this->y + 1))) {
            this->posDir.push_back(SEAST);
        }
            //else if it's a human add it to the humansNear array
        else if (this->city->getOrganism((this->x + 1), (this->y + 1))->
                getSpecies() == _GAMESPECS_H::HUMAN_CH) {

            this->humansNear.push_back(SEAST);
        }
    }

    //check south-west
    if (this->x >= 1 && this->y <= (_GAMESPECS_H::GRIDSIZE - 2)) {

        //if its empty add it to the posDir array
        if (this->city->isEmpty((this->x - 1), (this->y + 1))) {
            this->posDir.push_back(SWEST);
        }
            //else if it's a human add it to the humansNear array
        else if (this->city->getOrganism((this->x - 1), (this->y + 1))->
                getSpecies() == _GAMESPECS_H::HUMAN_CH) {

            this->humansNear.push_back(SWEST);
        }
    }
}

//function to shuffle the potential directions to move in to avoid movement bias
void Zombie::shuffleDirectionOptions() {

    //create random seed using system clock
    unsigned seed = chrono::system_clock::now()
            .time_since_epoch().count();

    std::shuffle(this->posDir.begin(), this->posDir.end(),
                 default_random_engine(seed));
}

//function to shuffle the potential directions to eat/breed in to avoid movement bias
void Zombie::shuffleEatOptions() {

    unsigned seed = chrono::system_clock::now().time_since_epoch().count();//create random seed using system clock
    std::shuffle(this->humansNear.begin(), this->humansNear.end(),
                 default_random_engine(seed));
}

//function to move in a given direction
void Zombie::moveDirection() {

    //function to move to the first location in posDir
    switch (this->posDir[0]) {
        case NORTH:
            city->moveOrganism(this, this->x, (this->y - 1));
            break;
        case EAST:
            city->moveOrganism(this, (this->x + 1), this->y);
            break;
        case SOUTH:
            city->moveOrganism(this, this->x, (this->y + 1));
            break;
        case WEST:
            city->moveOrganism(this, (this->x - 1), this->y);
            break;
        case NEAST:
            city->moveOrganism(this, (this->x + 1), (this->y - 1));
            break;
        case NWEST:
            city->moveOrganism(this, (this->x - 1), (this->y - 1));
            break;
        case SEAST:
            city->moveOrganism(this, (this->x + 1), (this->y + 1));
            break;
        case SWEST:
            city->moveOrganism(this, (this->x - 1), (this->y + 1));
            break;
        default:
            break;
    }
}

//function to eat in a given direction
void Zombie::eat() {

    //function to eat the human at the first location in humansNear
    switch (this->humansNear[0]) {
        case NORTH:
            city->consumeHuman(this, this->x, (this->y - 1));
            break;
        case EAST:
            city->consumeHuman(this, (this->x + 1), this->y);
            break;
        case SOUTH:
            city->consumeHuman(this, this->x, (this->y + 1));
            break;
        case WEST:
            city->consumeHuman(this, (this->x - 1), this->y);
            break;
        case NEAST:
            city->consumeHuman(this, (this->x + 1), (this->y - 1));
            break;
        case NWEST:
            city->consumeHuman(this, (this->x - 1), (this->y - 1));
            break;
        case SEAST:
            city->consumeHuman(this, (this->x + 1), (this->y + 1));
            break;
        case SWEST:
            city->consumeHuman(this, (this->x - 1), (this->y + 1));
            break;
        default:
            break;
    }
}

//function to clear the posDir and humansNear vectors
void Zombie::clearTargetingOptions() {

    if (!this->posDir.empty()) {
        this->posDir.erase(posDir.begin(), posDir.end());
    }

    if (!this->humansNear.empty()) {
        this->humansNear.erase(humansNear.begin(), humansNear.end());
    }

}

//function to check if there is a human near to create an ally
void Zombie::createAlly() {

    checkPossibleDirections();

    if (!humansNear.empty()) {
        breed();
        this->steps = 0;
    }
}

//function to create an ally in a space where a human is
void ::Zombie::breed() {

    //make a new zombie at the location of the first humansNear
    switch (this->humansNear[0]) {
        case NORTH:
            city->replaceHumanForZombie(this->x, (this->y - 1));
            break;
        case EAST:
            city->replaceHumanForZombie((this->x + 1), this->y);
            break;
        case SOUTH:
            city->replaceHumanForZombie(this->x, (this->y + 1));
            break;
        case WEST:
            city->replaceHumanForZombie((this->x - 1), this->y);
            break;
        case NEAST:
            city->replaceHumanForZombie((this->x + 1), (this->y - 1));
            break;
        case NWEST:
            city->replaceHumanForZombie((this->x - 1), (this->y - 1));
            break;
        case SEAST:
            city->replaceHumanForZombie((this->x + 1), (this->y + 1));
            break;
        case SWEST:
            city->replaceHumanForZombie((this->x - 1), (this->y + 1));
            break;
        default:
            break;
    }
}

//function to check if zombie has gone too many turns without eating
void ::Zombie::checkForStarving() {

    if (stepsWithoutFood >= _GAMESPECS_H::ZOMBIE_STARVE) {
        starve();
    }
}

//function to call for the zombie to be turned back into a human
void Zombie::starve() {

    city->replaceZombieForHuman(this->x, this->y);
}

