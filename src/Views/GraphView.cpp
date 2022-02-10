//
//  GraphView.cpp
//  acoustic_raytracer
//
//  Created by Allen Lee on 2022-02-09.
//

#include "GraphView.hpp"

const ofVec2f GraphView::_PLOT_DIMENSIONS = ofVec2f{500, 500};
const ofVec2f GraphView::_LEFT_PLOT_ORIGIN = ofVec2f{300, 1020};
const ofVec2f GraphView::_RIGHT_PLOT_ORIGIN = ofVec2f{_LEFT_PLOT_ORIGIN.x + _PLOT_DIMENSIONS.x + 100, _LEFT_PLOT_ORIGIN.y};

void GraphView::setup()
{
    _leftPlot.setup("Left IR", _LEFT_PLOT_ORIGIN, _PLOT_DIMENSIONS);
    _rightPlot.setup("Right IR", _RIGHT_PLOT_ORIGIN, _PLOT_DIMENSIONS);
    
    _leftPlot.setVisible(true);
    _rightPlot.setVisible(true);
}

void GraphView::draw(const std::vector<float>& leftIR, const std::vector<float>& rightIR) const
{
    _leftPlot.draw(leftIR);
    _rightPlot.draw(rightIR);
}
