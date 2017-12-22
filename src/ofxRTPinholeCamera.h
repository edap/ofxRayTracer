#pragma once
#include "ofMain.h"

class ofxRTPinholeCamera {
public:
    ofxRTPinholeCamera();
    void draw(); //just for debugging purposes
    glm::vec3 centerOfProjection;
    void getPrimaryRay(double x, double y, int width, int height, glm::vec3& P, glm::vec3& w) const;
    int getSamplesPerPixel() const;

protected:
    float verticalFieldOfView; //angle y0
    float z_near;
    int total_samples = 16;
};
