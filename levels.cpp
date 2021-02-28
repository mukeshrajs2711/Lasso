// modifies the parameters of the elements with respect to level of the game

#include <simplecpp>
#include <string>
#include "header_files/MovingObject.h"
#include "header_files/lasso.h"
#include "header_files/coin.h"
#include "header_files/bomb.h"

void level_mod (int level, Lasso *lasso, Coin *coin, Bomb *bomb) {
    /*if(level == 1) {
        Bomb bomb
    }*/

    if (level == 2) {
        // modifying the parameters of lasso and coin
        lasso->set_acc(20, 20);
        coin->set_v(120, 75);
        coin->set_acc(0, COIN_G);
    }

    if(level == 3) {
        for(int i = 0; i < 3; ++i) {
            bomb[i].unpause(); // to get the bomb moving
            bomb[i].unhideBomb(); // to make the bomb visible
        }
    }

    if(level == 4) {
        for(int i = 0; i < 3; i++) {
            bomb[i].resetBomb(); // to reset it to the top
            bomb[i].hideBomb(); // make the bomb invisible again
        }
        srand(time(0));
        coin->set_v(120, rand()%40+60);
    }
}