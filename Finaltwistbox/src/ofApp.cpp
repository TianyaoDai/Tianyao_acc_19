

#include "ofApp.h"
//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(30);
    ofBackground(0);
    ofSetWindowTitle("TwistBox");
    
    // Gathering the particle to form the box
    int span =50;
    for (int x = -ofGetWidth() ; x < ofGetWidth() ; x += span) {
        for (int y = -ofGetHeight() / 2; y < ofGetHeight() / 2; y += span) {
            for (int z = -ofGetWidth() / 2; z < ofGetWidth() / 2; z += span) {
                Particle p = Particle(x, y, z);
                this->particles.push_back(p);
            }
        }
    }
      this->light.setPosition(ofVec3f(600, 600, 850));
    this->threshold = 0.5;
}
//--------------------------------------------------------------
void ofApp::update(){
    
    this->move_x = ofGetWidth();
    this->move_y = ofGetHeight();
    this->move_z = ofGetWidth();
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofEnableDepthTest();
    ofEnableLighting();
    this->light.enable();
    cam.begin();
    
    float power =700; //power can control the movement of the particle 
    Leap::Controller controller;
    Leap::Frame frame = controller.frame();
    //detect the palm posistion.
 for (Leap::Hand hand : frame.hands()) {
        if (hand.isRight()) {
            
            this->move_x = hand.palmPosition().x * 2;
            this->move_y = hand.palmPosition().y - ofGetHeight() / 2;
            this->move_z = hand.palmPosition().z * 2;
            power *= 1 - hand.pinchStrength();//when you open your hand, the pinchstrengh will get closer to 0, when you grab your hand, the pinchstrength will get closer to 1.
            if(hand.grabStrength() >=1 ){
                
                this->threshold += this->threshold <=1 ? 0.05 : 0;
                
            }
            
            else {

                this->threshold -= this->threshold > 0 ? 0.05 : 0;

            }
        }
    }
    
    
    for (Particle& p : this->particles) {
        p.move(ofVec3f(this->move_x, this->move_y, this->move_z), power);
        p.update();
        p.draw();
        ofRotateX(this->threshold/40); //grab hand and it will twist
       
    }
    cam.end();
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
