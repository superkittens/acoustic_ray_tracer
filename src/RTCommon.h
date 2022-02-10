//
//  RTCommon.h
//  acoustic_raytracer
//
//  Created by Allen Lee on 2022-02-04.
//

#ifndef RTCommon_h
#define RTCommon_h

#define WHITE   ofColor(255, 255, 255)
#define PINK    ofColor(210, 84, 143)
#define RED     ofColor(236, 106, 94)
#define YELLOW  ofColor(244, 190, 79)
#define GRAY    ofColor(127, 127, 127)
#define ORANGE  ofColor(215, 95, 0)
#define GREEN   ofColor(97, 197, 85)

typedef enum
{
    START = 0,
    ROOM_BUILD,
    NORMAL,
    SIM_RUNNING,
    SIM_PAUSED,
    SIM_DONE
}RTState;

#endif /* RTCommon_h */
