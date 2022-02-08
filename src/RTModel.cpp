
#include "RTModel.h"

const size_t RTModel::MAX_NUM_LISTENERS = 1;
const size_t RTModel::MAX_NUM_SOURCES = 1;

void RTModel::addRoomVertex(const ofVec2f& point)
{
    _points.push_back(point);
}

void RTModel::buildRoom()
{
    _room.buildRoom(_points);
}

void RTModel::addSoundSource(const ofVec2f startingPos)
{
    _source.setCoordinates(startingPos);
    _source.setVisible(true);
}

void RTModel::addListener(const ofVec2f startingPos)
{
    _listener.setCoordinates(startingPos);
    _listener.setVisible(true);
}

bool RTModel::startRayTrace()
{
    //  Ensure that there is a room and at least one source and listener
    if (!_room.isBuilt())
        return false;
    
    SolverInput inputs;
    inputs.listener = &_listener;
    inputs.source = &_source;
    inputs.simulationTime = _simulationTime;
    inputs.timeStep = _timeStep;
    inputs.room = &_room;
    inputs.numRays = _numRays;
    inputs.worldScale = _worldScale;
    
    _raySnapshots.clear();
    _snapshotRequested = false;
    
    _solver.startSimulation(inputs);
    
    return true;
}

void RTModel::pauseRayTrace(bool pause)
{
    _solver.pauseSimulation(pause);
}

void RTModel::stopRayTrace()
{
    _solver.requestSimulationStop();
}

void RTModel::requestSnapshot()
{
    if (!_snapshotRequested)
    {
        _snapshotRequested = true;
        _solver.requestSimulationSnapshot();
    }
}

void RTModel::updateSnapshot()
{
    if (_snapshotRequested)
    {
        if (_solver.getRays(_raySnapshots))
            _snapshotRequested = false;
    }
}

const std::vector<Ray>& RTModel::getRays() const
{
    return _raySnapshots;
}

void RTModel::reset()
{
    _room.reset();
    _source.setVisible(false);
    _listener.setVisible(false);
    _raySnapshots.clear();
}
