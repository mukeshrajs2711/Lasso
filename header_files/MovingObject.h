#ifndef _MOVINGOBJECT_INCLUDED_
#define _MOVINGOBJECT_INCLUDED_

#define WINDOW_X 800
#define WINDOW_Y 800

#define STEP_TIME 0.05 //time b/w successive steps

#define PLAY_X_START 100
#define PLAY_Y_START 0
#define PLAY_X_WIDTH (WINDOW_X-PLAY_X_START)
#define PLAY_Y_HEIGHT (WINDOW_Y-100)

#include <simplecpp>
#include <vector>
#include <composite.h>
#include <sprite.h>

using namespace simplecpp;

class MovingObject : public Sprite {
  vector<Sprite*> parts;    //vector that contains all the pointers to the parts of a moving object
  double vx, vy;  //velocity of object
  double ax, ay;  //acceleration of object
  bool paused;
  void initMO(double argvx, double argvy, double argax, double argay, bool argpaused=true) {  //to initialize the object's velocity
    vx=argvx; vy=argvy; ax=argax; ay=argay; paused=argpaused;                                 //and acceleration
  }

 public:
 MovingObject(double argvx, double argvy, double argax, double argay, bool argpaused=true) : Sprite() {   //constructor in rectangular
    initMO(argvx, argvy, argax, argay, argpaused);                                                        //coordinates
  }
  
  //constructor with velocity in polar coordinates
 MovingObject(double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta) : Sprite() { 
   double angle_rad = angle_deg*PI/180.0;                                                                           
   double argvx = speed*cos(angle_rad);
   double argvy = -speed*sin(angle_rad);
   initMO(argvx, argvy, argax, argay, argpaused);
  }

  void set_vx(double argvx) { vx = argvx; }
  void set_vy(double argvy) { vy = argvy; }
  void set_ax(double argax) { ax = argax; }
  void set_ay(double argay) { ay = argay; }
  double getXPos();
  double getYPos();
  void reset_all(double argx, double argy, double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta);

  void pause() { paused = true; }
  void unpause() { paused = false; }
  bool isPaused() { return paused; }

  void addPart(Sprite* p) {
    parts.push_back(p);
  }
  void nextStep(double t);
  void getAttachedTo(MovingObject *m);
};

#endif
