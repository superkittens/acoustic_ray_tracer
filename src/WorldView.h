
#ifndef _WORLD_VIEW_H
#define _WORLD_VIEW_H

#include "ofMain.h"

class WorldView
{
    public:
    void setCursor(const ofVec2f& position);
    void setStraightLine(bool setting) { _drawStraightLines = setting; }

    void drawRoomSoFar();
    void drawSimulatedResult();


    private:
    static const ofVec2f _windowOffset;
    static const ofVec2f _windowDimensions;
    
    ofVec2f _cursorPosition;
    bool    _drawStraightLines;

    void    drawWindow();
    bool    cursorInBounds(const ofVec2f& position) const;
};

#endif