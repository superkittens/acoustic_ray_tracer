//
//  Plotter.cpp
//  acoustic_raytracer
//
//  Created by Allen Lee on 2022-02-09.
//

#include "Plotter.hpp"

bool Plotter::setup(const std::string& name, const ofVec2f& origin, const ofVec2f& dimensions)
{
    _plotName = name;
    _windowOrigin = origin;
    _windowDimensions = dimensions;
    
    return true;
}

void Plotter::draw(const std::vector<float>& samples) const
{
    if (_isVisible && !samples.empty())
    {
        drawWindowAndAxes();
        ofSetColor(PINK);
        ofSetLineWidth(2);
        
        auto maxElement = std::max_element(begin(samples), end(samples), [] (float a, float b) { return std::abs(a) < std::abs(b); });
        const float graphMidPointY = _windowOrigin.y + _windowDimensions.y / 2.0;
        
        //  We will need to compress the graph data if the number of samples exceeds the window size
        if (*maxElement > 0.0)
        {
            if (samples.size() > _windowDimensions.x)
            {
                float scaleFactor = (_windowDimensions.y / 2.0) / *maxElement;
                const size_t blockSize = (samples.size() / static_cast<size_t>(_windowDimensions.x)) + 1;
                int samplesRemaining = static_cast<int>(samples.size());
                size_t index = 0;
                
                auto startIterator = samples.begin();
                while (samplesRemaining > 0)
                {
                    auto endIterator = startIterator + blockSize;
                    if (samplesRemaining < blockSize)
                        endIterator = samples.end();
                    
                    auto maxIndex = std::max_element(startIterator, endIterator, [] (float a, float b) { return std::abs(a) < std::abs(b); });
                    ofDrawLine(_windowOrigin.x + index, graphMidPointY, _windowOrigin.x + index, graphMidPointY - (*maxIndex * scaleFactor));
                    
                    index++;
                    samplesRemaining -= blockSize;
                    startIterator += blockSize;
                }
            }
            else
            {
                size_t index = 0;
                for (auto& i : samples)
                {
                    ofDrawLine(_windowOrigin.x + index, graphMidPointY, _windowOrigin.x + index, graphMidPointY - (i * 100));
                    index++;
                }
            }
        }
    }
}

void Plotter::drawWindowAndAxes() const
{
    ofSetColor(WHITE);
    ofDrawBitmapString(_plotName, _windowOrigin.x, _windowOrigin.y - 10);
    
    //  Draw window
    ofSetColor(WHITE, 80);
    ofDrawRectangle(_windowOrigin, _windowDimensions.x, _windowDimensions.y);
    
    //  Draw axes
    const float windowCentreY = _windowOrigin.y + _windowDimensions.y / 2;
    
    ofSetColor(WHITE);
    ofSetLineWidth(2);
    ofDrawLine(_windowOrigin.x, windowCentreY, _windowOrigin.x + _windowDimensions.x, windowCentreY);
    ofDrawLine(_windowOrigin.x, _windowOrigin.y, _windowOrigin.x, _windowOrigin.y + _windowDimensions.y);
}
