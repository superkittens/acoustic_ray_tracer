 #include "Solver.h"

const float Solver::C = 343.0;

 void Solver::update()
 {
//     if (_simulationActive && !_simulationPaused)
//     {
//         for (auto& ray : _rays)
//         {
//             detectCollisionWithWallAndReflect(ray);
//             ray.update();
//         }
//     }
 }

float Solver::getSimulationTime() const
{
    std::lock_guard<std::mutex> guard(_simLock);
    return _currentTime;
}

bool Solver::getSimulationStatus() const
{
    std::lock_guard<std::mutex> guard(_simLock);
    return _simulationActive;
}

void Solver::simulationLoop()
{
    while (1)
    {
        std::lock_guard<std::mutex> guard(_simLock);
        if (_simulationActive)
        {
            if (!_simulationPaused)
            {
                //  If the snapshot of the simulation is requested, peel off a copy of the states of the rays
                if (_snapshotRequested)
                {
                    _raySnapshot.clear();
                    for (const auto& ray : _rays)
                        _raySnapshot.push_back(ray);
                    
                    _snapshotRequested = false;
                    
                    std::lock_guard<std::mutex> readyGuard(_snapshotDoneMutex);
                    _snapshotIsReady = true;
                }
                
                //  Update rays
                for (auto& ray : _rays)
                {
                    detectCollisionWithWallAndReflect(ray);
                    ray.update();
                }
                
                _currentTime += _simParameters.timeStep;
                
                if (_currentTime >= _simParameters.simulationTime)
                {
                    _simulationActive = false;
                    break;
                }
            }
            
            if (_stopSimulationRequested)
            {
                _simulationActive = false;
                break;
            }
        }
    }
}


bool Solver::startSimulation(SolverInput parameters)
{
    if (parameters.listeners == nullptr)
        return false;
    
    reset();
    
    _simParameters = parameters;
    
    //  Create rays
    const float distanceTravelledPerIteration = _simParameters.timeStep * C;
    const float angleDelta = 2.0 * M_PI / _simParameters.numRays;
    float angle = 0.0;
    
    for (auto i = 0; i < _simParameters.numRays; ++i)
    {
        const ofVec2f velocity = (distanceTravelledPerIteration / _simParameters.worldScale) * ofVec2f(cosf(angle), sinf(angle));
        _rays.push_back(Ray(velocity, _simParameters.source->getCoordinates(), distanceTravelledPerIteration));
        angle += angleDelta;
    }
    
    _simulationActive = true;
    
    std::thread sim_thread([&]{ simulationLoop(); });
    sim_thread.detach();
    
    return true;
}

void Solver::pauseSimulation(bool pause)
{
    std::lock_guard<std::mutex> guard(_simLock);
    if (pause)
        _simulationPaused = true;
    else
        _simulationPaused = false;
}

void Solver::requestSimulationStop()
{
    std::lock_guard<std::mutex> guard(_simLock);
    if (!_stopSimulationRequested)
        _stopSimulationRequested = true;
}

void Solver::requestSimulationSnapshot()
{
    std::lock_guard<std::mutex> guard(_simLock);
    _snapshotRequested = true;
}

bool Solver::getRays(std::vector<Ray>& destinationVec)
{
    std::lock_guard<std::mutex> guard(_snapshotDoneMutex);
    if (_snapshotIsReady)
    {
        destinationVec = std::move(_raySnapshot);
        _snapshotIsReady = false;
        
        return true;
    }
    return false;
}

void Solver::reset()
{
    _simulationActive = false;
    _simulationPaused = false;
    _snapshotRequested = false;
    _snapshotIsReady = false;
    _stopSimulationRequested = false;
    _currentTime = 0.0;
    
    _raySnapshot.clear();
    _rays.clear();
    
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

 void Solver::detectCollisionWithWallAndReflect(Ray& ray)
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

void Solver::detectListenerCollision()
{
    for (auto& listener : *_simParameters.listeners)
    {
        float summedRaysLeft = 0.f;
        float summedRaysRight = 0.f;
        //                    float numLeftCollisions = 0;
        //                    float numRightCollisions = 0;
        
        for (auto& ray : _rays)
        {
            //  Check to see if the ray has reached the listener
            if (ray.getActiveStatus())
            {
                auto collidedPair = listener.checkRayCollision(ray.getPosition());
                
                bool didCollide = std::get<0>(collidedPair);
                Direction collisionDirection = std::get<1>(collidedPair);
                
                if (didCollide)
                {
                    auto collidedListeners = ray.getListOfCollidedListeners();
                    auto index = std::find(collidedListeners.begin(), collidedListeners.end(), listener.getId());
                    if (index == collidedListeners.end())
                    {
                        ray.addCollidedListenerToRay(listener.getId());
                        
                        if (collisionDirection == LEFT)
                            summedRaysLeft += ray.getLevel();
                        else
                            summedRaysRight += ray.getLevel();
                    }
                }
                
                //  Deactive ray when it reaches all listeners
                if (ray.getListOfCollidedListeners().size() == _simParameters.listeners->size())
                    ray.setInactive();
            }
        }
        
        //  Store summedRays into IR
        listener.addSampleToIR(LEFT, summedRaysLeft);
        listener.addSampleToIR(RIGHT, summedRaysRight);
    }
}
