#ifndef _CITY_H
#define _CITY_H

#include <iostream>

using namespace std;

class Organism;

const int GRID_WIDTH = 20;
const int GRID_HEIGHT = 20;

class City {
protected:
    Organism *grid[GRID_HEIGHT][GRID_WIDTH] = {nullptr};

private:
    int generation;
    int zombieCount;
    int humanCount;
public:

    //constructors
    City();

    virtual ~City();

    //getters and setters
    int getGeneration();

    int getZombieCount();

    int getHumanCount();

    Organism *getOrganism(int x, int y);

    void setOrganism(Organism *organism, int x, int y);

    //logic functions
    bool hasDiversity();

    void reset();

    void populate();

    bool isEmpty(int xPos, int yPos);

    void col(int c);

    void move();

    void moveOrganism(Organism *organism, int x, int y);

    void consumeHuman(Organism *organism, int x, int y);

    void createHuman(int xPos, int yPos);

    void createZombie(int xPos, int yPos);

    void replaceZombieForHuman(int xPos, int yPos);

    void replaceHumanForZombie(int xPos, int yPos);

    void populateHumans();

    void populateZombies();

    friend ostream &operator<<(ostream &output, City &city);
};

#endif

