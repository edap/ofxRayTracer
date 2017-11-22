#pragma once
#include "ofMain.h"
#include "ofxRTSurfel.h"
#include "ofxRTPinholeCamera.h"
#include "ofxAssimpModelLoader.h"
#include "ofxRTRay.h"
#include "ofxRTConst.h"
#include "tbb/parallel_for.h"

// It takes a primary ray, it intersect it with a scene and it return a pointer to a surface element.
// A surface element (“surfel”) [Pfister2000Surfels] contains the intersection position, normal, and material information
// that will be useful for shading.
// If there is no intersection, then the pointer returned will be NULL. A NULL shared_ptr casts to the boolean false value.

class ofxRayTracer {
public:
    ofxRayTracer();
    // when you will pass a model from assimp,
    // remember this: https://github.com/openframeworks/openFrameworks/issues/2989
    void setup(const vector<of3dPrimitive>& primitives, const vector<ofMaterial>& materials,const vector<ofLight>& lights);
    //iterates overall pixels calling traceRay
    void traceImage(const ofxRTPinholeCamera& camera, ofRectangle& rectangle, shared_ptr<ofImage>& image, bool& parallel);
protected:
    vector<ofLight> lights;
    vector<of3dPrimitive> primitives;
    vector<ofMaterial> materials;
    uint64_t renderTimeInMilliseconds;

    shared_ptr<ofxRTSurfel> findFirstIntersectionWithThePrimitives(const ofxRTRay& ray) const;
    ofColor L_i(const ofxRTRay& ray) const;
    // Find the first intersection with the scene
    bool rayTriangleIntersect(const glm::vec3& P, const glm::vec3& w, const vector<glm::vec3> v, float baricenter[3], float& t) const;

    glm::vec3 getPointOnTriangle(const ofxRTRay& _ray, const glm::vec3& _baryPosition) const;
    ofColor L_0(const shared_ptr<ofxRTSurfel>& surfelY, const glm::vec3 ray_direction_inverted) const;
    bool visible(const glm::vec3& surfelPos, const glm::vec3& wi, const float& distanceToLight) const;
    ofFloatColor L_scatteredDirect(const shared_ptr<ofxRTSurfel>& surfelX,const glm::vec3 wo) const;

    ofFloatColor getColor(const ofMeshFace& face, int indexMeshes) const;
    void displayTime(uint64_t ellapsed) const;


    void cosineSampleHemisphere(int n_rays, glm::vec3 dir, glm::vec3 pos);
    glm::vec3 getRandomDir() const;

};
