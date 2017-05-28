#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    // initial setting
    ofSetFrameRate(60);
    ofSetBackgroundColor(0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    
    // shader setings
    fboShader.load("shaders/fboShader");
    blurShader.load("shaders/blurShader");
    
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
    sphereImage.load("texture0.png");
    
    // fbo
    fbo.allocate(ofGetWidth(), ofGetHeight());
    useBlur = 0;
    
    pos = ofVec3f(0.0, 0.0, 0.0);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    // debug
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    
    time = ofGetElapsedTimef();
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    fbo.begin();
    ofClear(0, 255);
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearDepth(1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    easyCam.begin();
    
    sphereImage.getTexture().bind();
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    fboShader.begin();
    
    // model Matrix
    ofMatrix4x4 modelMatrix;
    modelMatrix.rotate(time*10, 1.0, 0.5, 0.0);
    //pos * modelMatrix;
    sphere.set(128, 64);
    sphere.mapTexCoordsFromTexture(sphereImage.getTexture());
    sphere.setPosition(pos);
    
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
    
    // light direction
    ofVec3f lightDirection = ofVec3f(-0.5, 0.5, 0.5);
    
    fboShader.setUniformMatrix4f("model", modelMatrix);
    fboShader.setUniformMatrix4f("view", viewMatrix);
    fboShader.setUniformMatrix4f("projection", projectionMatrix);
    fboShader.setUniformMatrix4f("mvp", mvpMatrix);
    fboShader.setUniformMatrix4f("inv", invMatrix);
    fboShader.setUniform3f("lightDirection", lightDirection);
    fboShader.setUniformTexture("tex0", sphereImage.getTexture(), 0);
    
    vboMesh = sphere.getMesh();
    for(int j=0; j<vboMesh.getVertices().size(); j++){
        vboMesh.addColor(ofFloatColor(1.0, 1.0, 1.0, 1.0));
    }
    vboMesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    vboMesh.draw();
    
    fboShader.end();
    
    sphereImage.getTexture().unbind();
    
    // draw axis (x, y, z)
    ofSetLineWidth(0.1);
    ofSetColor(255, 0, 0);
    ofDrawLine(-500, 0, 0, 500, 0, 0);
    ofSetColor(0, 255, 0);
    ofDrawLine(0, -400, 0, 0, 400, 0);
    ofSetColor(0, 0, 255);
    ofDrawLine(0, 0, -400, 0, 0, 400);
    
    easyCam.end();
    
    fbo.end();
    
    // --------- blur filter
    
    fbo.getTexture().bind();
    
    blurShader.begin();
    blurShader.setUniformTexture("fbo", fbo.getTexture(), 0);
    blurShader.setUniform1i("useBlur", useBlur);
    fbo.draw(0, 0);
    blurShader.end();
    
    fbo.getTexture().unbind();
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if(key == ' '){
        useBlur = (useBlur + 1) % 2;
    }
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
