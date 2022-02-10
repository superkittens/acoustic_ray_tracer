//
//  GraphView.hpp
//  acoustic_raytracer
//
//  Created by Allen Lee on 2022-02-09.
//

#ifndef GraphView_hpp
#define GraphView_hpp

#include <stdio.h>
#include "Plotter.hpp"

class GraphView
{
protected:
    static const ofVec2f _LEFT_PLOT_ORIGIN;
    static const ofVec2f _RIGHT_PLOT_ORIGIN;
    static const ofVec2f _PLOT_DIMENSIONS;
    
    Plotter _leftPlot, _rightPlot;
    
public:
    void setup();
    void reset();
    void draw(const std::vector<float>& leftIR, const std::vector<float>& rightIR) const;
};

#endif /* GraphView_hpp */
