#include "ofApp.h"

// const float ofApp::MAX_SIMULATION_TIME = 1.f;
// const float ofApp::SAMPLING_FREQ = 44100.f;

//--------------------------------------------------------------
void ofApp::setup(){
    _mainWindow.setup();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    _mainWindow.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    _mainWindow.keyPressed(key);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    _mainWindow.keyReleased(key);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    _mainWindow.mouseMoved(ofVec2f(x, y));
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    _mainWindow.mouseDragged(ofVec2f(x, y), button);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    _mainWindow.mouseClicked(ofVec2f(x, y), button);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    _mainWindow.mouseReleased(ofVec2f(x, y), button);
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
