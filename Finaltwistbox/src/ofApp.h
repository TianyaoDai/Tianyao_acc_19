#pragma once

#include "ofMain.h"
#include "Particle.h"
//leapmotion addon
#include "ofxLeapMotion2.h"


class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    //setup interactive camera
    ofEasyCam cam;
    // add light 
    ofLight light;
    vector<Particle> particles;
    float move_x, move_y, move_z;
    // Leap Motion
    ofxLeapMotion controller;
    float threshold;
  
};
