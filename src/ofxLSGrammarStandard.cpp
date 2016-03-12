#include "ofxLSGrammarStandard.h"

string ofxLSGrammarStandard::generateSentence(vector<string> ruleListString, int _numberOfSteps, string _axiom){
    string finalSentence = _axiom;
    auto ruleList = getRules(ruleListString);
    for(unsigned int i = 0; i< _numberOfSteps; i++){
        finalSentence = rewriteSentence(finalSentence, ruleList);
    }
    return finalSentence;
}

vector<ofxLSGRuleStandard> ofxLSGrammarStandard::getRules(vector<string> ruleList){
    vector<ofxLSGRuleStandard> rulesContainer;
    for(auto rule:ruleList){
        auto parts = ofSplitString(rule, "->");
        if(parts.size()==2){
            auto axiom = ofxLSGSanitizer::removeSpacesAndNewlines(parts.at(0))[0];
            auto rule = ofxLSGSanitizer::removeSpacesAndNewlines(parts.at(1));
            rulesContainer.push_back(ofxLSGRuleStandard(axiom, rule));
        }else{
            ofLogError("Standard Grammar detected, but rule not in the correct format");
        }
    }
    return rulesContainer;
}

string ofxLSGrammarStandard::rewriteSentence(string _currentSentence, vector<ofxLSGRuleStandard> ruleList) {
    string nextSentence = "";
    bool firstReplacementDone = false;
    for( int i=0; i<_currentSentence.length(); i++ ){
        char cur = _currentSentence[i];
        string replacement = ofToString(cur);
        for(auto r : ruleList){
            if( r.axiom == cur){
                replacement = r.rule;
                break;
            }
        }
        nextSentence += replacement;
    }
    return nextSentence;
}
