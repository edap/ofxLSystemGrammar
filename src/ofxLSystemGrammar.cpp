#include "ofxLSystemGrammar.h"

const vector<string> ofxLSystemGrammar::buildSentences(vector<string> rules, const int _n_steps, string _axiom, map<string,float> _constants){
    vector<string> stringRules = sanitizeRules(rules);
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

const vector<string> ofxLSystemGrammar::sanitizeRules(vector<string> rules){
    vector<string> sanitizedRules;
    for(auto r : rules){
        string cleaned = ofxLSGSanitizer::removeSpacesAndNewlines(r);
        if (cleaned.length()>0 && ofxLSGSanitizer::isRuleValid(cleaned)){
            sanitizedRules.push_back(cleaned);
        }
    }
    return sanitizedRules;
}
