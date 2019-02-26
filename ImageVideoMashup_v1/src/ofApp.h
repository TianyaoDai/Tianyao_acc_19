#pragma once

#include "ofMain.h"
#include "ofxGif.h"

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
    
        void animatePlayPause();
        //ofVideoPlayer player;

    
        // base vid players
    
        ofVideoPlayer basePlayer_1;
        ofVideoPlayer basePlayer_2;
    
        vector<ofVideoPlayer> mBasePlayersVec;

        // vectors for overlay vids
    
        vector<ofVideoPlayer> mPlayerVec;
        vector< deque<ofPixels> > mFrameDeques;
        vector<ofPixels> mPixelVec;
        vector<ofImage> mImageVec;
    
        vector<int> mXcoords;
        vector<int> mYcoords;
    
        // player index
        int mIdx = 0;
    
        // overlay 1
        ofVideoPlayer player_OL1;
        ofImage img_OL1;
        deque<ofPixels> frames_1;
        ofPixels imagePixels_1;
    
    
        // overlay 2
        ofVideoPlayer player_OL2;
        ofImage img_OL2;
        deque<ofPixels> frames_2;
        ofPixels imagePixels_2;
    
    
    
        // overlay vids' coordinates
        int ol1X; int ol1Y;
        int ol2X; int ol2Y;
    
    
        ofColor buttonColor;
        ofColor getSlitPixelColor(int x, int y, int i);
    
        int N = 100;
    
    
        int overlayW = 320;
        int overlayH;
        float aspectRatio;
    
        bool gifOn = false;
        ofxGIF::fiGifLoader gifloader;
        int gif_idx = 0;
    
        bool gifOn1= false;
        ofxGIF::fiGifLoader gifloader1;
        int gif_idx1 = 0;
    
    
        ofSoundPlayer   mySound;
        bool mySound1 = false;
        //bool gifOn_2 = false;
        //ofxGIF::fiGifLoader gifloader_2;
        //int gif_idx_2 = 0;
    
};
