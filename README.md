# HumansVsZombiesSimulator
A console line application where the user can watch an epic battle between humans and zombies, and see which species will be victorious

<br>

## Features
- Uses three of the four major Object-Oriented Programming principles : inheritance, encapsulation, and polymorphism.
- The grid is displayed using a two dimensional array of pointers to the “Organism” class which the Human and Zombie class both inherit from, allowing both Humans and Zombies to exist in the array.
- Zombies have prioritized movement to eat a human if there is one near them.
- If a Zombie moves three spaces and does not eat a human, it will “starve” and turn back into a human.
