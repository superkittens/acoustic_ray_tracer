#ifndef _RTMODEL_H
#define _RTMODEL_H

//#include "World.h"
#include "Room.h"
#include "Solver.h"
#include "SourceSink.h"
#include "ofMain.h"

class RTModel
{
    public:
    static const size_t MAX_NUM_LISTENERS;
    static const size_t MAX_NUM_SOURCES;
    
    const   std::vector<ofVec2f>& getRoomVertices() const { return _points; }
    void    addRoomVertex(const ofVec2f& point);
    void    clearRoomVertices() { _points.clear(); }
    
    void        buildRoom(const ofVec2f roomOrigin);
    const Room& getRoom() const { return _room; }
    
    void    setWorldScale(const float scale) { _worldScale = scale; }
    float   getWorldScale() const { return _worldScale; }
    
    void                        addSoundSource();
    std::vector<Source>&        getSoundSources() { return _sources; }
    const std::vector<Source>&  getSoundSources() const { return _sources; }
    
    void    addListener();
    const std::vector<Listener>&    getListeners() const { return _listeners; }
    std::vector<Listener>&          getListeners() { return _listeners; }
    
    void    reset();

    private:
    std::vector<ofVec2f> _points;
    std::vector<Source> _sources;
    std::vector<Listener> _listeners;
    float _worldScale = 0.01;
    
    Room _room;
};

#endif
