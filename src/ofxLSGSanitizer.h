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
    static void   validateConstants(map<string,float> _constants);
private:
    //TODO add more validations for the rules
    static bool itContainsLowercases(string str);
    static bool hasMinimumParts(string rule);
    static bool containsSeparator(string rule);
};
