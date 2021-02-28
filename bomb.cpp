#include "Header Files/bomb.h"
#include<cstdlib>

void Bomb::initBomb(double argvy) {
    srand(argvy); // to seed rand() with vy since it is different for each bomb
    start_x = rand()%550 + 200; // to create a random number b/w 200 and 750
    start_y = 0;
    bomb_circle.reset(start_x, start_y, BOMB_SIZE);
    // Note that the bomb is intitally white making it invisible
    bomb_circle.setColor(COLOR("white"));
    bomb_circle.setFill(true);
    addPart(&bomb_circle);
}

void Bomb::resetBomb() {
    srand(time(0)); // to seed rand()
    start_x = rand()%550 + 200; // to create a random number b/w 200 and 750
    start_y = 0;
    reset_all(start_x, start_y, vy, -90, 0, ay, false, true);
}

void Bomb::unhideBomb() { // to make the bomb visible when needed
    bomb_circle.setColor(COLOR("grey"));
    bomb_circle.setFill(true);
}

void Bomb::hideBomb() { // to make the bomb invisible
    bomb_circle.setColor(COLOR("white"));
    bomb_circle.setFill(true);
}

