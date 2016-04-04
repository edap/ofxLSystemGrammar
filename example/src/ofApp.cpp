#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofTrueTypeFont::setGlobalDpi(72);
    ofSetBackgroundColor(0, 0, 0);
    verdana.load("verdana.ttf", 14, true, true);
    verdana.setLineHeight(18.0f);
    verdana.setLetterSpacing(1.037);

   resultEdgeRewriting = ofxLSystemGrammar::buildSentences(edgeRewriting, 4, "F");
   resultNodeRewriting = ofxLSystemGrammar::buildSentences(nodeRewriting, 6, "X");
   resultStochastic = ofxLSystemGrammar::buildSentences(stochastic, 6, "F");
   resultParametric = ofxLSystemGrammar::buildSentences(parametric, 3, "B(2),A(4,4)");

   map<string, float> constants;
   constants.insert(make_pair("R", 1.456));
   resultParametricWithConstant = ofxLSystemGrammar::buildSentences(parametricWithConstant, 6, "A(1)", constants);

   allTheResult.push_back(resultEdgeRewriting);
   allTheResult.push_back(resultNodeRewriting);
   allTheResult.push_back(resultStochastic);
   allTheResult.push_back(resultParametric);
   allTheResult.push_back(resultParametricWithConstant);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    int x = 20;
    int y = 20;
    for(auto result : allTheResult){
        string text;
        for(auto sentence : result){
            text += sentence + "\n";
        }

        ofSetColor(0,255,0);
        ofRectangle bounds = verdana.getStringBoundingBox(text, 100, y);
        verdana.drawString(text , x, y );
        y += bounds.height+15;
    }
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
