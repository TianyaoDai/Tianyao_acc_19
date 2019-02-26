#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    basePlayer_1.load("free_tv_960.mp4");
    basePlayer_2.load("toddy_fearless_960.mp4");

    basePlayer_1.play();
    basePlayer_2.play();
    //sound
    mySound.load("mp3/tv.mp3");
    
    if(mIdx==0){
        basePlayer_1.setVolume(1.0f);
        basePlayer_2.setVolume(0.0f);
    } else if(mIdx==1){
        basePlayer_1.setVolume(0.0f);
        basePlayer_2.setVolume(1.0f);
    }
    
    // overlay 1
    player_OL1.load("free_tv_960.mp4");
    
    // overlay 2
    player_OL2.load("toddy_fearless_960.mp4");
    
    // push overlay players to player vector
    mPlayerVec.push_back(player_OL1);
    mPlayerVec.push_back(player_OL2);
    
    mFrameDeques.push_back(frames_1);
    mFrameDeques.push_back(frames_2);
    
    mPixelVec.push_back(imagePixels_1);
    mPixelVec.push_back(imagePixels_2);
    
    mImageVec.push_back(img_OL1);
    mImageVec.push_back(img_OL2);
    
    
    
    
    for(int i=0; i<mPlayerVec.size(); i++){
        
        mPlayerVec[i].setVolume(0.0f);
        mPlayerVec[i].play();
    }

    // coordinates of overlay vids
    ol1X = ofGetWidth()*3/4;
    ol1Y = ofGetHeight()*3/4;
    ol2X = ofGetWidth()/4;
    ol2Y = ofGetHeight()*3/4;
    
    
    // push coordinate values to coordinate vectors
    mXcoords.push_back(ol1X);
    mXcoords.push_back(ol2X);
    
    mYcoords.push_back(ol1Y);
    mYcoords.push_back(ol2Y);
    
    
    // w&h of overlay vids
    aspectRatio = basePlayer_1.getWidth() / basePlayer_1.getHeight();
    overlayH = overlayW/aspectRatio;
    
   
    // gif
    gifloader.load("gifs/badtv.gif");
    gifloader1.load("gifs/ghostguy.gif");
    
    
    // button
    buttonColor = ofColor(255, 255, 255, 255);
    ofSetFrameRate(120);
    
}
   



