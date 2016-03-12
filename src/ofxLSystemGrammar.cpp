#include "ofxLSystemGrammar.h"

const string ofxLSystemGrammar::buildSentence(string rules, const int _n_steps, string _axiom){
    vector<string> stringRules = putStringInContainer(rules);
    string finalSentence = _axiom;
    if(ofxLSGrammarDetector::isStochastic(stringRules)){
        finalSentence = ofxLSGrammarStochastic::generateSentence(stringRules, _n_steps, finalSentence);
    }else if(ofxLSGrammarDetector::isStandard(stringRules)) {
        finalSentence = ofxLSGrammarStandard::generateSentence(stringRules, _n_steps, finalSentence);
    }else if(ofxLSGrammarDetector::isParametric(stringRules)) {
        finalSentence = ofxLSGrammarParametric::generateSentence(stringRules, _n_steps, finalSentence);
    }else{
        //do not brake
        ofLogError("It is not possible to detect the grammar type");
        finalSentence = "FF";
    }
    return finalSentence;
}

vector<string> ofxLSystemGrammar::putStringInContainer(string rules){
    vector<string> stringRules;
    if(rules.find(";") != std::string::npos){
        //multiple rules
        auto rule_container = ofSplitString(rules, ";");
        for(auto r:rule_container){
            string cleaned = ofxLSGSanitizer::removeSpacesAndNewlines(r);
            if (cleaned.length()>0 && ofxLSGSanitizer::isRuleValid(cleaned)){
                stringRules.push_back(cleaned);
            }
        }
    }else{
        //single rule
        if(rules.length()>0 && ofxLSGSanitizer::isRuleValid(rules)){
            stringRules.push_back(rules);
        }
    }
    return stringRules;
}
