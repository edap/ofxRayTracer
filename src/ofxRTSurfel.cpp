#include "ofxRTSurfel.h"

ofxRTSurfel::ofxRTSurfel(const glm::vec3& _faceNormal, const glm::vec3& _rayDirection, const glm::vec3 _position, const ofFloatColor _color){
    geometricNormal = _faceNormal;
    shadingNormal = _faceNormal; // TODO, this should be calculated, for example from a bump map
    position = _position;
//  We'll allow all of our triangles to be Òtwo sidedÓ for now, so that we see consistent results from the front and back of the triangle. When you detect a hit on the triangle, if the dot product of the ray direction and the counter-clockwise normal is positive, then the ray actually struck the triangle from behind.
    if(glm::dot(_faceNormal, _rayDirection) >= 0){
        backface = true;
    }
    color = glm::vec3(_color.r,_color.g,_color.b);

}

glm::vec3 ofxRTSurfel::emittedRadiance(glm::vec3 wo) const {
    return glm::vec3(0.f,0.f,0.f); //material is not emissive
};

glm::vec3 ofxRTSurfel::finiteScatteringDensity(const glm::vec3& w_i, const glm::vec3& w_o) const {
    //easy for now. TODO, implement different reflections
    return lambertianReflectivity();
}

glm::vec3 ofxRTSurfel::getColor() const {
    return color;
}

// From http://graphicscodex.com/projects/rays/
// "The simplest material parameter is to set the G3D::UniversalSurfel::lambertianReflectivity to the color that you want the object to appear."
glm::vec3 ofxRTSurfel::lambertianReflectivity() const {
    return color;
}
