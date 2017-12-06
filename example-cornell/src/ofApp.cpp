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
    vector<string> options = {"1x1", "120x75", "320x200", "640x400","800x600", "1280x768"};
    availableResolution = prepareResolutions();
    gui = new ofxDatGui( ofxDatGuiAnchor::TOP_RIGHT );
    ambientBias.set("Ambient bias", 0.2, 0.1, 0.6);
    gui->setAutoDraw(false);
    gui->addTextInput("message", "Ray Casting");
    gui->addDropdown("Resolution", options);
    gui->addSlider("indirect rays per pixel", 0, 2048);
    gui->addSlider(ambientBias);
    gui->addToggle("run in parallel", runInParallel);
    gui->addButton("start render");
    gui->onDropdownEvent(this, &ofApp::onResolutionEvent);
    gui->onButtonEvent(this, &ofApp::onRenderEvent);
    gui->onToggleEvent(this, &ofApp::onToggleEvent);
    gui->onSliderEvent(this, &ofApp::onIndRaysEvent);
}

void ofApp::startRender(guiOptions options){
    ofxRTPinholeCamera camera;
    rayTracer.setup(primitives, materials, lights, options.ambientBias);
    image = initImage(options.resolution.width, options.resolution.height);
    auto rect = ofRectangle(0, 0, options.resolution.width, options.resolution.height);
    int n_rays = ceil(options.nIndirectRays);
    cout << runInParallel << endl;
    rayTracer.traceImage(camera, rect, image, runInParallel, n_rays);
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
    //ofDrawBitmapString(ofToString(ofGetFrameRate(),0), 20, 20);
}

void ofApp::onResolutionEvent(ofxDatGuiDropdownEvent e){
    options.resolution = availableResolution[int(e.child)];
}

void ofApp::onToggleEvent(ofxDatGuiToggleEvent e){
    runInParallel = e.checked;
};

void ofApp::onRenderEvent(ofxDatGuiButtonEvent e){
    cout << e.target << endl;
    startRender(options);
}

void ofApp::onIndRaysEvent(ofxDatGuiSliderEvent e){
    if (e.target->is("Ambient bias")){
        options.ambientBias = e.target->getValue();
    }

    if (e.target->is("indirect rays per pixel")){
        options.nIndirectRays = e.target->getValue();
    }

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
    imgDimension veryBig; veryBig.width = 1024; veryBig.height = 640;
    avl[0] = small;
    avl[1] = normal;
    avl[2] = medium;
    avl[3] = large;
    avl[4] = big;
    avl[5] = veryBig;
    return avl;
};

shared_ptr<ofImage> ofApp::initImage(int _width, int _height){
    shared_ptr<ofImage> img = std::make_shared<ofImage>();
    img->allocate(_width, _height, OF_IMAGE_COLOR_ALPHA);
    return img;
}
