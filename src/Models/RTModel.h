#ifndef _RTMODEL_H
#define _RTMODEL_H

#include "Room.h"
#include "Solver.h"
#include "SourceSink.h"
#include "ofMain.h"
#include "RTCommon.h"
#include "Ray.h"

class RTModel
{
    public:
    static const size_t MAX_NUM_LISTENERS;
    static const size_t MAX_NUM_SOURCES;
    
    const   std::vector<ofVec2f>&   getRoomVertices() const { return _points; }
    void                            addRoomVertex(const ofVec2f& point);
    void                            clearRoomVertices() { _points.clear(); }
    
    void                            buildRoom();
    const Room&                     getRoom() const { return _room; }
    
    void                            setWorldScale(const float scale) { _worldScale = scale; }
    float                           getWorldScale() const { return _worldScale; }
    
    void                            addSoundSource(const ofVec2f startingPos);
    Source&                         getSoundSource() { return _source; }
    const Source&                   getSoundSource() const { return _source; }
    
    void                            addListener(const ofVec2f startingPos);
    const Listener&                 getListener() const { return _listener; }
    Listener&                       getListener() { return _listener; }
    
    void                            setSimulationTime(const float time) { _simulationTime = time; }
    const float&                    getSimulationTime() const { return _simulationTime; }
    float                           getCurrentSimulationTime() const { return _solver.getSimulationTime(); }
    bool                            getSimulationStatus() const { return _solver.getSimulationStatus(); }
    void                            setNumRays(const size_t numRays) { _numRays = numRays; }
    const size_t                    getNumRays() const { return _numRays; }
    void                            setTimeStep(const float timeStep) { _timeStep = timeStep; }
    const float&                    getTimeStep() const { return _timeStep; }
    
    bool                            startRayTrace();
    void                            pauseRayTrace(bool pause);
    void                            stopRayTrace();
    
    void                            updateSnapshot();
    const std::vector<Ray>&         getRays() const { return _raySnapshots; }
    const std::vector<float>&       getImpulseResponse(const Direction& dir) const;
    
    const ofVec2f&                  getRay() const { return _solver.getRay(); } //  Debug only
    
    void                            update() { _solver.update(); };
    
    void                            reset();

    
    private:
    std::vector<ofVec2f>    _points;
    Source                  _source;
    Listener                _listener;
    float                   _worldScale;
    float                   _simulationTime;
    float                   _timeStep;
    size_t                  _numRays;
    
    
    Room                    _room;
    Solver                  _solver;
    
    std::vector<Ray>        _raySnapshots;
    std::vector<float>      _irLeftSnapshot, _irRightSnapshot;
    bool                    _snapshotRequested = false;
};

#endif
