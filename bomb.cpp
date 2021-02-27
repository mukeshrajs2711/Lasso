#include "Header Files/bomb.h"
#include<cstdlib>

void Bomb::initBomb() {
    srand(time(0)); // to seed rand()
    start_x = rand()%700 + 100; // to create a random number b/w 100 and 800
    start_y = 0;
    bomb_circle.reset(start_x, start_y, BOMB_SIZE);
    // Note that the bomb is intitally white making it invisible
    bomb_circle.setColor(COLOR("white"));
    bomb_circle.setFill(true);
    addPart(&bomb_circle);
}

void Bomb::resetBomb() {
    srand(time(0)); // to seed rand()
    start_x = rand()%700 + 100; // to create a random number b/w 100 and 800
    start_y = 0;
    reset_all(start_x, start_y, 120, -90, 0, BOMB_G, false, true);
}

void Bomb::makeVis() { // to make the bomb visible when needed
    bomb_circle.setColor(COLOR("grey"));
    bomb_circle.setFill(true);
}

