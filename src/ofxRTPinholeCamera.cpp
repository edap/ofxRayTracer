#include "ofxRTPinholeCamera.h"

//TODO, provide an option struct to the constructor

ofxRTPinholeCamera::ofxRTPinholeCamera(){
    centerOfProjection = glm::vec3(0.0,0.0,0.0);
    z_near =  -1.0;
    verticalFieldOfView = PI/3;
}

void ofxRTPinholeCamera::draw(){
    ofDrawSphere(centerOfProjection.x, centerOfProjection.y, centerOfProjection.z, 10);
}

//The camera must convert a pixel position in the image to a point on the near clipping plane,
//and then to the ray that passes through that point from the center of projection.

// C++ A Camera Model [_rn_camera] from http://graphicscodex.com
/* x, y, width, and height in pixels; P in meters */
void ofxRTPinholeCamera::getPrimaryRay(float x, float y, int width, int height, glm::vec3& P, glm::vec3& w) const {
    // Compute the side of a square at $z = -1$ based on our vertical top-to-bottom field of view
    const float side = -2.0f * tan(verticalFieldOfView / 2.0f);

    // I invert the y-axis because we're moving from the 2D y=down to the 3D y=up coordinate system
    P = glm::vec3( z_near * (x / width - 0.5f) * side * width / height,
               z_near * -(y / height - 0.5f) * side,
               z_near);

    // The incoming direction is simply that from the origin to P
    glm::vec3 dir = P - centerOfProjection;
    w = glm::normalize(dir);
}

