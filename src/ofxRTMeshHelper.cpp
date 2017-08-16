#include "ofxRTMeshHelper.h"

of3dPrimitive ofxRTMeshHelper::toPrimitive(const ofMesh& mesh) {
    of3dPrimitive primitive;
    primitive.getMesh().clear();
    primitive.getMesh().append(mesh);
    primitive.getMesh().enableColors();
    primitive.getMesh().enableNormals();
    return primitive;
}

void ofxRTMeshHelper::getPrimitives(ofxAssimpModelLoader& model,
                                               vector<of3dPrimitive>& primitives,
                                               ofNode& parentNode){
    for (int i = 0; i< model.getMeshCount(); i++) {
        auto primitive = ofxRTMeshHelper::toPrimitive(model.getMesh(i));
        primitive.setParent(parentNode);
        primitives.push_back(primitive);
    };
}

void ofxRTMeshHelper::getPrimitivesAndMaterials(ofxAssimpModelLoader& model,
                                                  vector<of3dPrimitive>& primitives,
                                                  vector<ofMaterial>& materials,
                                                  ofNode& parentNode){
    for (int i = 0; i< model.getMeshCount(); i++) {
        auto primitive = ofxRTMeshHelper::toPrimitive(model.getMesh(i));
        primitive.setParent(parentNode);
        primitives.push_back(primitive);

        auto material = model.getMaterialForMesh(i);
        materials.push_back(material);
    };
}

