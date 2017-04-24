#pragma once

#include "ofMain.h"

#define MODEL_NUM 7

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
    
    ofEasyCam easyCam;
    ofShader shader;
    ofVboMesh vboMesh;
    ofPlanePrimitive plane;
    ofImage img1;
    ofImage img2;
    
    ofVec3f pos;
    float time;
    
};
