#pragma once
#include "ofMain.h"
#include "ofxLSGUtils.h"

class ofxLSGrammarDetector{
public:
    static const bool isStochastic(vector<string> ruleList);
    static const bool isStandard(vector<string> ruleList);
    static const bool isParametric(vector<string> ruleList);
};
