
#include "RTModel.h"

void RTModel::addRoomVertex(const ofVec2f& point)
{
    _points.push_back(point);
}

void RTModel::buildRoom(const ofVec2f roomOrigin)
{
    _room.setOrigin(roomOrigin);
    std::transform(_points.begin(), _points.end(), _points.begin(),
                    [&](ofVec2f a) { return a - roomOrigin; });
    
    _room.buildRoom(_points);
}
