#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "PinholeCamera.h"
#include "ofxDatGui.h"
#include "Surfel.h"
#include "RayCaster.h"
#include "MeshHelper.h"

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


    void startRender(guiOptions opt);
    shared_ptr<ofImage> initImage(int width, int height);

    shared_ptr<ofImage> image;
    ofxDatGui* gui;

    ofxAssimpModelLoader modelTeapot;
    ofxAssimpModelLoader modelCornell;
    vector<of3dPrimitive> primitives;
    vector<ofLight>	lights;
    ofNode centerOfTheScene;
    guiOptions options;

    //debug 3dScene
    ofBoxPrimitive box; //debugging box
    ofPlanePrimitive plane;
    ofMaterial material;
    ofMaterial lightDebugColor;
    ofEasyCam cam;
    bool show3DScene = false;
    bool showCube = false;
    bool showCornell = true;

    //gui helpers
    map<int, imgDimension> availableResolution;
    map<int, imgDimension> prepareResolutions();

};
