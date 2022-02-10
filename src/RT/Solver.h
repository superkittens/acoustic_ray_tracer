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
    std::vector<float> _irLeft, _irRight;
    std::vector<float> _irLeftSnapshot, _irRightSnapshot;
    
    float       _currentTime;
    size_t      _iteration;
    size_t      _totalIterations;
    SolverInput _simParameters;
    
    mutable std::mutex  _simLock;
    std::mutex          _snapshotDoneMutex;
    
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
    
    bool    getSnapshotData(std::vector<Ray>& raysDest, std::vector<float>& irLeftDest, std::vector<float>& irRightdest);
    
    const ofVec2f&   getRay() const { return _rays.at(0).getPosition(); }   // Debug only
//    const std::vector<float>& getImpulseResponse(const Direction& dir);
};

#endif
