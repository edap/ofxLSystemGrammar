#pragma once

#include "ofMain.h"
#include "ofxLSystemGrammar.h"

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
    void drawResult(vector<string>);
    void gotMessage(ofMessage msg);

    ofTrueTypeFont	verdana;

    vector<string> edgeRewriting{"F->F[+F]F[-F][F]"};
    vector<string> nodeRewriting{"X->F[+X][-X]FX", "F->FF"};
    vector<string> stochastic {
      "0.33 -> F -> F[+F]F[−F]F",
      "0.33 -> F -> F[+F]F",
      "0.34 -> F -> F[−F]F",
    };
    vector<string> parametric {
        "A(x,y): y<=3 -> A(x*2,x+y)",
        "A(x,y): y>3 -> B(x)A(x/y,0)",
        "B(x) : x>=1 -> B(x-1)",
        "A(x,y): y<=3 -> A(x*2,x+y)"
    };
    vector<string> parametricWithConstant { "A(s) -> F (s)[+A(s/R)][−A(s/R)]"};

    vector<string> resultEdgeRewriting, resultNodeRewriting, resultStochastic, resultParametric, resultParametricWithConstant;

    vector<vector<string>> allTheResult;

};
