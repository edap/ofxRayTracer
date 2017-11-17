#include "ofxRTSampler.h"

// http://corysimon.github.io/articles/uniformdistn-on-sphere/
void ofxRTSampler::cosineHemisphere(int n_rays, glm::vec3 dir, glm::vec3 pos){
    int lenght = 20;
    for(int i = 0; i < n_rays; i++){
        glm::vec3 rdir = getRandomDir();

        float acos = glm::dot(dir, rdir);
        glm::vec3 spos = pos + rdir * lenght;
        if(acos > 0){
            ofDrawSphere(spos, 1);
        }

    }
}

const glm::vec3 ofxRTSampler::getRandomDir(){
    float x = ofRandom(-1.0f, 1.0f);
    float y = ofRandom(-1.0f, 1.0f);
    float z = ofRandom(-1.0f, 1.0f);
    return glm::normalize(glm::vec3(x, y, z));
}

