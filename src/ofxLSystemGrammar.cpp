#include "ofxLSystemGrammar.h"

const vector<string> ofxLSystemGrammar::buildSentences(string rules, const int _n_steps, string _axiom, map<string,float> _constants){
    vector<string> stringRules = putStringInContainer(rules);
    vector<string> finalSentence;
    ofxLSGSanitizer::validateConstants(_constants);
    if(ofxLSGrammarDetector::isStochastic(stringRules)){
        finalSentence = ofxLSGrammarStochastic::generateSentence(stringRules, _n_steps, _axiom, _constants);
    }else if(ofxLSGrammarDetector::isStandard(stringRules)) {
        finalSentence = ofxLSGrammarStandard::generateSentence(stringRules, _n_steps, _axiom, _constants);
    }else if(ofxLSGrammarDetector::isParametric(stringRules)) {
        finalSentence = ofxLSGrammarParametric::generateSentence(stringRules, _n_steps, _axiom, _constants);
    }else{
        //do not brake
        ofLogError("It is not possible to detect the grammar type");
        finalSentence.push_back("FF");
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
