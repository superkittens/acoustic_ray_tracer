#ifndef _RTMODEL_H
#define _RTMODEL_H

#include "World.h"
#include "Solver.h"
#include "SourceSink.h"
#include "ofMain.h"

class RTModel
{
    public:
    const std::vector<ofVec2f>& getRoomVertices() const { return _points; }
    void addRoomVertex(const ofVec2f& point);

    private:
    std::vector<ofVec2f> _points;
};

#endif
