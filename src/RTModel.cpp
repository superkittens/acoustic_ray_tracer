
#include "RTModel.h"

const size_t RTModel::MAX_NUM_LISTENERS = 1;
const size_t RTModel::MAX_NUM_SOURCES = 1;

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

void RTModel::addSoundSource()
{
    if (_sources.size() < MAX_NUM_SOURCES)
        _sources.push_back(Source(_room.getOrigin(), _sources.size()));
}

void RTModel::addListener()
{
    if (_listeners.size() < MAX_NUM_SOURCES)
        _listeners.push_back(Listener(_room.getOrigin(), _listeners.size()));
}

void RTModel::reset()
{
    _room.reset();
    _sources.clear();
    _listeners.clear();
}
