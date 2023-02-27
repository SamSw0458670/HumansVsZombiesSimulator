#ifndef _Human_H
#define _Human_H

#include "Organism.h"

class Human : public Organism {
public:
    //constructor/destructor
    Human(City *city, int width, int height);

    ~Human() override;

    //overridden logic functions
    void move() override;

    void createAlly() override;

    void turn() override;

    void checkAllyCreation() override;

    void checkPossibleDirections() override;

    void shuffleDirectionOptions() override;

    void moveDirection() override;

    void clearTargetingOptions() override;

    //logic functions
    void recruit();
};

#endif
