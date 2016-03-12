#pragma once
#include "ofMain.h"
#include "ofxLSGRuleStandard.h"
#include "ofxLSGSanitizer.h"

class ofxLSGrammarStandard {
public:
    static string generateSentence(vector<string> ruleListString, int numberOfSteps, string axiom);
private:
    static vector<ofxLSGRuleStandard> getRules(vector<string> ruleList);
    static string                     rewriteSentence(string sentence, vector<ofxLSGRuleStandard>);
};
