#ifndef _RTMODEL_H
#define _RTMODEL_H

#include "Room.h"
#include "Solver.h"
#include "SourceSink.h"
#include "ofMain.h"

class RTModel
{
    public:
    static const size_t MAX_NUM_LISTENERS;
    static const size_t MAX_NUM_SOURCES;
    
    const   std::vector<ofVec2f>&   getRoomVertices() const { return _points; }
    void                            addRoomVertex(const ofVec2f& point);
    void                            clearRoomVertices() { _points.clear(); }
    
    void                            buildRoom(const ofVec2f roomOrigin);
    const Room&                     getRoom() const { return _room; }
    
    void                            setWorldScale(const float scale) { _worldScale = scale; }
    float                           getWorldScale() const { return _worldScale; }
    
    void                            addSoundSource();
    Source&                         getSoundSource() { return _source; }
    const Source&                   getSoundSource() const { return _source; }
    
    void                            addListener();
    const std::vector<Listener>&    getListeners() const { return _listeners; }
    std::vector<Listener>&          getListeners() { return _listeners; }
    
    void                            setSimulationTime(const float time) { _simulationTime = time; }
    const float                     getSimulationTime() const { return _simulationTime; }
    void                            setNumRays(const size_t numRays) { _numRays = numRays; }
    const size_t                    getNumRays() const { return _numRays; }
    void                            setTimeStep(const float timeStep) { _timeStep = timeStep; }
    const float                     getTimeStep() const { return _timeStep; }
    
    bool                            startRayTrace();
    void                            pauseRayTrace();
    void                            stopRayTrace();
    
    void                            update();
    
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
};

#endif
