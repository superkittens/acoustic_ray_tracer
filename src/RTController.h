#ifndef _RTCONTROLLER_H
#define _RTCONTROLLER_H

#include "WorldView.h"
#include "RTModel.h"
#include "ofMain.h"

class RTController
{
    typedef enum
    {
        START = 0,
        ROOM_BUILD,
        NORMAL,
        SIM_RUNNING
    }RTState;

    public:
    void draw() const;
    void mouseMoved(const ofVec2f& position);
    void mouseClicked(const ofVec2f& position, const int button);
    void mouseDragged(const ofVec2f& position, const int button);
    void mouseReleased(const ofVec2f& position, const int button);
    void keyPressed(const int key);
    void keyReleased(const int key);

    void onCreateRoomClicked();
    void onWorldScaleSliderChanged(float& value);
    void onClearRoomClicked();
    void onAddSourceClicked();
    void onAddListenerClicked();

    private:
    static const float SNAP_THRESHOLD;
    
    WorldView   _worldView;
    RTModel     _model;
    
    RTState     _currentState = START;
    
    bool        _drawStraightLines = false;
    
    ofVec2f snapCursor(const ofVec2f& cursorPos);
    ofVec2f snapCursorToFirstPoint(const ofVec2f& cursorPos);
};

#endif
