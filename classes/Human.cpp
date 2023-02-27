
#include <random>
#include <algorithm>
#include "../headers/Human.h"
#include "../headers/GameSpecs.h"
#include "../headers/City.h"

//constructor
Human::Human(City *city, int width, int height) : Organism(city, width,
                                                           height) {

    this->city = city;
    this->width = width;
    this->height = height;
    this->species = _GAMESPECS_H::HUMAN_CH;
}

//destructor
Human::~Human() {

    this->city = nullptr;
}

//function to check if the human has moved yet, if not, call move and checkAllyCreation
void Human::turn() {

    if (!moved) {
        move();
        checkAllyCreation();
    }
}

//function to attempt to move the human
void Human::move() {

    checkPossibleDirections();

    //verify there is possible directions to move
    if (!this->posDir.empty()) {
        shuffleDirectionOptions();
        moveDirection();
        clearTargetingOptions();
    }

    //set moved flag
    this->moved = true;
}

//function to check if the human can recruit, and increment the humans time steps
void Human::checkAllyCreation() {

    if (this->steps > _GAMESPECS_H::HUMAN_BREED) {
        createAlly();
        this->steps = 0;
        clearTargetingOptions();
    }

    this->steps++;
}

//function to check which available directions are empty
void Human::checkPossibleDirections() {

    //check north, add it to the posDir array it the human can move there
    if (this->y >= 1) {
        if (this->city->isEmpty(this->x, (this->y - 1))) {
            this->posDir.push_back(NORTH);
        }
    }

    //check south, add it to the posDir array it the human can move there
    if (this->y <= (_GAMESPECS_H::GRIDSIZE - 2)) {
        if (this->city->isEmpty(this->x, (this->y + 1))) {
            this->posDir.push_back(SOUTH);
        }
    }

    //check west, add it to the posDir array it the human can move there
    if (this->x >= 1) {
        if (this->city->isEmpty((this->x - 1), this->y)) {
            this->posDir.push_back(WEST);
        }
    }

    //check east, add it to the posDir array it the human can move there
    if (this->x <= (_GAMESPECS_H::GRIDSIZE - 2)) {
        if (this->city->isEmpty((this->x + 1), this->y)) {
            this->posDir.push_back(EAST);
        }
    }
}

//function to shuffle the potential directions to avoid movement bias
void Human::shuffleDirectionOptions() {

    unsigned seed = chrono::system_clock::now().
            time_since_epoch().count();//create random seed using system clock

    std::shuffle(this->posDir.begin(), this->posDir.end(),
                 default_random_engine(seed));
}

//function to move in a given direction
void Human::moveDirection() {

    //move in the direction of the first location in the posDir array
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
        default:
            break;
    }
}

//function to check if space is available to create an ally
void Human::createAlly() {

    checkPossibleDirections();
    if (!this->posDir.empty()) {
        shuffleDirectionOptions();
        recruit();
    }
}

//function to create an ally in an empty space
void Human::recruit() {

    //create a human in the first location of the posDir array
    switch (this->posDir[0]) {
        case NORTH:
            city->createHuman(this->x, (this->y - 1));
            break;
        case EAST:
            city->createHuman((this->x + 1), this->y);
            break;
        case SOUTH:
            city->createHuman(this->x, (this->y + 1));
            break;
        case WEST:
            city->createHuman((this->x - 1), this->y);
            break;
        default:
            break;
    }
}

//function to clear the posDir vector
void Human::clearTargetingOptions() {

    if (!this->posDir.empty()) {
        this->posDir.clear();
    }
}






