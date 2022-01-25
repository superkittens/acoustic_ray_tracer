
#ifndef MAIN_WINDOW_H_
#define MAIN_WINDOW_H_

#include "RTController.h"
#include "ofxGui.h"

class MainWindow
{
    public:
    void setup();
    void draw();
    void mouseMoved(const ofVec2f& position);
    void mouseClicked(const ofVec2f& position);
    void mouseDragged(const ofVec2f& position);

    private:
    RTController    _controller;
    ofxPanel        _roomBuildPanel;
    ofxPanel        _simulationPanel;
};

#endif