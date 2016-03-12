#pragma once
#include "ofMain.h"
#include "RuleStochastic.h"
#include "Utils.h"

class Sanitizer{
public:
    static bool   isRuleValid(string rule);
    static bool   isProbabilityValid(vector<RuleStochastic> ruleList);
    static string removeSpacesAndNewlines(string str);
    static bool   roundBracketsAreClosed(string str);
private:
    //TODO add more validations for the rules
    static bool hasMinimumParts(string rule);
    static bool containsSeparator(string rule);
};
