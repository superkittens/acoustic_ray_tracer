#ifndef _RTCONTROLLER_H
#define _RTCONTROLLER_H

#include "WorldView.h"

class RTController
{
    public:
    void draw() const;
    void mouseMoved(const ofVec2f& position);
    void mouseClicked(const ofVec2f& position);
    void mouseDragged(const ofVec2f& position);

    private:
    WorldView _worldView;
};

#endif