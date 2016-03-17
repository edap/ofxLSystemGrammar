#include "ofxLSGrammarStochastic.h"

vector<string> ofxLSGrammarStochastic::generateSentence(vector<string> ruleListString, int _numberOfSteps, string _axiom){
    vector<string> finalSentence;
    finalSentence.push_back(_axiom);
    vector<ofxLSGRuleStochastic> ruleList = getRules(ruleListString);
    if(ofxLSGSanitizer::isProbabilityValid(ruleList)){
        auto rulesWithProbability = buildRuleRange(ruleList);
        for(unsigned int i = 0; i< _numberOfSteps; i++){
            auto currentSentence = finalSentence.back();
            auto nextSentence = rewriteSentenceStochastic(currentSentence, rulesWithProbability);
            finalSentence.push_back(nextSentence);
        }
    }
    return finalSentence;
}

vector<ofxLSGRuleStochastic> ofxLSGrammarStochastic::getRules(vector<string> ruleList){
    vector<ofxLSGRuleStochastic> rulesContainer;
    for(auto rule:ruleList){
        auto parts = ofSplitString(rule, "->");
        if(parts.size()==3){
            auto probability = ofxLSGSanitizer::removeSpacesAndNewlines(parts.at(0));
            auto axiom = ofxLSGSanitizer::removeSpacesAndNewlines(parts.at(1))[0];
            auto rule = ofxLSGSanitizer::removeSpacesAndNewlines(parts.at(2));
            rulesContainer.push_back(ofxLSGRuleStochastic(axiom, rule, stof(probability)));
        }else{
            ofLogError("Stochastic Grammar detected, but rule not in the correct format");
        }
    }
    return rulesContainer;
}

string ofxLSGrammarStochastic::rewriteSentenceStochastic(string _currentSentence, const map<float,ofxLSGRuleStochastic> rulesMap) {
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

const map<float, ofxLSGRuleStochastic> ofxLSGrammarStochastic::buildRuleRange(vector<ofxLSGRuleStochastic> ruleList){
    map<float, ofxLSGRuleStochastic> rulesWithProbability;
    float maxBound = 0.0;
    for (auto r : ruleList){
        maxBound += r.probability;
        rulesWithProbability.insert(make_pair(maxBound,r));
    }
    return rulesWithProbability;
}
