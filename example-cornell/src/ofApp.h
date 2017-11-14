#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "ofxRTMeshHelper.h"
#include "ofxRayTracer.h"
#include "ofxRTPinholeCamera.h"
#include "ofxDatGui.h"

struct imgDimension{
    int width;
    int height;
};

struct guiOptions{
    imgDimension resolution;
    int nIndirectRays;
};

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

    void onResolutionEvent(ofxDatGuiDropdownEvent e);
    void onRenderEvent(ofxDatGuiButtonEvent e);
    void onIndRaysEvent(ofxDatGuiSliderEvent e);
    void onToggleEvent(ofxDatGuiToggleEvent e);


    void startRender(guiOptions opt);
    ofxDatGui* gui;
    ofxRayTracer rayTracer;
    // https://forum.openframeworks.cc/t/ray-tracer-implementation/27283/55
    // this problem is still not fixed
    bool runInParallel = false;

    ofxAssimpModelLoader modelCornell;
    vector<of3dPrimitive> primitives;
    vector<ofMaterial> materials;
    vector<ofLight>	lights;
    ofNode centerOfTheScene;
    guiOptions options;

    //debug 3dScene, this is useful when you have to position the camera
    ofMaterial material;
    ofMaterial lightDebugColor;
    ofEasyCam cam;
    bool show3DScene = false;

    //gui helpers
    map<int, imgDimension> availableResolution;
    map<int, imgDimension> prepareResolutions();

    shared_ptr<ofImage> image;
    shared_ptr<ofImage> initImage(int width, int height);

};
