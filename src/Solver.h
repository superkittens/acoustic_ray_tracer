#ifndef SOLVER_H_
#define SOLVER_H_

#include "ofMain.h"
#include "SourceSink.h"
#include "Room.h"
#include "Ray.h"

#include <thread>

struct SolverInput
{
    float simulationTime;
    float timeStep;
    size_t numRays;
    float worldScale;
    
    const Source* source;
    const std::vector<Listener>* listeners;
    const Room* room;
};


class Solver
{
private:
    static const float C;
    bool _simulationActive = true;
    bool _pauseSimulation = false;

    std::vector<Ray> _rays;
    
    float       _currentTime;
    SolverInput _simParameters;
    
    bool        _snapshotRequested = false;
    bool        _snapshotReady = false;
    
    void detectCollisionAndReflect(Ray& ray);
    void detectListenerCollision(Ray& ray);
    void reflectRay(const ofVec2f& wallUnitVec, Ray& ray);
    
    void simulationLoop();
    
public:
    
    void    update();
    float   getSimulationTime() const { return _currentTime; }
    bool    getSimulationStatus() const { return _simulationActive; }
    bool    startSimulation(SolverInput parameters);
    void    pauseSimulation() { _simulationActive = false; }
    void    restartSimulation() { _simulationActive = true; }
    
    void    requestSimulationSnapshot() { _snapshotRequested = true; }
    //  getRayData();
    std::vector<float>& getImpulseResponse(const size_t listenerID);
//    const std::vector<float>& getImpulseResponse(const Direction& dir);
};

#endif
