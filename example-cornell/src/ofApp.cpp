#include "ofApp.h"



//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(255,255,255);
    ofSetVerticalSync(true);
    ofEnableDepthTest();

    modelCornell.loadModel("CornellBox-Original.obj", 20);
    // set up a scene
    centerOfTheScene.setPosition(0, 0, 0);
    // set the lights
    ofLight light;
    light.setPointLight();
    light.setPosition(0, +0.5, -3.0);
    lights.push_back(light);
    // set the materials used in the debug view
    material.setEmissiveColor(ofFloatColor::red);
    lightDebugColor.setEmissiveColor(ofFloatColor::blue);

    // read the models and fullfill the primitives and the materials vectors
    ofxRTMeshHelper::getPrimitivesAndMaterials(modelCornell, primitives, materials,centerOfTheScene);
    // position the primitives
    centerOfTheScene.move(0, -1, -3);

    // instantiate and position the gui //
    vector<string> options = {"1x1", "120x75", "320x200", "640x400","800x600"};
    availableResolution = prepareResolutions();
    gui = new ofxDatGui( ofxDatGuiAnchor::TOP_RIGHT );
    gui->setAutoDraw(false);
    gui->addTextInput("message", "Ray Casting");
    gui->addDropdown("Resolution", options);
    gui->addSlider("indirect rays per pixel", 0, 2048);
    gui->addButton("start render");
    gui->onDropdownEvent(this, &ofApp::onResolutionEvent);
    gui->onButtonEvent(this, &ofApp::onRenderEvent);
    gui->onSliderEvent(this, &ofApp::onIndRaysEvent);
}

void ofApp::startRender(guiOptions options){
    ofxRTPinholeCamera camera;
    rayTracer.setup(primitives, materials, lights);
    image = initImage(options.resolution.width, options.resolution.height);
    auto rect = ofRectangle(0, 0, options.resolution.width, options.resolution.height);
    rayTracer.traceImage(camera, rect, image);
}

//--------------------------------------------------------------
void ofApp::draw(){
    if (show3DScene) {
        cam.begin();
        lights[0].enable();
        lightDebugColor.begin();
        for(auto l:lights) {
            auto pos = l.getGlobalPosition();
            ofDrawSphere(pos.x, pos.y, pos.z, 0.2);
        }
        lightDebugColor.end();
        material.begin();
        for(of3dPrimitive primitive: primitives){
            primitive.draw();
        }
        material.end();
        lights[0].disable();
        ofDrawAxis(100);
        cam.end();
    } else {
        if (image && image->isAllocated()) {
            image->draw(10,10, 640, 400);
        }
        ofDisableDepthTest();
        gui->draw();
        ofEnableDepthTest();
    }
    ofDrawBitmapString(ofToString(ofGetFrameRate(),0), 20, 20);
}

void ofApp::onResolutionEvent(ofxDatGuiDropdownEvent e){
    options.resolution = availableResolution[int(e.child)];
}

void ofApp::onRenderEvent(ofxDatGuiButtonEvent e){
    cout << e.target << endl;
    startRender(options);
}

void ofApp::onIndRaysEvent(ofxDatGuiSliderEvent e){
    options.nIndirectRays = e.target->getValue();
    if (e.target->is("datgui opacity")) gui->setOpacity(e.scale);

}

//--------------------------------------------------------------
void ofApp::update(){
    gui->update();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}

map<int, imgDimension> ofApp::prepareResolutions(){
    map<int, imgDimension> avl;
    imgDimension small; small.width = 1; small.height = 1;
    imgDimension normal; normal.width = 120; normal.height = 75;
    imgDimension medium; medium.width = 320; medium.height = 200;
    imgDimension large; large.width = 640; large.height = 400;
    imgDimension big; big.width = 800; big.height = 600;
    avl[0] = small;
    avl[1] = normal;
    avl[2] = medium;
    avl[3] = big;
    avl[4] = large;
    return avl;
};

shared_ptr<ofImage> ofApp::initImage(int _width, int _height){
    shared_ptr<ofImage> img = std::make_shared<ofImage>();
    img->allocate(_width, _height, OF_IMAGE_COLOR);
    return img;
}
