
#include <random>
#include <windows.h>
#include "../headers/City.h"
#include "../headers/Organism.h"
#include "../headers/GameSpecs.h"
#include "../headers/Human.h"
#include "../headers/Zombie.h"

//constructors
City::City() {

    this->zombieCount = 0;
    this->humanCount = 0;
    this->generation = 0;
}

City::~City() {

    for (auto &i: grid) {
        for (auto &j: i) {
            delete j;
        }
    }
}


//getters
int City::getGeneration() { return this->generation; }


int City::getZombieCount() {
    return this->zombieCount;
}


int City::getHumanCount() {
    return this->humanCount;
}

//function to get the organism at the specific cell
Organism *City::getOrganism(int x, int y) {

    Organism *temp = this->grid[x][y];
    return temp;
}

//function to set position of an organism
void City::setOrganism(Organism *organism, int x, int y) {

    this->grid[x][y] = organism;
}

//function to check is there at least one human and zombie
bool City::hasDiversity() {

    if (this->zombieCount > 0 && this->humanCount > 0) {
        return true;
    } else {
        return false;
    }
}

//function to call the functions that populate the grid with humans and zombies
void City::populate() {

    populateHumans();
    populateZombies();
}

//function to populate the grid with humans
void City::populateHumans() {

    //create randomizer
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist20(0, 19);

    //populate humans
    for (int i = 0; i < _GAMESPECS_H::HUMAN_STARTCOUNT; i++) {
        int xPos = dist20(rng);
        int yPos = dist20(rng);
        while (true) {
            if (!isEmpty(xPos, yPos)) {
                xPos = dist20(rng);
                yPos = dist20(rng);
            } else {
                createHuman(xPos, yPos);
                break;
            }
        }
    }
}

//function to populate the grid with zombies
void City::populateZombies() {

    //create randomizer
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist9(0, 9);
    std::uniform_int_distribution<std::mt19937::result_type> dist19(10, 19);

    //populate zombies by evenly distributing them into each quadrant
    for (int i = 0; i < _GAMESPECS_H::ZOMBIE_STARTCOUNT; i++) {
        int j = i;
        int xPos;
        int yPos;
        while (j >= 4) { j -= 4; }
        while (true) {
            switch (j) {
                case 0:
                    xPos = dist9(rng);
                    yPos = dist9(rng);
                    break;
                case 1:
                    xPos = dist9(rng);
                    yPos = dist19(rng);
                    break;
                case 2:
                    xPos = dist19(rng);
                    yPos = dist9(rng);
                    break;
                case 3:
                    xPos = dist19(rng);
                    yPos = dist19(rng);
                    break;
            }
            if (isEmpty(xPos, yPos)) {
                createZombie(xPos, yPos);
                break;
            }
        }
    }
}

//function to reset the move flags on the humans and zombies
void City::reset() {

    for (int i = 0; i < GRID_HEIGHT; i++) {
        for (int j = 0; j < GRID_WIDTH; j++) {
            if (!this->isEmpty(i, j)) {
                getOrganism(i, j)->endTurn();
            }
        }
    }
}

//function to change the color output of the console
void City::col(int c) {

    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, c);
}

//function to move organism in city and nullify old position
void City::moveOrganism(Organism *organism, int x, int y) {

    int tempX = organism->getx();
    int tempY = organism->gety();
    this->grid[x][y] = organism;
    this->grid[tempX][tempY] = nullptr;
    organism->setx(x);
    organism->sety(y);
}

//function to check if a specific cell is empty
bool City::isEmpty(int xPos, int yPos) {

    if (this->grid[xPos][yPos] == nullptr) {
        return true;
    } else {
        return false;
    }
}

//function to call each organism's turn function and increase the generation
void City::move() {

    this->generation++;
    for (int i = 0; i < GRID_HEIGHT; i++) {
        for (int j = 0; j < GRID_HEIGHT; j++) {
            if (!this->isEmpty(i, j)) {
                getOrganism(i, j)->turn();
            }
        }
    }
}

//function to delete a human and move a zombie the humans position
void City::consumeHuman(Organism *organism, int x, int y) {

    delete getOrganism(x, y);
    this->grid[x][y] = nullptr;
    this->moveOrganism(organism, x, y);
    this->humanCount--;
}

//function to create a human and add it to the grid in a given cell location
void City::createHuman(int xPos, int yPos) {

    Human *human = new Human(this, 1, 1);
    human->setPosition(xPos, yPos);
    this->setOrganism(human, xPos, yPos);
    this->humanCount++;
}

//function to create a zombie and add it to the grid in a given cell location
void City::createZombie(int xPos, int yPos) {

    Zombie *zombie = new Zombie(this, 1, 1);
    zombie->setPosition(xPos, yPos);
    this->setOrganism(zombie, xPos, yPos);
    this->zombieCount++;
}

//function to replace a zombie with a human in the same cell
void City::replaceZombieForHuman(int x, int y) {

    delete getOrganism(x, y);
    this->grid[x][y] = nullptr;
    createHuman(x, y);
    this->zombieCount--;
}

//function to replace a human with a zombie in the same cell
void City::replaceHumanForZombie(int x, int y) {

    delete getOrganism(x, y);
    this->grid[x][y] = nullptr;
    createZombie(x, y);
    this->humanCount--;
}

//overriding the << operator
ostream &operator<<(ostream &output, City &city) {

    output << "GENERATION: " << city.generation << endl;

    //place the horizontal wall on top of grind
    output << "----------------------" << endl;

    for (int i = 0; i < GRID_HEIGHT; i++) {

        //place the vertical wall on left edge of grid
        output << "|";
        for (int j = 0; j < GRID_WIDTH; j++) {

            //if no organism at the location, print empty space
            if (city.isEmpty(i, j)) {
                output << (char) _GAMESPECS_H::SPACE_CH;
            }
                // if it's a human print the human character
            else if (city.getOrganism(i, j)->
                    getSpecies() == _GAMESPECS_H::HUMAN_CH) {

                city.col(_GAMESPECS_H::HUMAN_COLOR);
                output << (char) _GAMESPECS_H::HUMAN_CH;
                city.col(_GAMESPECS_H::DEFAULT_COLOR);
            }
                //else print a zombie character
            else {
                city.col(_GAMESPECS_H::ZOMBIE_COLOR);
                output << (char) _GAMESPECS_H::ZOMBIE_CH;
                city.col(_GAMESPECS_H::DEFAULT_COLOR);
            }
        }

        //place the vertical wall on right edge of grid
        output << "|" << endl;
    }

    //place the horizontal wall on bottom of grind
    output << "----------------------" << endl;
    return output;
}
