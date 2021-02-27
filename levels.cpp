// modifies the parameters of the elements with respect to level of the game

#include <simplecpp>
#include <string>
#include "Header Files/MovingObject.h"
#include "Header Files/lasso.h"
#include "Header Files/coin.h"
#include "Header Files/bomb.h"

void level_mod (int level, Lasso *lasso, Coin *coin, Bomb *bomb) {
    /*if(level == 1) {
        Bomb bomb
    }*/

    if (level == 2) {
        // modifying the parameters of lasso and coin
        lasso->mod_acc(20, 20);
        coin->mod_acc_v(120, 75, 0, COIN_G);
        
        // to reset lasso and coin
        lasso->resetLasso();
        coin->resetCoin();
    }

    if(level == 3) {
        bomb->unpause(); // to get the bomb moving
        bomb->unhideBomb(); // to make the bomb visible
    }

    if(level == 4) {
        bomb->hideBomb(); // make the bomb invisible again
    }
}