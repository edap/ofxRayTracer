#pragma once
#include "ofMain.h"

class ofxRTRay {
public:
    ofxRTRay(glm::vec3 origin, glm::vec3 direction);
    /* Starting point $P$ */
    glm::vec3   origin;
    /* Unit vector $\w$ */
    glm::vec3  direction;
};
