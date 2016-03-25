#pragma once
#include "ofMain.h"
#include "ofxLSGRuleParametric.h"
#include "ofxLSGUtils.h"
#include "ofxLSGSanitizer.h"
#include "ofxLSGModuleReaderParametric.h"

typedef pair<string,vector<float>> Module; // like A[1.0,2.0]
typedef pair<string, map<string, float>> ModuleMapped; // like A{x:1.0, y: 2.0}

class ofxLSGrammarParametric {
public:
    static vector<string> generateSentence(vector<string> ruleList, int numberOfSteps, string sentence, map<string,float> _constants);
private:
    static string rewriteSentence(string currentSentence, vector<ofxLSGRuleParametric>);
    static string injectResults(ofxLSGRuleParametric rule, ModuleMapped module);
    static const vector<ofxLSGRuleParametric> getRules(vector<string> ruleList,map<string,float> _constants);
    static const vector<string> getPredecessorAndCondition(string str);
    static vector<Module> getModules(string axiom);

    static bool conditionsForReproductionAreMet(ofxLSGRuleParametric rule, ModuleMapped module);
    static bool conditionsAreTrue(vector<ofxLSGCondition> conditions, ModuleMapped module);


    static const bool moduleNotMentionedInPredecessors(vector<ofxLSGRuleParametric> ruleContainer, ModuleMapped module);
    static bool parametersAndLettersMatch(ofxLSGRuleParametric rule, ModuleMapped module);
};
