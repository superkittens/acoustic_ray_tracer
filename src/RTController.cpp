
#include "RTController.h"

void RTController::mouseMoved(const ofVec2f& position)
{
    _worldView.setCursor(position);
}

void RTController::draw() const
{
    _worldView.drawRoomSoFar();
}