//--------------------------------------------------------------
void ofApp::update(){
    
    // base video players update
    basePlayer_1.update();
    basePlayer_2.update();
    
    
    // switch base players' volumes on/off accordingly
    if(mIdx==0){
        basePlayer_1.setVolume(1.0f);
        basePlayer_2.setVolume(0.0f);
    } else if(mIdx==1){
        basePlayer_1.setVolume(0.0f);
        basePlayer_2.setVolume(1.0f);
    }
    
    
    // partical system for overlay vids
    
    for(int i=0; i<mPlayerVec.size(); i++){
        mPlayerVec[i].update();
        
        
        if(mPlayerVec[i].isFrameNew()){
            mFrameDeques[i].push_front(mPlayerVec[i].getPixels());
            if(mFrameDeques[i].size() > N ){ //if frames are greater than our max number
                mFrameDeques[i].pop_back(); //remove the last frame from the deque
            }
        }
        
        //if our frames deque is not empty
        if(!mFrameDeques[i].empty()){
            //and imagePixels is not allocated
            if(!mPixelVec[i].isAllocated()){
                mPixelVec[i] = mFrameDeques[i][0];
            }
            
            int w = mFrameDeques[i][0].getWidth();
            int h = mFrameDeques[i][0].getHeight();
            
            for (int y=0; y < h; y++) {
                for (int x=0; x < w; x++) {
                    //get the pixel color from our slit and assign to variable col
                    ofColor col = getSlitPixelColor(x,y,i);
                    
                    mPixelVec[i].setColor(x, y, col);
                }
            }
            
            mImageVec[i].setFromPixels(mPixelVec[i]);
        }
        
    }
    
    
    // gif-player update
    if (ofGetElapsedTimeMillis() % 3)
    {
        gif_idx++;
        if (gif_idx > gifloader.pages.size()-1) gif_idx = 0;
    }
    if (ofGetElapsedTimeMillis() % 30)
    {
        gif_idx1++;
        if (gif_idx1 > gifloader1.pages.size()-1) gif_idx1 =0;
    }
    

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(0);
    
    // play base vid accordingly
    if(mIdx==0){
        basePlayer_1.draw(0.0f, 0.0f, ofGetWidth(), ofGetHeight());
    } else if(mIdx==1){
        basePlayer_2.draw( 0.0f, 0.0f, ofGetWidth(), ofGetHeight());
    }
   
    
    ofPushStyle();
    ofSetColor(255, 255, 355);
    
    for(int i=0; i<mPlayerVec.size(); i++){
        if (mPlayerVec[i].isLoaded()) {

            mImageVec[i].draw(mXcoords[i]-overlayW/2, mYcoords[i]-overlayW/2, overlayW, overlayH);
        }
    }
    
    //if the button color alpha is greater than 4
    //animate the button
    if(buttonColor.a >= 4){
        animatePlayPause();
    }
    ofPopStyle();
    
    
    //draw our progress along the bottom of our screen
    ofPushStyle();
    ofSetColor(255, 200, 0, 255);
    ofFill();
    ofDrawRectangle(0.0f, ofGetHeight() - 10.0f, basePlayer_1.getPosition() * ofGetWidth(), 10.0f);
    ofPopStyle();
    
    
    // gif
    if(gifOn){
        gifloader.pages[gif_idx].draw(ofGetWidth()/15-80,ofGetHeight()/15-100,1000,1000);
    }
    
    if(gifOn1){
        gifloader1.pages[gif_idx1].draw(ofGetWidth()/15-80,ofGetHeight()/15-100,1000,1000);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    bool isPaused;
    
    switch (key) {
        case 'f':
            ofToggleFullscreen();
            break;
        case ' ':
            buttonColor.a = 255;
            // this is a ternary expression
            // if the player is paused, return false, otherwise return true
            isPaused = (basePlayer_1.isPaused()) ? false : true;
            basePlayer_1.setPaused(isPaused);
            break;
        case OF_KEY_LEFT:
            if (basePlayer_1.isPaused()) {
                basePlayer_1.previousFrame();
            }
            break;
        case OF_KEY_RIGHT:
            if (basePlayer_1.isPaused()) {
                basePlayer_1.nextFrame();
            }
            break;
        case '0':
            basePlayer_1.firstFrame();
            break;
        case 'g':
            gifOn = !gifOn;
            if(!gifOn){
                mySound.stop();
            }
            break;
        case 'h':
            gifOn1 = !gifOn1;
        default:
            break;
    }

}


//--------------------------------------------------------------
void ofApp::animatePlayPause(){
    ofPushStyle();
    ofSetColor(buttonColor);
    if(basePlayer_1.isPaused()){
        ofPushMatrix();
        ofFill();
        ofDrawRectangle(ofGetWidth()/2.0, ofGetHeight()/2.0, 10.0, 50.0);
        ofDrawRectangle(ofGetWidth()/2.0+25.0, ofGetHeight()/2.0, 10.0, 50.0);
        ofPopMatrix();
        buttonColor.a-=4;
    }
    else{
        ofPushMatrix();
        ofDrawTriangle(ofGetWidth()/2.0, ofGetHeight()/2.0, ofGetWidth()/2.0+50.0, ofGetHeight()/2.0+25.0, ofGetWidth()/2.0, ofGetHeight()/2.0+50.0);
        ofPopMatrix();
        buttonColor.a-=4;
    }
    ofPopStyle();
}

//--------------------------------------------------------------
ofColor ofApp::getSlitPixelColor(int x, int y, int i){
    float dist = ofDist(x, y, mouseX, mouseY);
    float f = dist / 16.0f;
    
    int i0 = int(f);
    int i1 = i0 + 1;
    
    //compute weights of the frames i0 and i1
    float weight0= i1 - f;
    float weight1 = 1 - weight0;
    
    //make sure we limit out frames between 0 and frames.size() - 1
    i0= ofClamp(i0, 0, mFrameDeques[i].size() - 1);
    i1= ofClamp(i1, 0, mFrameDeques[i].size() - 1);
    
    ofColor color0 = mFrameDeques[i][i0].getColor(x, y);
    ofColor color1 = mFrameDeques[i][i1].getColor(x, y);
    
    //interpolate between colors 0 and 1
    // this is the meat of the algorithm!
    ofColor interpolatedColor = color0 * weight0 + color1* weight1;
    
    return interpolatedColor;
    
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
    
    // y coordinates
    if( ofGetMouseY()>=ol1Y-overlayH/2 && ofGetMouseY()<=ol1Y+overlayH/2 ){
        
        //x coordinates
        if( ofGetMouseX()>=ol1X-overlayW/2 && ofGetMouseX()<=ol1X+overlayW/2 ){
            mIdx=0;
        } else if( ofGetMouseX()>=ol2X-overlayW/2 && ofGetMouseX()<=ol2X+overlayW/2 ){
            mIdx=1;
        }
    }
    
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
