#ifndef _BOMB_H_
#define _BOMB_H_

#include "MovingObject.h"
#define BOMB_START_X 
#define BOMB_SIZE 9
#define BOMB_SPEED 120
#define BOMB_G 30

class Bomb : public MovingObject {
    
    double start_x;
    double start_y;
    double vx, vy;
    double ax, ay;

    Circle bomb_circle;

    public:
        void initBomb();

        Bomb (double argvx, double argvy, double argax, double argay, bool argpaused = true) : MovingObject(argvx, argvy, argax, argay, argpaused) {
            vx = argvx; vy = argvy;
            ax = argax; ay = argay;
            initBomb();
        }

    void resetBomb(); // to reset bomb back to position
    void makeVis();
};

#endif