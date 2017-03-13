#pragma once

#include "ofMain.h"
#include "ofxExportImageSequence.h"

#define MODE_PREVIOUS_FRAME

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
    
    float videoWidth;
    float videoHeight;
		
    ofVideoPlayer video;
    
    // original
    ofTexture texVideo;
    ofTexture texVideoGray;
    ofFbo fboVideoGray;
    
    // base subtraction
    ofTexture texBase;
    ofTexture texBaseGray;
    ofFbo fboBaseGray;
    
    // buffer
    ofTexture texBuffer;
    ofFbo fboBuffer;
    
    ofShader shGlayScale;
    ofShader shSubtraction;
    ofFbo fboSubtraction;
    
    ofxExportImageSequence exp;
};
