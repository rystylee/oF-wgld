#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    // initial setting
    ofSetFrameRate(60);
    ofSetBackgroundColor(0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
    ofEnableAlphaBlending();
    
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
    ofDisableArbTex();
    img.load("texture.png");
    ofEnableArbTex();
    //glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    //glTexEnvi(GL_POINT_SPRITE, GL_COORD_REPLACE, GL_TRUE);
    
    vertexAlpha = 0.7;
    useTexture = 1;
    
    pos = ofVec3f(0.0, 0.0, 0.0);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    // debug
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    
    vertexAlpha = abs(sin(ofGetElapsedTimef() * 0.5));
    time = ofGetElapsedTimef();
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearDepth(1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    easyCam.begin();
    
    img.getTexture().bind();
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    // how to calculate blending (default is GL_FUNC_ADD)
    glBlendEquation(GL_FUNC_ADD);
    //glBlendEquation(GL_FUNC_SUBTRACT);
    //glBlendEquation(GL_FUNC_REVERSE_SUBTRACT);
    
    // extention method
    //glBlendEquationSeparate();
    
    // blendfactor settings
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // add blend
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    
    // extention method
    //glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);
    
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
        
        // view Matrix
        ofMatrix4x4 viewMatrix;
        viewMatrix = ofGetCurrentViewMatrix();
        
        // projection Matrix
        ofMatrix4x4 projectionMatrix;
        projectionMatrix = easyCam.getProjectionMatrix();
        
        // mvp Matrix
        ofMatrix4x4 mvpMatrix;
        mvpMatrix = modelMatrix * viewMatrix * projectionMatrix;
        
        shader.setUniformMatrix4f("model", modelMatrix);
        shader.setUniformMatrix4f("view", viewMatrix);
        shader.setUniformMatrix4f("projection", projectionMatrix);
        shader.setUniformMatrix4f("mvp", mvpMatrix);
        shader.setUniform1f("vertexAlpha", vertexAlpha);
        shader.setUniformTexture("tex0", img.getTexture(), 0);
        shader.setUniform1i("useTexture", useTexture);
        
        vboMesh = sphere.getMesh();
        for(int j=0; j<vboMesh.getVertices().size(); j++){
            vboMesh.addColor(ofFloatColor(1.0, 1.0, 1.0, 1.0));
        }
        vboMesh.setMode(OF_PRIMITIVE_POINTS);
        // anti-aliasing
        glEnable(GL_POINT_SMOOTH);
        //glEnable(GL_POINT_SPRITE);
        ofEnablePointSprites();
        vboMesh.draw();
        ofDisablePointSprites();
        //glDisable(GL_POINT_SPRITE);
    }
    
    shader.end();
    
    img.getTexture().unbind();
    
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
    
    if(key == ' '){
        useTexture = (useTexture + 1) % 2;
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
