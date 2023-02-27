#ifndef _Organism_H
#define _Organism_H

#include <iostream>
#include <vector>

using namespace std;

class City;

class Organism {
protected:
    int x;
    int y;
    int species;
    bool moved = false;
    int steps = 0;

    enum directions {
        WEST, NORTH, EAST, SOUTH
    };
    City *city;
    vector<directions> posDir;

public:
    //constructor/destructor
    Organism(City *city, int width, int height);

    virtual ~Organism();

    //virtual logic functions
    virtual void move() = 0;

    virtual void createAlly() = 0;

    virtual void turn() = 0;

    virtual void checkAllyCreation() = 0;

    virtual void checkPossibleDirections() = 0;

    virtual void shuffleDirectionOptions() = 0;

    virtual void moveDirection() = 0;

    virtual void clearTargetingOptions() = 0;

    //getters and setters
    int getx() const;

    int gety() const;

    int getSpecies() const;

    void setx(int x);

    void sety(int y);

    void setPosition(int x, int y);

    //logic functions
    void endTurn();     //set the move flag back to false
};

#endif
