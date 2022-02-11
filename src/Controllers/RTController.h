#ifndef _RTCONTROLLER_H
#define _RTCONTROLLER_H

#include "WorldView.h"
#include "GraphView.hpp"
#include "RTModel.h"
#include "ofMain.h"
#include "RTCommon.h"
#include "RTFileWriter.hpp"

class RTController
{
    public:
    void setup(const float worldScale, const float simTime, const float timeStep, const size_t numRays);
    void draw() const;
    void update();
    
    void mouseMoved(const ofVec2f& position);
    void mouseClicked(const ofVec2f& position, const int button);
    void mouseDragged(const ofVec2f& position, const int button);
    void mouseReleased(const ofVec2f& position, const int button);
    void keyPressed(const int key);
    void keyReleased(const int key);

    void onCreateRoomClicked();
    void onWorldScaleSliderChanged(float& value);
    void onClearRoomClicked();
    
    void onStartSimClicked();
    void onPauseSimClicked();
    void onStopSimClicked();
    void onSimTimeSliderChanged(float& value);
    void onNumRaysChanged(size_t& value);
    void onTimeStepChanged(float& value);
    
    void onWriteIRClicked();

    private:
    static const float SNAP_THRESHOLD;
    
    WorldView   _worldView;
    GraphView   _graphView;
    
    RTModel     _model;
    
    RTState     _currentState = START;
    
    bool        _drawStraightLines = false;
    
    RTFileWriter    _fileWriter;
    Direction       _currentIRBeingWritten = LEFT;
    
    size_t      _counter = 0;
    
    ofVec2f snapCursor(const ofVec2f& cursorPos);
    ofVec2f snapCursorToFirstPoint(const ofVec2f& cursorPos);
    void    buildRoom();
};

#endif
