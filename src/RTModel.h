#ifndef _RTMODEL_H
#define _RTMODEL_H

//#include "World.h"
#include "Room.h"
#include "Solver.h"
#include "SourceSink.h"
#include "ofMain.h"

class RTModel
{
    public:
    const std::vector<ofVec2f>& getRoomVertices() const { return _points; }
    void addRoomVertex(const ofVec2f& point);
    void clearRoomVertices() { _points.clear(); }
    
    void buildRoom(const ofVec2f roomOrigin);
    const Room& getRoom() const { return _room; }
    
    void setWorldScale(const float scale) { _worldScale = scale; }
    float getWorldScale() const { return _worldScale; }

    private:
    std::vector<ofVec2f> _points;
    float _worldScale = 1.0;
    
    Room _room;
};

#endif
