
#ifndef _WORLD_VIEW_H
#define _WORLD_VIEW_H

#include "ofMain.h"

class WorldView
{
    public:
    void setCursor(const ofVec2f& position);

    void    drawEmptyWindow() const;
    void    drawRoomSoFar(const std::vector<ofVec2f>& points) const;
    void    drawSimulatedResult();
    bool    withinBounds(const ofVec2f& position) const;


    private:
    static const ofVec2f    _windowOffset;
    static const ofVec2f    _windowDimensions;
    static const float      CROSSHAIR_LENGTH;
    
    ofVec2f _cursorPosition;

    void    drawWindow() const;
};

#endif
