#pragma once
#include "ofMain.h"

class ofxLSGRuleStochastic{
public:
    ofxLSGRuleStochastic( char _a, string _b, float _probability = 0.0){
        axiom = _a;
        rule = _b;
        probability = _probability;
    };

    char axiom;
    string rule;
    float probability; // from 0 to 1.0
};
