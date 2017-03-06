#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    video.load("dog.mov");
    video.setLoopState(OF_LOOP_NORMAL);
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
    
    shGlayScale.load("", "shader/grayscale.frag");
    shSubtraction.load("", "shader/subtraction.frag");
    
    fboSubtraction.allocate(videoWidth, videoHeight);
}

//--------------------------------------------------------------
void ofApp::update(){
    video.update();
    
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
    
    // buffer
    
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
}

//--------------------------------------------------------------
void ofApp::draw(){
    fboSubtraction.draw(0, 0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
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
