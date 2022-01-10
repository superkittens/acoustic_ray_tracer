#ifndef _SOLVER_H
#define _SOLVER_H

#include "ofMain.h"
#include "World.h"
#include "SourceSink.h"
#include "Ray.h"
#include <fstream>

class Solver
{
    private:
    bool _simulationActive = true;
    static const float NUM_RAYS;
    std::vector<Ray> _rays;

    float _currentTime;
    const float _timeStep = 0.f;
    const float _maxSimulationTime;

    std::vector<float> _leftIR;
    std::vector<float> _rightIR;

    const World* _world;
    std::shared_ptr<Listener> _listener;
    std::shared_ptr<Emitter> _emitter;

    std::ofstream _outputFileLeft;
    std::ofstream _outputFileRight;

    void detectCollisionAndReflect(Ray& ray);
    void detectListenerCollision(Ray& ray);
    void reflectRay(const ofVec2f& wallUnitVec, Ray& ray);

    public:
    Solver(const World* world, std::shared_ptr<Listener> listener, std::shared_ptr<Emitter> emitter, float timeStep, float maxSimulationTime);
    ~Solver() = default;

    void    update();
    void    draw() const;
    float   getSimulationTime() const { return _currentTime; }
    bool    getSimulationStatus() const { return _simulationActive; }
    void    pauseSimulation() { _simulationActive = false; }
    void    restartSimulation() { _simulationActive = true; }
    const std::vector<float>& getImpulseResponse(const Direction& dir);
};

#endif