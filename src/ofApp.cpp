#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

}

//--------------------------------------------------------------
void ofApp::update(){
    if (solver.get() != nullptr)
        solver->update();

    if (world.getWorldBuildState() == World::BUILT)
    {
        const auto walls = world.getWalls();
        bool indOutsideWall = false;
        for (const auto &w : walls)
        {
            bool status = w.isPointOutsideWall(ind.getCoordinates());
            if (status)
                indOutsideWall = true;
        }

        if (indOutsideWall)
            ind.setColor(ofColor(0, 255, 255));
        else
            ind.setColor(ofColor(255, 255, 255));
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    world.draw();
    ind.draw();

    if (listener.get() != nullptr)
        listener->draw();
    
    if (emitter.get() != nullptr)
        emitter->draw();

    if (solver.get() != nullptr)
        solver->draw();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key)
    {
        case 'w':
        world.startWorldBuilding();
        break;

        case 'l':
        if (listener.get() == nullptr)
            listener = std::make_shared<Listener>(ofVec2f{world.getWorldOrigin()});
        break;

        case 'e':
        if (emitter.get() == nullptr)
            emitter = std::make_shared<Emitter>(ofVec2f{world.getWorldOrigin()});
        break;

        //  Start simulation
        case 's':
        if (emitter.get() != nullptr && listener.get() != nullptr)
        {
            solver = std::make_unique<Solver>(&world, listener, emitter, 0.1, 1);
        }
        break;

        //  Shift key
        case 1:
        world.setLineLock(true);
        break;

        default:
        break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

    switch (key)
    {
        case 1:
        world.setLineLock(false);
        break;

        default:
        break;
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    world.setCursor(ofVec2f(x, y));
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    if (listener.get() != nullptr)
        listener->move(ofVec2f(x, y));
    
    if (emitter.get() != nullptr)
        emitter->move(ofVec2f(x, y));

    ind.move(ofVec2f(x, y));
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    world.setPoint();

    if (listener.get() != nullptr)
        listener->grab(ofVec2f(x, y));

    if (emitter.get() != nullptr)
        emitter->grab(ofVec2f(x, y));

    ind.grab(ofVec2f(x, y));
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    if (listener.get() != nullptr)
        listener->release();
    
    if (emitter.get() != nullptr)
        emitter->release();

    ind.release();
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
