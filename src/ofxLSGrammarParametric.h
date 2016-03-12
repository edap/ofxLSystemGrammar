#pragma once
#include "ofMain.h"
#include "RuleParametric.h"
#include "Utils.h"
#include "Sanitizer.h"

class ParametricGrammar {
public:
    static string generateSentence(vector<string> ruleList, int numberOfSteps, string sentence);
private:
    static string rewriteSentence(string currentSentence, vector<RuleParametric>);
    static const vector<RuleParametric> getRules(vector<string> ruleList);
    static const map<string,vector<string>> getVarNamesOutOfRules(vector<RuleParametric> rulesContainer);
    static const vector<string> getPredecessorAndCondition(string str);
    static vector<pair<string,vector<float>>> getModules(string axiom);
    static vector<pair <string, map<string, float>>> initializeMap(vector<pair<string,vector<float>>> modules, vector<RuleParametric> ruleContainer);
    static bool conditionsForReproductionAreMet(RuleParametric rule, pair<string, map<string,float>> module);
    static bool conditionsAreTrue(vector<Condition> conditions, pair<string, map<string,float>> module);
    static bool predecessorMatchModules(pair<string,vector<string>>, pair<string,vector<float>> module);
    static const bool moduleNotMentionedInPredecessors(map<string,vector<string>> predecessors, pair<string,vector<float>> module);
    static const bool moduleNotMentionedInPredecessors(vector<RuleParametric> ruleContainer, pair <string, map<string, float>> module);
    static bool parametersAndLettersMatch(RuleParametric rule, pair<string, map<string,float>> module);
};