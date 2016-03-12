#pragma once
#include "ofMain.h"
#include "ofxLSGRuleParametric.h"
#include "ofxLSGUtils.h"
#include "ofxLSGSanitizer.h"

class ofxLSGrammarParametric {
public:
    static string generateSentence(vector<string> ruleList, int numberOfSteps, string sentence);
private:
    static string rewriteSentence(string currentSentence, vector<ofxLSGRuleParametric>);
    static const vector<ofxLSGRuleParametric> getRules(vector<string> ruleList);
    static const map<string,vector<string>> getVarNamesOutOfRules(vector<ofxLSGRuleParametric> rulesContainer);
    static const vector<string> getPredecessorAndCondition(string str);
    static vector<pair<string,vector<float>>> getModules(string axiom);
    static vector<pair <string, map<string, float>>> initializeMap(vector<pair<string,vector<float>>> modules, vector<ofxLSGRuleParametric> ruleContainer);
    static bool conditionsForReproductionAreMet(ofxLSGRuleParametric rule, pair<string, map<string,float>> module);
    static bool conditionsAreTrue(vector<ofxLSGCondition> conditions, pair<string, map<string,float>> module);
    static bool predecessorMatchModules(pair<string,vector<string>>, pair<string,vector<float>> module);
    static const bool moduleNotMentionedInPredecessors(map<string,vector<string>> predecessors, pair<string,vector<float>> module);
    static const bool moduleNotMentionedInPredecessors(vector<ofxLSGRuleParametric> ruleContainer, pair <string, map<string, float>> module);
    static bool parametersAndLettersMatch(ofxLSGRuleParametric rule, pair<string, map<string,float>> module);
};
