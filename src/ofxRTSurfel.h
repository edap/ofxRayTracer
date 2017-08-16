#pragma once
#include "ofMain.h"

//All the position that this class knows has to be global positions

class ofxRTSurfel {
public:
    ofxRTSurfel(const glm::vec3& _faceNormal, const glm::vec3& _rayDirection, const glm::vec3 position, const ofFloatColor color);
    virtual ~ofxRTSurfel() {};
    glm::vec3 getPosition() const { return position; };
    glm::vec3 getGeometricNormal() const { return geometricNormal; };
    glm::vec3 getColor() const;
    glm::vec3 finiteScatteringDensity(const glm::vec3& w_i, const glm::vec3& w_o) const;
    glm::vec3 emittedRadiance(glm::vec3 wo) const;
    glm::vec3 lambertianReflectivity() const;

private:
    glm::vec3 geometricNormal;
    glm::vec3 position;
    glm::vec3 color;
    //float light;

    //The normal to the patch for shading purposes, i.e., after normal mapping.
    //e.g., the interpolated vertex normal or normal-mapped normal.
    //Always a unit vector.
    glm::vec3 shadingNormal; // this needs to be calculated

    bool backface = false;

};
