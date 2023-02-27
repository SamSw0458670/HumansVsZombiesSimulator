#ifndef _Zombie_H
#define _Zombie_H

#include "Organism.h"

class Zombie : public Organism {
private:
    enum directions {
        WEST, NORTH, EAST, SOUTH, NEAST, SEAST, NWEST, SWEST
    };
    vector<directions> posDir;
    vector<directions> humansNear;
    int stepsWithoutFood = 0;
public:
    //constructor/destructor
    Zombie(City *city, int width, int height);

    ~Zombie() override;

    //overridden logic functions
    void createAlly() override;

    void turn() override;

    void checkAllyCreation() override;

    void move() override;

    void checkPossibleDirections() override;

    void shuffleDirectionOptions() override;

    void clearTargetingOptions() override;

    void moveDirection() override;

    //logic functions
    void shuffleEatOptions();

    void eat();

    void breed();

    void starve();

    void checkForStarving();
};

#endif
