#ifndef SOLVER_H_
#define SOLVER_H_

#include "ofMain.h"
#include "SourceSink.h"
#include "Room.h"
#include "Ray.h"
#include "RTCommon.h"

#include <thread>
#include <mutex>
#include <memory>

struct SolverInput
{
    float simulationTime;
    float timeStep;
    size_t numRays;
    float worldScale;
    
    const Source* source;
    const Listener* listener;
    const Room* room;
};


class Solver
{
private:
    static const float C;
    bool _simulationActive = true;
    bool _simulationPaused = false;
    bool _stopSimulationRequested = false;

    std::vector<Ray> _rays;
    std::vector<Ray> _raySnapshot;
    
    float       _currentTime;
    SolverInput _simParameters;
    
    bool        _snapshotRequested = false;
    bool        _snapshotIsReady = false;
    
    mutable std::mutex  _simLock;
    std::mutex  _snapshotDoneMutex;
    
    void detectCollisionWithWallAndReflect(Ray& ray);
    void detectListenerCollision();
    void reflectRay(const ofVec2f& wallUnitVec, Ray& ray);
    
    void simulationLoop();
    
public:
    
    void    update();
    float   getSimulationTime() const;
    bool    getSimulationStatus() const;
    bool    startSimulation(SolverInput parameters);
    void    pauseSimulation(bool pause);
    void    requestSimulationStop();
    void    reset();
    
    void    requestSimulationSnapshot();
    
    bool    getRays(std::vector<Ray>& destinationVec);
    
    const ofVec2f&   getRay() const { return _rays.at(0).getPosition(); }   // Debug only
    std::vector<float>& getImpulseResponse(const size_t listenerID);
//    const std::vector<float>& getImpulseResponse(const Direction& dir);
};

#endif
