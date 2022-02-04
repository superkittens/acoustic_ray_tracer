 #include "Solver.h"

const float Solver::C = 343.0;

// void Solver::update()
// {
//     if (_simulationActive)
//     {
//         float summedRaysLeft = 0.f;
//         float summedRaysRight = 0.f;
//         float numLeftCollisions = 0;
//         float numRightCollisions = 0;
//
//         for (auto &ray : _rays)
//         {
//             detectCollisionAndReflect(ray);
//
//             //  Check to see if any rays have reached the listener
//             if (ray.getActiveStatus())
//             {
//                 auto collided = _listener->checkRayCollision(ray.getPosition());
//                 if (collided.first)
//                 {
//                     ray.setInactive();
//
//                     if (collided.second == LEFT)
//                     {
//                         summedRaysLeft += ray.getLevel();
//                         numLeftCollisions += 1;
//                     }
//                     if (collided.second == RIGHT)
//                     {
//                         summedRaysRight += ray.getLevel();
//                         numRightCollisions += 1;
//                     }
//                 }
//             }
//             ray.update();
//         }
//
//         float leftAverage = 0.f;
//         float rightAverage = 0.f;
//
//         if (numLeftCollisions > 0)
//             leftAverage = summedRaysLeft / numLeftCollisions;
//         if (numRightCollisions > 0)
//             rightAverage = summedRaysRight / numRightCollisions;
//
//         _leftIR.push_back(leftAverage);
//         _rightIR.push_back(rightAverage);
//
//         _outputFileLeft << to_string(leftAverage) << '\n';
//         _outputFileRight << to_string(rightAverage) << '\n';
//
//         _currentTime += _timeStep;
//         if (_currentTime >= _maxSimulationTime)
//         {
//             _simulationActive = false;
//             _outputFileLeft.close();
//             _outputFileRight.close();
//         }
//     }
// }

void Solver::simulationLoop()
{
    while(_simulationActive)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}


bool Solver::startSimulation(SolverInput parameters)
{
    if (parameters.listeners == nullptr)
        return false;
    
    _simParameters = parameters;
    
    //  Create rays
    const float distanceTravelledPerIteration = _simParameters.timeStep * C;
    const float angleDelta = 2.0 * M_PI / _simParameters.numRays;
    float angle = 0.0;
    
    for (auto i = 0; i < _simParameters.numRays; ++i)
    {
        const ofVec2f velocity = (distanceTravelledPerIteration * _simParameters.worldScale) * ofVec2f(cosf(angle), sinf(angle));
        _rays.push_back(Ray(velocity, _simParameters.source->getCoordinates(), distanceTravelledPerIteration));
        angle += angleDelta;
    }
    
    std::thread sim_thread([&]{ simulationLoop(); });
    sim_thread.detach();
    
    return true;
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
     const auto walls = _simParameters.room->getWalls();

     for (const auto &w : walls)
     {
         //  If a ray has collided with a wall, reflect it
         if (w.isPointOutsideWall(ray.getPosition()))
         {
             ray.signalTrajectoryChange();
             reflectRay(w.getUnitVector(), ray);
         }
     }
 }
