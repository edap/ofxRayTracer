#pragma once
#include "ofMain.h"

class ofxRTSampler{
public:
    static void cosineHemisphere(int n_rays, glm::vec3 dir, glm::vec3 pos);
    static const glm::vec3 getRandomDir();
};


