
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
    ofVec3f startlocation;
    ofVec3f velocity;
    ofVec3f acceleration;
    ofColor pcolor;
    vector<ofVec3f> log;
    float maxspeed;
    float maxforce;
    float radius;
    float angle;
    float psize;

  
};
