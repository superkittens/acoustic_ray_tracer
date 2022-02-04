
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
    if (!_source.getVisibility())
    {
        _source.setCoordinates(_room.getOrigin());
        _source.setVisible(true);
    }
}

void RTModel::addListener()
{
    if (_listeners.size() < MAX_NUM_SOURCES)
    {
        _listeners.push_back(Listener(_room.getOrigin(), _listeners.size()));
        _listeners.back().setVisible(true);
    }
}

bool RTModel::startRayTrace()
{
    //  Ensure that there is a room and at least one source and listener
    if (_listeners.empty() || !_room.isBuilt())
        return false;
    
    SolverInput inputs;
    inputs.listeners = &_listeners;
    inputs.source = &_source;
    inputs.simulationTime = _simulationTime;
    inputs.timeStep = _timeStep;
    inputs.room = &_room;
    inputs.numRays = _numRays;
    inputs.worldScale = _worldScale;
    
    _solver.startSimulation(inputs);
    
    return true;
}

void RTModel::pauseRayTrace()
{
    
}

void RTModel::stopRayTrace()
{
    
}

void RTModel::reset()
{
    _room.reset();
    _listeners.clear();
}
