//
//  Plotter.hpp
//  acoustic_raytracer
//
//  Created by Allen Lee on 2022-02-09.
//

#ifndef Plotter_hpp
#define Plotter_hpp

#include <stdio.h>
#include "ofMain.h"
#include "RTCommon.h"

class Plotter
{
protected:
    ofVec2f _windowDimensions;
    ofVec2f _windowOrigin;
    
    std::string _plotName;
    
    bool    _isVisible;
    
    void    drawWindowAndAxes() const;
    
public:
    bool    setup(const std::string& name, const ofVec2f& origin, const ofVec2f& dimensions);
    void    draw(const std::vector<float>& samples) const;
    void    setVisible(bool visible) { _isVisible = visible; }
    bool    isVisible() const { return _isVisible; }
};

#endif /* Plotter_hpp */
