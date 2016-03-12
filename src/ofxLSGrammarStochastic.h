#pragma once
#include "ofMain.h"
#include "RuleStochastic.h"
#include "Sanitizer.h"

class StochasticGrammar {
public:
    static string         generateSentence(vector<string> ruleListString, int numberOfSteps, string axiom);
private:
    static vector<RuleStochastic> getRules(vector<string> ruleList);
    static string                rewriteSentenceStochastic(string sentence, map<float,RuleStochastic>);
    static const map<float,RuleStochastic> buildRuleRange(vector<RuleStochastic> ruleList);
};
