
#ifndef MAIN_WINDOW_H_
#define MAIN_WINDOW_H_

#include "RTController.h"
#include "ofxGui.h"

class MainWindow
{
    public:
    void setup();
    void draw();
    void update();
    
    void mouseMoved(const ofVec2f& position);
    void mouseClicked(const ofVec2f& position, const int button);
    void mouseDragged(const ofVec2f& position, const int button);
    void mouseReleased(const ofVec2f& position, const int button);
    void keyPressed(const int key);
    void keyReleased(const int key);

    private:
    
    static const float  START_TIME_STEP;
    static const float  MAX_SCALE;
    static const float  MAX_SIM_TIME;
    static const int    MAX_NUM_RAYS;
    static const float  MIN_SCALE;
    static const float  MIN_SIM_TIME;
    static const int    MIN_NUM_RAYS;
    static const float  SLIDER_WIDTH;
    static const float  SLIDER_HEIGHT;
    
    RTController    _controller;
    
    ofxPanel        _roomBuildPanel;
    ofxButton       _createRoomButton;
    ofxButton       _clearRoomButton;
    ofxFloatSlider  _worldScaleSlider;

    ofxPanel        _simulationPanel;
    ofxButton       _startSimButton;
    ofxButton       _stopSimButton;
    ofxButton       _pauseSimButton;
    ofxFloatSlider  _simTimeSlider;
    ofxLabel        _numRaysLabel;
    ofxInputField<size_t> _numRaysField;
    ofxLabel        _timeStepLabel;
    ofxInputField<float> _timeStepField;
};

#endif
