#pragma once
#include "ofMain.h"

class ofxLSGRuleStandard{
public:
    ofxLSGRuleStandard( char _a, string _b){
        axiom = _a;
        rule = _b;
    };
    
    char axiom;
    string rule;
};
