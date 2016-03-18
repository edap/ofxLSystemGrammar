#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofTrueTypeFont::setGlobalDpi(72);
    ofSetBackgroundColor(0, 0, 0);

    verdana14.load("verdana.ttf", 14, true, true);
    verdana14.setLineHeight(18.0f);
    verdana14.setLetterSpacing(1.037);

    verdana30.load("verdana.ttf", 30, true, true);
    verdana30.setLineHeight(34.0f);
    verdana30.setLetterSpacing(1.035);

    //parametric test. Rules also in page 43 of "The Algorithmic Beauty of Plants"
    string parametricRules;
    parametricRules += "A(x,y): y<=3 -> A(x*2,x+y);";
    parametricRules += "A(x,y): y>3 -> B(x)A(x/y,0);";
    parametricRules += "B(x) :x<1 -> C;";
    parametricRules += "B(x) : x>=1 -> B(x-1);";
    vector<string> expectedParametricResult {
        "B(2)A(4,4)",
        "B(1)B(4)A(1,0)",
        "B(0)B(3)A(2,1)",
        "CB(2)A(4,3)"
    };
    auto parametricTest = RuleTest("Parametric Grammar test",
                                   "B(2)A(4,4)",
                                   parametricRules,
                                   3,
                                   expectedParametricResult
                                   );
    parametricTest.executeTest();
    tests.push_back(parametricTest);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    int y = 50;
    for(auto test : tests){
        string text;
        if(test.isPassed()){
            ofSetColor(0,255,0);
            text = test.getTitle() += ": OK";
        }else{
            ofSetColor(255,0,0);
            text = test.getTitle() += ": ERROR";
        }
        auto passed = test.isPassed() ? "OK" : "ERROR";
        verdana14.drawString(text , 100, y );
        y += 50;
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
