#ifndef _SOLVER_H
#define _SOLVER_H

#include "ofMain.h"
#include "World.h"
#include "SourceSink.h"
#include "Ray.h"

class Solver
{
    private:
    static const size_t NUM_RAYS;
    std::vector<Ray> _rays;

    float _currentTime;
    const float _timeStep = 0.f;
    const float _maxSimulationTime;

    const World* _world;
    std::shared_ptr<Listener> _listener;
    std::shared_ptr<Emitter> _emitter;

    void detectCollisionAndReflect(Ray& ray);
    void reflectRay(const ofVec2f& wallUnitVec, Ray& ray);

    public:
    Solver(const World* world, std::shared_ptr<Listener> listener, std::shared_ptr<Emitter> emitter, float timeStep, float maxSimulationTime);
    ~Solver() = default;

    void update();
    void draw() const;
};

#endif