#pragma once
#include "ofMain.h"

class ofxRTPinholeCamera {
public:
    ofxRTPinholeCamera();
    void draw(); //just for debugging purposes
    glm::vec3 centerOfProjection;
    void getPrimaryRay(float x, float y, int width, int height, glm::vec3& P, glm::vec3& w) const;

protected:
    float verticalFieldOfView; //angle y0
    float z_near;
};
