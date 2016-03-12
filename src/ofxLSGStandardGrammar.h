#pragma once
#include "ofMain.h"
#include "RuleStandard.h"
#include "Sanitizer.h"

class StandardGrammar {
public:
    static string         generateSentence(vector<string> ruleListString, int numberOfSteps, string axiom);
private:
    static vector<RuleStandard> getRules(vector<string> ruleList);
    static string               rewriteSentence(string sentence, vector<RuleStandard>);
};
