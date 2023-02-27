
#include "../headers/Organism.h"

//constructor
Organism::Organism(City *city, int width, int height) {
    this->city = city;
    this->width = width;
    this->height = height;
}

//destructor
Organism::~Organism() = default;

//getters
int Organism::getSpecies() const {return this->species;}

int Organism::getx() const { return this->x;}

int Organism::gety() const { return this->y;}

//setters
void Organism::setx(int x) {this->x = x;}

void Organism::sety(int y){this->y = y;};

void Organism::setPosition(int xPos, int yPos) {
    this->x = xPos;
    this->y = yPos;
}

//set the move flag back to false
void Organism::endTurn() {this->moved = false;}


