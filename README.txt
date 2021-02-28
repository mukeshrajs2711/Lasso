Introduction to the game

Objective:
    The game consists of five levels. The objective of the game is to 
    complete all the levels in the shortest time possible.

The mechanics of the game:
    The lasso game involves throwing a lasso and looping it to catch a coin
    that bounces of the ground. Once the coin is caught, the player has to 
    yank back the lasso to gain points.

Level 1: 
    This is the most basic level to get the player used to the game. Every 
    level needs fives coins to be caught in order to move to the next level. 

Level 2:
    In this level, the coin is given a horizontal velocity as well to make
    it go in a parabola. Also, the lasso is given a horizontal acceleration
    so as to increase it's horizontal reach.

Level 3:
    In this level, bombs are dropped from the sky which are definitely 
    not the things one wants to catch. Catching these bombs will reset 
    the progress of the player in the same level.

Level 4:
    If catching a coin that is following a fixed trajectory isn't hard enough,
    to make it even more harder, in this level, the coin's direction is 
    completely random every time it jumps of the ground.

Level 5:
    All these levels must've tested the skills of the player. This level is
    designed to test the patience of the player. Get ready for some slow 
    burn. The game is intentionally slowed down to 3fps to make it harder.



Commands of the game:
    't': To throw the lasso
    'l': To loop the lasso
    'y': To yank the lasso
    '[': To reduce the angle of the lasso throw
    ']': To increase the angle of the lasso throw
    '-': To reduce the speed of lasso throw
    '=': To increase the speed of the lasso
    'q': To quit the game


(*) Command to compile: ./compile.sh
    [s++ -o lasso lasso.cpp MovingObject.cpp coin.cpp levels.cpp bomb.cpp main.cpp]
