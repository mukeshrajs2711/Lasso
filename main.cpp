#include <simplecpp>
#include <string>
#include "Header Files/MovingObject.h"
#include "Header Files/lasso.h"
#include "Header Files/coin.h"
#include "Header Files/bomb.h"

using namespace simplecpp;

main_program {

  // to get and store player's name
  char player_name[200];
  cout << "Enter your name: ";
  if (fgets(player_name, sizeof(player_name), stdin)) {
    player_name[strcspn(player_name, "\n")] = '\0'; // to remove the '\n' in the end of player_name
  }

  initCanvas("Lasso", WINDOW_X, WINDOW_Y);
  int stepCount = 0;
  float stepTime = STEP_TIME; 
  float runTime = -1; // sec; -ve means infinite
  float game_time = 0; // total time the game has been running
  float currTime = 0;

  // Draw lasso at start position
  double release_speed = INIT_RELEASE_SPEED; 
  double release_angle_deg = INIT_RELEASE_ANGLE_DEG; 
  double lasso_ax = 0; 
  double lasso_ay = LASSO_G; 
  bool paused = true;
  bool rtheta = true; 
  Lasso lasso(release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta); // constructing lasso

  // Draw coin at start position
  paused = true; rtheta = true;
  double coin_speed = COIN_SPEED;
  double coin_angle_deg = COIN_ANGLE_DEG;
  double coin_ax = 0;
  double coin_ay = COIN_G;
  Coin coin(coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta);

  // Define bombs 
  Bomb bomb[3] = {Bomb(0, BOMB_SPEED, 0, BOMB_G), Bomb(0, 2*BOMB_SPEED, 0, BOMB_G), Bomb(0, 1.4*BOMB_SPEED, 0, 0.8*BOMB_G)};

  Line b1(0, PLAY_Y_HEIGHT, WINDOW_X, PLAY_Y_HEIGHT); // x-axis
  b1.setColor(COLOR("blue"));
  Line b2(PLAY_X_START, 0, PLAY_X_START, WINDOW_Y);  // y-axis
  b2.setColor(COLOR("blue"));

  // to display the charachter pressed
  string msg("Cmd: _");
  Text charPressed(PLAY_X_START+50, PLAY_Y_HEIGHT+20, msg);

  // to display the total runtime of the game
  char gameTimeStr[256];
  sprintf(gameTimeStr, "Time: %f", game_time);
  Text gameTime(PLAY_X_START+200, PLAY_Y_HEIGHT+50, gameTimeStr);

  // to display current score
  char coinScoreStr[256]; 
  sprintf(coinScoreStr, "Coins: %d", lasso.getNumCoins()); 
  Text coinScore(PLAY_X_START+50, PLAY_Y_HEIGHT+50, coinScoreStr); 

  // to display the current level
  string msg2("Level: _");
  Text gameLevel(PLAY_X_START+200, PLAY_Y_HEIGHT+20, msg2);

  // to display name of the player
  char playNameStr[256];
  sprintf(playNameStr, "Name: %s", player_name);
  Text playName(PLAY_X_START+350, PLAY_Y_HEIGHT+20, playNameStr);

  // After every COIN_GAP sec, make the coin jump
  double last_coin_jump_end = 0;

  /* 
    t: throw lasso;
    lasso within range => stick coin
    y: yank lasso;
    l: loop lasso;
    q: quit 
  */

  int lev_num = 1; // level of the game
  void level_mod(int, Lasso *, Coin *, Bomb *); 

  while(true) { // start of each level

    // to display the current level
    msg2[msg2.length()-1] = lev_num+48;
    gameLevel.setMessage(msg2);

    level_mod(lev_num, &lasso, &coin, bomb);

    // to define vector from lasso to coin
    double diff_x1 = diff_y1 = 0; // vector in previous step
    double diff_x2 = diff_y2 = 0; // vector in current step

    while(true) { // start of step
      if((runTime > 0) && (currTime > runTime)) { break; }  

      // to update gameTime
      sprintf(gameTimeStr, "Time: %f", game_time);
      gameTime.setMessage(gameTimeStr);

      bool bomb_caught = false; // to check whether bomb is caught    

      XEvent e;
      bool pendingEv = checkEvent(e);
      if(pendingEv) {  

        char c = charFromEvent(e);

        // to display the given command
        msg[msg.length()-1] = c; 
        charPressed.setMessage(msg); 

        switch(c) {
              case 't':
	              lasso.unpause();
	              break;

              case 'y':
	              lasso.yank();
	              break;

              case 'l':
	              lasso.loopit();
	              lasso.check_for_coin(&coin);
                if(lev_num == 3)
                  bomb_caught = lasso.check_for_bomb(bomb); // to check whether lasso caught a bomb
	              wait(STEP_TIME*3);
	              break;

              case '[':
	              if(lasso.isPaused()) { lasso.addAngle(-RELEASE_ANGLE_STEP_DEG);	}
	              break;

              case ']':
	              if(lasso.isPaused()) { lasso.addAngle(+RELEASE_ANGLE_STEP_DEG); }
	              break;

              case '-':
	              if(lasso.isPaused()) {
                  if (lev_num != 5) // to prevent modifications in level 5
                    lasso.addSpeed(-RELEASE_SPEED_STEP);  
                }
	              break;

              case '=':
	              if(lasso.isPaused()) {
                  if(lev_num != 5) // to prevent modifications in level 5
                    lasso.addSpeed(+RELEASE_SPEED_STEP); 
                }
	              break;

              case 'q':
	              exit(0);

              default:
	              break;
        }
      }

      lasso.nextStep(stepTime);

      coin.nextStep(stepTime);
      if(coin.isPaused()) {
        if((currTime-last_coin_jump_end) >= COIN_GAP) {
	        coin.unpause();
        }
      }

      if(coin.getYPos() > PLAY_Y_HEIGHT) {
        coin.resetCoin();
        last_coin_jump_end = currTime;
      }

      // level 3 and bomb related modifications
      if( lev_num == 3 ) {
        for(int i = 0; i < 3; ++i) {
          bomb[i].nextStep(stepTime); // to move the bombs
          if(bomb[i].getYPos() > PLAY_Y_HEIGHT) { // bombs back to it's starting
            bomb[i].resetBomb();
          }
        }

        if(bomb_caught) {
          coin.resetCoin();
          lasso.resetLasso();
          for(int i = 0; i < 3; ++i) {
            bomb[i].resetBomb();
          }
          lasso.restoreNumCoins(); //if a bomb is caught, progress in the level resets
          bomb_caught = false;
        }
      }

    /*
      // level 4 related modifications
      if( lev_num == 4 ) {
        diff_x1 = diff_x2;
        diff_y1 = diff_y2;

        diff_x2 = coin.getXPos() - lasso.getXPos();
        diff_y2 = coin.getYPos() - lasso.getYPos();

        coin.mod_acc(diff_x2, diff_y2);
      }
    */
    
      sprintf(coinScoreStr, "Coins: %d", lasso.getNumCoins()); // updates coinStoreStr
      coinScore.setMessage(coinScoreStr); // changes the output to the string coinScoreStr

      if(lasso.getNumCoins() > 2) { 
          lev_num++;                  // update level number
          lasso.restoreNumCoins();
          break;   
      }

      stepCount++;
      currTime += stepTime;

      if(lev_num == 5) {  // slows down the game in level 5
        wait(0.3);
        game_time += 0.3; // updating the gameTime
      } 
      else {  
        wait(stepTime);
        game_time += stepTime; // updating the gameTime
      }
    } // end of one step
  } // end of a level

  wait(3);
} // End main_program
