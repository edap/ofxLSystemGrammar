#pragma once
#include "ofMain.h"
#include "ofxLSGRuleParametric.h"
#include "ofxLSGUtils.h"
#include "ofxLSGSanitizer.h"

typedef pair<string,vector<float>> Module; // like A[1.0,2.0]
typedef pair<string, map<string, float>> ModuleMapped; // like A{x:1.0, y: 2.0}

class ofxLSGrammarParametric {
public:
    static string generateSentence(vector<string> ruleList, int numberOfSteps, string sentence);
private:
    static string rewriteSentence(string currentSentence, vector<ofxLSGRuleParametric>);
    static const vector<ofxLSGRuleParametric> getRules(vector<string> ruleList);
    static const map<string,vector<string>> getVarNamesOutOfRules(vector<ofxLSGRuleParametric> rulesContainer);
    static const vector<string> getPredecessorAndCondition(string str);
    static vector<Module> getModules(string axiom);
    static vector<ModuleMapped> initializeMap(vector<Module> modules, vector<ofxLSGRuleParametric> ruleContainer);
    static bool conditionsForReproductionAreMet(ofxLSGRuleParametric rule, ModuleMapped module);
    static bool conditionsAreTrue(vector<ofxLSGCondition> conditions, ModuleMapped module);
    static bool predecessorMatchModules(pair<string,vector<string>>, Module module);
    static const bool moduleNotMentionedInPredecessors(map<string,vector<string>> predecessors, Module module);
    static const bool moduleNotMentionedInPredecessors(vector<ofxLSGRuleParametric> ruleContainer, ModuleMapped module);
    static bool parametersAndLettersMatch(ofxLSGRuleParametric rule, ModuleMapped module);

};
