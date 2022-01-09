#include "Solver.h"


const size_t Solver::NUM_RAYS = 1;

Solver::Solver(const World* world, std::shared_ptr<Listener> listener, std::shared_ptr<Emitter> emitter, float timeStep, float maxSimulationTime) : _timeStep{timeStep}, _maxSimulationTime{maxSimulationTime}, _world{world}, _listener{listener}, _emitter{emitter}
{
    //  Create the rays originating from the emitter position
    //  The velocity and attenuation parameters are world dependent and we need to calculate them accordingly
    const float distanceTravelledPerIteration = timeStep * world->getSpeedOfSound();
    const ofVec2f velocity = (distanceTravelledPerIteration / world->WORLD_SCALE) * ofVec2f(0.707, 0.707);

    _rays.push_back(Ray(velocity, emitter->getCoordinates(), distanceTravelledPerIteration));
}

void Solver::update()
{
    for (auto& ray : _rays)
    {
        detectCollisionAndReflect(ray);
        ray.update();
    }
}

void Solver::draw() const
{
    for (auto& ray : _rays)
        ray.draw();
}

//  Ray reflection uses the Householder reflection matrix to determine the new velocity vector for a ray
//  This could benefit from SIMD I think
void Solver::reflectRay(const ofVec2f& wallUnitVec, Ray& ray)
{
    //  Move ray back one iteration
    ofVec2f prevRayPosition = ray.getPosition() - ray.getVelocity();
    ray.setPosition(prevRayPosition);

    float wallLengthSqured = wallUnitVec.lengthSquared();
    float n = (2 * (wallUnitVec.x * wallUnitVec.x) / wallLengthSqured) - 1;
    float m = 2 * (wallUnitVec.x * wallUnitVec.y) / wallLengthSqured;
    float o = (2 * (wallUnitVec.y * wallUnitVec.y) / wallLengthSqured) - 1;

    float vx = (n * ray.getVelocity().x) + (m * ray.getVelocity().y);
    float vy = (m * ray.getVelocity().x) + (o * ray.getVelocity().y);

    ray.setVelocity(ofVec2f(vx, vy));
}

void Solver::detectCollisionAndReflect(Ray& ray)
{
    //  Check to see if a ray has collided with a wall
    const auto walls = _world->getWalls();

    for (const auto &w : walls)
    {
        //  If a ray has collided with a wall, reflect it
        if (w.isPointOutsideWall(ray.getPosition()))
            reflectRay(w.getUnitVector(), ray);
    }
}