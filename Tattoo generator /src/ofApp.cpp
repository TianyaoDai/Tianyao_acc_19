#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(30);
    ofBackground(255);
    ofSetBackgroundAuto(false);
    ofSetWindowTitle("Insta");
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    int angle_step = 30;
    
    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
    
    ofPushMatrix();
    
    ofSetLineWidth(0.3);
    ofSetColor(128);
    for (int i = 0; i < 540; i += angle_step / 3) {
        ofRotate(angle_step / 3);
        ofDrawLine(ofVec2f(0, 0), ofVec2f(ofGetWidth(), 0));
    }
    
    ofPopMatrix();
    
    ofSetLineWidth(1);
    ofSetColor(0);
    Leap::Controller controller;
    
    Leap::Frame frame = controller.frame();
    
    for (Leap::Hand hand : frame.hands()) {
        if (hand.isRight()) {
            for (Leap::Finger finger : hand.fingers()) {
                if (finger.type() == Leap::Finger::Type::TYPE_INDEX) {
                    this->pre_index_position = this->index_position;
                    this->index_position = ofVec3f(finger.tipPosition().x, -finger.tipPosition().y, 0);
                    if(hand.pinchStrength()>=1){
                        ofBackground(255);
                    }
                }
            }
        }
    }
    
    if (pre_index_position != ofVec3f(0, 0, 0)) {
        for (int i = 0; i < 480; i += angle_step) {
            ofPushMatrix();
            
            ofRotateZ(i);
            ofLine(index_position, pre_index_position);
            
            ofRotateY(90);
            ofLine(index_position, pre_index_position);
            
            ofPopMatrix();
        }
    }
}

