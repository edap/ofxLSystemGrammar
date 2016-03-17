#pragma once
#include "ofMain.h"
#include "ofxLSGRuleStochastic.h"
#include "ofxLSGSanitizer.h"

class ofxLSGrammarStochastic {
public:
    static vector<string> generateSentence(vector<string> ruleListString, int numberOfSteps, string axiom);
private:
    static vector<ofxLSGRuleStochastic> getRules(vector<string> ruleList);
    static string                       rewriteSentenceStochastic(string sentence, map<float,ofxLSGRuleStochastic>);
    static const map<float,ofxLSGRuleStochastic> buildRuleRange(vector<ofxLSGRuleStochastic> ruleList);
};
