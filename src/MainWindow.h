
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
    void mouseClicked(const ofVec2f& position, const int button);
    void mouseDragged(const ofVec2f& position, const int button);
    void mouseReleased(const ofVec2f& position, const int button);
    void keyPressed(const int key);
    void keyReleased(const int key);

    private:
    
    static const float MAX_SCALE;
    static const float SLIDER_WIDTH;
    static const float SLIDER_HEIGHT;

    
    RTController    _controller;
    
    ofxPanel        _roomBuildPanel;
    ofxButton       _createRoomButton;
    ofxButton       _addSourceButton;
    ofxButton       _addListenerButton;
    ofxButton       _clearRoomButton;
    ofxFloatSlider  _worldScaleSlider;

    ofxPanel        _simulationPanel;
    ofxButton       _startSimButton;
    ofxButton       _stopSimButton;
    ofxButton       _pauseSimButton;
    ofxFloatSlider  _simTimeSlider;
};

#endif
