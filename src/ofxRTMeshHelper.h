#pragma once
#include "ofMain.h"
#include "ofxAssimpModelLoader.h"

class ofxRTMeshHelper{
public:
    //get an of3dPrimitive from a mesh
    static of3dPrimitive toPrimitive(const ofMesh& mesh);
    // it fullfills an empty vector of of3dPrimitive
    // with the primitive obtained from an ofxAssimpModelLoader
    // and set as parent node for each primitive, the parentNode
    static void readModelAndGetPrimitives(ofxAssimpModelLoader& model,
                                                vector<of3dPrimitive>& primitives,
                                                ofNode& parentNode);
    static void getPrimitivesAndMaterials(ofxAssimpModelLoader& model,
                                          vector<of3dPrimitive>& primitives,
                                          vector<ofMaterial>& materials,
                                          ofNode& parentNode);
    static void getPrimitives(ofxAssimpModelLoader& model,
                                          vector<of3dPrimitive>& primitives,
                                          ofNode& parentNode);

};
