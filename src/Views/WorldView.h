
#ifndef _WORLD_VIEW_H
#define _WORLD_VIEW_H

#include "ofMain.h"
#include "SourceSink.h"
#include "Ray.h"
#include "Room.h"
#include "RTCommon.h"

typedef std::tuple<const Room&, const float, const Source&, const Listener&, const std::vector<Ray>&> SimulationData;
typedef std::tuple<const Room&, const float, const Source&, const Listener&, const ofVec2f&> SimulationDataDebug;

class WorldView
{
    public:
    void    setCursor(const ofVec2f& position);

    void    drawEmptyWindow() const;
    void    drawStatusBar(const RTState state) const;
    void    drawRoomSoFar(const std::tuple<const std::vector<ofVec2f>&, const float>& roomDrawData) const;
    void    drawNormalState(const Room& room, const float scale, const Source& source, const Listener& listener) const;
    void    drawSimulateState(const Room& room, const float scale, const Source& source, const Listener& listener, const std::vector<Ray>& rays) const;
    void    drawSimulateStateDebug(const SimulationDataDebug& data) const;
    void    drawSimulationProgress(const float time) const;
    bool    withinBounds(const ofVec2f& position) const;
    ofVec2f getWindowOrigin() const { return _WINDOW_OFFSET; }
    ofVec2f getWindowDimensions() const { return _WINDOW_DIMENSIONS; }

    private:
    static const ofVec2f    _WINDOW_OFFSET;
    static const ofVec2f    _WINDOW_DIMENSIONS;
    static const ofVec2f    _STATUS_BAR_OFFSET;
    static const ofVec2f    _STATUS_BAR_DIMENSIONS;
    static const float      _CROSSHAIR_LENGTH;
    static const float      _STATUS_BAR_COL_LENGTH;
    
    ofVec2f _cursorPosition;

    void    drawWindow() const;
    void    drawCursorPosInStatusBar(const ofVec2f pos) const;
};

#endif
