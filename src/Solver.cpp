// #include "Solver.h"


// const float Solver::NUM_RAYS = 100;

// Solver::Solver(const World* world, std::shared_ptr<Listener> listener, std::shared_ptr<Emitter> emitter, float timeStep, float maxSimulationTime) : _timeStep{timeStep}, _maxSimulationTime{maxSimulationTime}, _world{world}, _listener{listener}, _emitter{emitter}
// {
//     //  Create the rays originating from the emitter position
//     //  The velocity and attenuation parameters are world dependent and we need to calculate them accordingly
//     const float distanceTravelledPerIteration = timeStep * world->getSpeedOfSound();

//     const float angleDelta = 2 * M_PI / NUM_RAYS;
//     float angle = 0;

//     for (size_t i = 0; i < (size_t)NUM_RAYS; ++i)
//     {
//         const ofVec2f velocity = (distanceTravelledPerIteration * world->WORLD_SCALE) * ofVec2f(cosf(angle), sinf(angle));
//         _rays.push_back(Ray(velocity, emitter->getCoordinates(), distanceTravelledPerIteration));
//         angle += angleDelta;
//     }

//     _outputFileLeft.open("");
//     _outputFileRight.open("");
// }

// void Solver::update()
// {
//     if (_simulationActive)
//     {
//         float summedRaysLeft = 0.f;
//         float summedRaysRight = 0.f;
//         float numLeftCollisions = 0;
//         float numRightCollisions = 0;

//         for (auto &ray : _rays)
//         {
//             detectCollisionAndReflect(ray);

//             //  Check to see if any rays have reached the listener
//             if (ray.getActiveStatus())
//             {
//                 auto collided = _listener->checkRayCollision(ray.getPosition());
//                 if (collided.first)
//                 {
//                     ray.setInactive();

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

//         float leftAverage = 0.f;
//         float rightAverage = 0.f;

//         if (numLeftCollisions > 0)
//             leftAverage = summedRaysLeft / numLeftCollisions;
//         if (numRightCollisions > 0)
//             rightAverage = summedRaysRight / numRightCollisions;

//         _leftIR.push_back(leftAverage);
//         _rightIR.push_back(rightAverage);

//         _outputFileLeft << to_string(leftAverage) << '\n';
//         _outputFileRight << to_string(rightAverage) << '\n';

//         _currentTime += _timeStep;
//         if (_currentTime >= _maxSimulationTime)
//         {
//             _simulationActive = false;
//             _outputFileLeft.close();
//             _outputFileRight.close();
//         }
//     }
// }

// void Solver::draw() const
// {
//     for (auto& ray : _rays)
//         ray.draw();
// }

// const std::vector<float>& Solver::getImpulseResponse(const Direction& dir)
// {
//     if (dir == LEFT)
//         return _leftIR;
    
//     return _rightIR;
// }

// //  Ray reflection uses the Householder reflection matrix to determine the new velocity vector for a ray
// //  This could benefit from SIMD I think
// void Solver::reflectRay(const ofVec2f& wallUnitVec, Ray& ray)
// {
//     //  Move ray back one iteration
//     ofVec2f prevRayPosition = ray.getPosition() - ray.getVelocity();
//     ray.setPosition(prevRayPosition);

//     float wallLengthSqured = wallUnitVec.lengthSquared();
//     float n = (2 * (wallUnitVec.x * wallUnitVec.x) / wallLengthSqured) - 1;
//     float m = 2 * (wallUnitVec.x * wallUnitVec.y) / wallLengthSqured;
//     float o = (2 * (wallUnitVec.y * wallUnitVec.y) / wallLengthSqured) - 1;

//     float vx = (n * ray.getVelocity().x) + (m * ray.getVelocity().y);
//     float vy = (m * ray.getVelocity().x) + (o * ray.getVelocity().y);

//     ray.setVelocity(ofVec2f(vx, vy));
// }

// void Solver::detectCollisionAndReflect(Ray& ray)
// {
//     //  Check to see if a ray has collided with a wall
//     const auto walls = _world->getWalls();

//     for (const auto &w : walls)
//     {
//         //  If a ray has collided with a wall, reflect it
//         if (w.isPointOutsideWall(ray.getPosition()))
//         {
//             ray.signalTrajectoryChange();
//             reflectRay(w.getUnitVector(), ray);
//         }
//     }
// }

// // void Solver::detectListenerCollision(Ray& ray)
// // {
// //     float summedLevelLeft = 0.f;
// //     float summedLevelRight = 0.f;

// //     auto collided = _listener->checkRayCollision(ray.getPosition());
    
// //     //  If there is a collision, then get the direction, add it to the impulse reponse and inactivate ray
// //     if (collided.first)
// //     {
// //         ray.setInactive();
// //         if (collided.second == LEFT)
// //             _leftIR.push_back(ray.getLevel());
// //         if (collided.second == RIGHT)
// //             _rightIR.push_back(ray.getLevel());
// //     }
// //     else
// //     {
// //         _leftIR.push_back(0.f);
// //         _rightIR.push_back(0.f);
// //     }
// // }