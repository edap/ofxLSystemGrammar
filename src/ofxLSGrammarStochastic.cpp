#include "StochasticGrammar.h"

string StochasticGrammar::generateSentence(vector<string> ruleListString, int _numberOfSteps, string _axiom){
    string finalSentence = _axiom;
    vector<RuleStochastic> ruleList = getRules(ruleListString);
    if(Sanitizer::isProbabilityValid(ruleList)){
        auto rulesWithProbability = buildRuleRange(ruleList);
        for(unsigned int i = 0; i< _numberOfSteps; i++){
            finalSentence = rewriteSentenceStochastic(finalSentence, rulesWithProbability);
        }
    }
    return finalSentence;
}

vector<RuleStochastic> StochasticGrammar::getRules(vector<string> ruleList){
    vector<RuleStochastic> rulesContainer;
    for(auto rule:ruleList){
        auto parts = ofSplitString(rule, "->");
        if(parts.size()==3){
            auto probability = Sanitizer::removeSpacesAndNewlines(parts.at(0));
            auto axiom = Sanitizer::removeSpacesAndNewlines(parts.at(1))[0];
            auto rule = Sanitizer::removeSpacesAndNewlines(parts.at(2));
            rulesContainer.push_back(RuleStochastic(axiom, rule, stof(probability)));
        }else{
            ofLogError("Stochastic Grammar detected, but rule not in the correct format");
        }
    }
    return rulesContainer;
}

string StochasticGrammar::rewriteSentenceStochastic(string _currentSentence, const map<float,RuleStochastic> rulesMap) {
    string nextSentence = "";
    bool firstReplacementDone = false;
    float randomIndex = ofRandom(0.99);
    auto randomRule = rulesMap.lower_bound(randomIndex);
    for(int i=0; i<_currentSentence.length(); i++){
        char cur = _currentSentence[i];
        string replacement = ofToString(cur);
        if(randomRule->second.axiom == cur){
            replacement = randomRule->second.rule;
        }
        nextSentence += replacement;
    }
    return nextSentence;
}

const map<float, RuleStochastic> StochasticGrammar::buildRuleRange(vector<RuleStochastic> ruleList){
    map<float, RuleStochastic> rulesWithProbability;
    float maxBound = 0.0;
    for (auto r : ruleList){
        maxBound += r.probability;
        rulesWithProbability.insert(make_pair(maxBound,r));
    }
    return rulesWithProbability;
}
