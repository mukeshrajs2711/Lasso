#include <simplecpp>
#include "Header Files/MovingObject.h"

using namespace simplecpp;

//to move the object to its next step
//moves all parts of the object
void MovingObject::nextStep(double t) {         
  if(paused) { return; }
  //cerr << "x=" << getXPos() << ",y=" << getYPos() << endl;      
  //cerr << "vx=" << vx << ",vy=" << vy << endl;  
  //cerr << "ax=" << ax << ",ay=" << ay << endl;  

  for(size_t i=0; i<parts.size(); i++){
    parts[i]->move(vx*t, vy*t);
  }
  vx += ax*t;
  vy += ay*t;
} // End MovingObject::nextStep()

double MovingObject::getXPos() {
  return (parts.size() > 0) ? parts[0]->getX() : -1;
}

double MovingObject::getYPos() {
  return (parts.size() > 0) ? parts[0]->getY() : -1;
}

void MovingObject::reset_all(double argx, double argy, double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta) {
  for(size_t i=0; i<parts.size(); i++){
    parts[i]->moveTo(argx, argy);
  }
  double angle_rad = angle_deg*PI/180.0;
  double argvx = speed*cos(angle_rad);
  double argvy = -speed*sin(angle_rad);
  vx = argvx; vy = argvy; ax = argax; ay = argay; paused = argpaused;
} // End MovingObject::reset_all()

/* A function that attaches a moving object
to another. Like, attaching the gold coin to 
the end of the lasso */ 

/* My understanding as of now is that,
this function acts on moving object coin to attach
it to moving object lasso */
void MovingObject::getAttachedTo(MovingObject *m) {
  double xpos = m->getXPos();
  double ypos = m->getYPos();
  for(size_t i=0; i<parts.size(); i++){
    parts[i]->moveTo(xpos, ypos);   //moving all parts of coin 
  }                                 //to the position of m
  
  //initializing coin with the speed and acceleration of lasso
  initMO(m->vx, m->vy, m->ax, m->ay, m->paused); 
}
