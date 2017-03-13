#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    video.load("movies/dogCG.mp4");
    video.setLoopState(OF_LOOP_NONE);
    video.play();
    
    videoWidth = video.getWidth();
    videoHeight = video.getHeight();
    
    texVideo.allocate(video.getPixels());
    texVideoGray.allocate(video.getPixels());
    fboVideoGray.allocate(videoWidth, videoHeight);
    
    texBase.allocate(video.getPixels());
    texBaseGray.allocate(video.getPixels());
    fboBaseGray.allocate(videoWidth, videoHeight);
    
    texBuffer.allocate(video.getPixels());
    fboBuffer.allocate(videoWidth, videoHeight);
    
    shGlayScale.load("", "shaders/grayscale.frag");
    shSubtraction.load("", "shaders/subtraction.frag");
    
    fboSubtraction.allocate(videoWidth, videoHeight);
    
    exp.setup(videoWidth, videoHeight, 24);
    exp.setOutputDir("out");
    exp.setOverwriteSequence(true);
    exp.setAutoExit(true);
    exp.startExport();
    
    ofSetFrameRate(24);
}

//--------------------------------------------------------------
void ofApp::update(){
    video.update();
    
    if (!video.isFrameNew()) {
        return;
    }
    
    // convert video to texture
    texVideo.loadData(video.getPixels(), videoWidth, videoHeight, GL_RGB);
    
    // video image graycale
    fboVideoGray.begin();
    shGlayScale.begin();
    shGlayScale.setUniformTexture("u_tex", texVideo, 0);
    ofDrawRectangle(0, 0, videoWidth, videoHeight);
    shGlayScale.end();
    fboVideoGray.end();
    
    // convert fbo to texture
    texVideoGray = fboVideoGray.getTexture();
    
    // baseGray - videoGray
    fboSubtraction.begin();
    shSubtraction.begin();
    shSubtraction.setUniformTexture("u_texBaseGray", texBaseGray, 0);
    shSubtraction.setUniformTexture("u_texVideoGray", texVideoGray, 1);
    ofDrawRectangle(0, 0, videoWidth, videoHeight);
    shSubtraction.end();
    fboSubtraction.end();
    
#ifdef MODE_PREVIOUS_FRAME
    // save base image
    texBuffer.loadData(video.getPixels(), videoWidth, videoHeight, GL_RGB);
    
    // base image graycale
    fboBuffer.begin();
    shGlayScale.begin();
    shGlayScale.setUniformTexture("u_tex", texBuffer, 0);
    ofDrawRectangle(0, 0, videoWidth, videoHeight);
    shGlayScale.end();
    fboBuffer.end();
    
    // convert fbo to texture
    texBaseGray = fboBuffer.getTexture();
#endif
    
    // temp screen image to buffer
    if (video.isPlaying()) {
        exp.begin();
        fboSubtraction.draw(0, 0);
        exp.end();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    exp.draw(0, 0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
#ifdef MODE_PREVIOUS_FRAME
#else
    // If you need a base frame
    if (key == OF_KEY_RETURN) {
        // save base image
        texBase.loadData(video.getPixels(), videoWidth, videoHeight, GL_RGB);
        
        // base image graycale
        fboBaseGray.begin();
        shGlayScale.begin();
        shGlayScale.setUniformTexture("u_tex", texBase, 0);
        ofDrawRectangle(0, 0, videoWidth, videoHeight);
        shGlayScale.end();
        fboBaseGray.end();
        
        // convert fbo to texture
        texBaseGray = fboBaseGray.getTexture();
    }
#endif
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
