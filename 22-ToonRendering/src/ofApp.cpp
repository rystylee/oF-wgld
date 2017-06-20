#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    // initial setting
    ofSetFrameRate(60);
    ofSetBackgroundColor(0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_CULL_FACE);
    
    // shader setings
    shader.load("shaders/shader");
    
    //    // ----------------------------- debug
    //    // projection
    //    std::cout << "Fov : " << easyCam.getFov() << endl;
    //    std::cout << "AspectRatio : " << easyCam.getAspectRatio() << endl;
    //    std::cout << "NearClip : " << easyCam.getNearClip() << endl;
    //    std::cout << "FarClip : " << easyCam.getFarClip() << endl;
    //    // view
    //    std::cout << "Position: " << easyCam.getPosition() << endl;
    //    std::cout << "LookAt : " << easyCam.getLookAtDir() << endl;
    //    std::cout << "Up : " << easyCam.getUpDir() << endl;
    
    // camera setting
    easyCam.setNearClip(0);
    easyCam.setFarClip(1500);
    
    // load image
    img.load("toon.png");
    
    pos = ofVec3f(0.0, 0.0, 0.0);
    edge = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
    
    // debug
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    
    time = ofGetElapsedTimef();
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
    glClearDepth(1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    easyCam.begin();
    
    img.getTexture().bind();
    
    shader.begin();
    
    for(int i=0; i<MODEL_NUM; i++){
        
        // model Matrix
        ofMatrix4x4 modelMatrix;
        if(i == 0) modelMatrix.translate(-100, 0, 0);
        if(i == 1) modelMatrix.translate(0, 0, 0);
        if(i == 2) modelMatrix.translate(100, 0, 0);
        if(i == 3) modelMatrix.translate(0, -100, 0);
        if(i == 4) modelMatrix.translate(0, 100, 0);
        if(i == 5) modelMatrix.translate(0, 0, -100);
        if(i == 6) modelMatrix.translate(0, 0, 100);
        modelMatrix.rotate(time*10, 1.0, 0.5, 0.0);
        //pos * modelMatrix;
        sphere.setPosition(pos);
        sphere.setRadius(50);
        sphere.mapTexCoordsFromTexture(img.getTexture());
        
        // view Matrix
        ofMatrix4x4 viewMatrix;
        viewMatrix = ofGetCurrentViewMatrix();
        
        // projection Matrix
        ofMatrix4x4 projectionMatrix;
        projectionMatrix = easyCam.getProjectionMatrix();
        
        // mvp Matrix
        ofMatrix4x4 mvpMatrix;
        mvpMatrix = modelMatrix * viewMatrix * projectionMatrix;
        
        // inv Matrix
        ofMatrix4x4 invMatrix;
        invMatrix = modelMatrix.getInverse();
        
        // light position
        ofVec3f lightDirection = ofVec3f(-0.5, 0.5, 0.5);
        
        // edge color
        ofVec4f edgeColor = ofVec4f(0.0, 0.0, 0.0, 0.0);
        
        // edge checker
        edge = 0;
        
        shader.setUniformMatrix4f("model", modelMatrix);
        shader.setUniformMatrix4f("view", viewMatrix);
        shader.setUniformMatrix4f("projection", projectionMatrix);
        shader.setUniformMatrix4f("mvp", mvpMatrix);
        shader.setUniform1i("edge", edge);
        shader.setUniformMatrix4f("inv", invMatrix);
        shader.setUniform3f("lightDirection", lightDirection);
        shader.setUniformTexture("tex0", img.getTexture(), 0);
        shader.setUniform4f("edgeColor", edgeColor);
        
        glCullFace(GL_FRONT);
        
        vboMesh = sphere.getMesh();
        for(int j=0; j<vboMesh.getVertices().size(); j++){
            vboMesh.addColor(ofFloatColor(1.0, 1.0, 1.0, 1.0));
        }
        vboMesh.setMode(OF_PRIMITIVE_TRIANGLES);
        vboMesh.draw();
        
        // ----------------------------- edge
        
        // edge checker
        edge = 1;
        
        // edge color
        edgeColor = ofVec4f(0.0, 0.0, 0.0, 1.0);
        
        shader.setUniform1i("edge", edge);
        shader.setUniform4f("edgeColor", edgeColor);
        
        glCullFace(GL_BACK);
        
        vboMesh.draw();
    }
    
    shader.end();
    
    img.getTexture().bind();
    
    // draw axis (x, y, z)
    ofSetLineWidth(0.1);
    ofSetColor(255, 0, 0);
    ofDrawLine(-500, 0, 0, 500, 0, 0);
    ofSetColor(0, 255, 0);
    ofDrawLine(0, -400, 0, 0, 400, 0);
    ofSetColor(0, 0, 255);
    ofDrawLine(0, 0, -400, 0, 0, 400);
    
    easyCam.end();
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
