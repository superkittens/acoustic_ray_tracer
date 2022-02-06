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
    const std::vector<Listener>&    getListeners() const { return _listeners; }
    std::vector<Listener>&          getListeners() { return _listeners; }
    
    void                            setSimulationTime(const float time) { _simulationTime = time; }
    const float&                    getSimulationTime() const { return _simulationTime; }
    void                            setNumRays(const size_t numRays) { _numRays = numRays; }
    const size_t                    getNumRays() const { return _numRays; }
    void                            setTimeStep(const float timeStep) { _timeStep = timeStep; }
    const float&                    getTimeStep() const { return _timeStep; }
    
    bool                            startRayTrace();
    void                            pauseRayTrace();
    void                            stopRayTrace();
    
    void                            requestSnapshot();
    void                            updateSnapshot();
    bool                            isSnapshotReady() const;
    const std::vector<Ray>&         getRays() const;
    const ofVec2f&                  getRay() const { return _solver.getRay(); }
    
    void                            update() { _solver.update(); };
    
    void                            reset();

    
    private:
    std::vector<ofVec2f>    _points;
    Source                  _source;
    std::vector<Listener>   _listeners;
    float                   _worldScale;
    float                   _simulationTime;
    float                   _timeStep;
    size_t                  _numRays;
    
    
    Room                    _room;
    Solver                  _solver;
    
    std::vector<Ray>        _raySnapshots;
    bool                    _snapshotRequested = false;
};

#endif
