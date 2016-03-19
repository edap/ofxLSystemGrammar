#pragma once
#include "ofMain.h"
#include "ofxLSGRuleStandard.h"
#include "ofxLSGSanitizer.h"

class ofxLSGrammarStandard {
public:
    static vector<string> generateSentence(vector<string> ruleListString, int numberOfSteps, string axiom, map<string,float> _constants);
private:
    static vector<ofxLSGRuleStandard> getRules(vector<string> ruleList);
    static string                     rewriteSentence(string sentence, vector<ofxLSGRuleStandard>);
};
