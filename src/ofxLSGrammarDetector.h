#pragma once
#include "ofMain.h"
#include "Utils.h"

class GrammarDetector{
public:
    static const bool isStochastic(vector<string> ruleList);
    static const bool isStandard(vector<string> ruleList);
    static const bool isParametric(vector<string> ruleList);
};
