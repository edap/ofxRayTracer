#include "ofxRTMeshHelper.h"

of3dPrimitive ofxRTMeshHelper::toPrimitive(const ofMesh& mesh) {
    of3dPrimitive primitive;
    primitive.getMesh().clear();
    primitive.getMesh().append(mesh);
    primitive.getMesh().enableColors();
    primitive.getMesh().enableNormals();
    return primitive;
}

void ofxRTMeshHelper::readModelAndGetPrimitives(ofxAssimpModelLoader& model,
                                               vector<of3dPrimitive>& primitives,
                                               ofNode& parentNode){
    for (int i = 0; i< model.getMeshCount(); i++) {
        auto primitive = ofxRTMeshHelper::toPrimitive(model.getMesh(i));
        primitive.setParent(parentNode);
        primitives.push_back(primitive);
    };
}

