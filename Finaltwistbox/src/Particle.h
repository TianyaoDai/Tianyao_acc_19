
#pragma once

#include "ofMain.h"

class Particle
{
public:
    Particle();
    Particle(float x, float y, float z);
    ~Particle();
    
    void applyForce(ofVec3f force);
    void seek(ofVec3f target);
    void move(ofVec3f target, float pow);
    void update();
    void draw();
    
private:
    ofVec3f location;
    ofVec3f start_location;
    ofVec3f velocity;
    ofVec3f acceleration;
    ofColor particlecolor;
    vector<ofVec3f> log;
    float max_speed;
    float max_force;
    float radius;
    float particlesize;

  
};
