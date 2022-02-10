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
                if (_iteration >= _totalIterations)
                {
                    _simulationActive = false;
                    break;
                }
                
                detectListenerCollision();
                
                //  Update rays
                for (auto& ray : _rays)
                {
                    detectCollisionWithWallAndReflect(ray);
                    ray.update();
                }
                
                _currentTime += _simParameters.timeStep;
                _iteration += 1;
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
    if (parameters.listener == nullptr || parameters.source == nullptr)
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
    
    //  Reserve memory for IRs
    const float numSamples = (parameters.simulationTime / parameters.timeStep) + 1.0;
    _irLeft = std::move(std::vector<float>(static_cast<size_t>(numSamples), 0.0));
    _irRight = std::move(std::vector<float>(static_cast<size_t>(numSamples), 0.0));
    _totalIterations = static_cast<size_t>(numSamples);
    
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

bool Solver::getSnapshotData(std::vector<Ray>& raysDest, std::vector<float>& irLeftDest, std::vector<float>& irRightDest)
{
    std::lock_guard<std::mutex> guard(_simLock);
    
    if (raysDest.empty())
        std::copy(begin(_rays), end(_rays), std::back_inserter(raysDest));
    else
        std::copy(begin(_rays), end(_rays), begin(raysDest));
    
    std::copy(begin(_irLeft), end(_irLeft), begin(irLeftDest));
    std::copy(begin(_irRight), end(_irRight), begin(irRightDest));
    
    return true;
}

void Solver::reset()
{
    _simulationActive = false;
    _simulationPaused = false;
    _stopSimulationRequested = false;
    _currentTime = 0.0;
    _iteration = 0;
    _totalIterations = 0;
    
    _raySnapshot.clear();
    _rays.clear();
    _irLeft.clear();
    _irRight.clear();
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
    float summedRaysLeft = 0.f;
    float summedRaysRight = 0.f;
    
    //  TODO: [Opt] Don't check every single ray.  Only the ones close to reaching the listener
    for (auto& ray : _rays)
    {
        //  Check to see if the ray has reached the listener
        if (ray.getActiveStatus())
        {
            auto collidedPair = _simParameters.listener->checkRayCollision(ray.getPosition());
            
            bool didCollide = std::get<0>(collidedPair);
            Direction collisionDirection = std::get<1>(collidedPair);
            
            if (didCollide)
            {
                if (collisionDirection == LEFT)
                    summedRaysLeft += ray.getLevel();
                else
                    summedRaysRight += ray.getLevel();
                
                //  TODO:  [Phy] Don't deactivate?  Instead attenuate and continue propagation
                //  Deactive ray
                //ray.setInactive();
            }
        }
    }
    
    //  Store summedRays into IR
    _irLeft.at(_iteration) = summedRaysLeft;
    _irRight.at(_iteration) = summedRaysRight;
}
