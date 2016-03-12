#pragma once
#include "ofMain.h"
#include "ofxLSGRuleStochastic.h"
#include "ofxLSGUtils.h"

class ofxLSGSanitizer{
public:
    static bool   isRuleValid(string rule);
    static bool   isProbabilityValid(vector<ofxLSGRuleStochastic> ruleList);
    static string removeSpacesAndNewlines(string str);
    static bool   roundBracketsAreClosed(string str);
private:
    //TODO add more validations for the rules
    static bool hasMinimumParts(string rule);
    static bool containsSeparator(string rule);
};
