#include "ofxLSGSanitizer.h"

//it just displays an error message if constant are lowercases
void ofxLSGSanitizer::validateConstants(map<string,float> _constants){
    for(auto cons : _constants){
        if(itContainsLowercases(cons.first)){
            string msg = "constant "+ cons.first +" is invalid";
            msg += "only uppercase constant are allowed";
            ofLogError(ofToString(msg));
        }
    }
}

bool ofxLSGSanitizer::isRuleValid(string rule){
    return hasMinimumParts(rule) && containsSeparator(rule);
}

bool ofxLSGSanitizer::itContainsLowercases(string str){
    if(str.length() > 0 && ofxLSGUtils::isStringInRegex(str, "[a-z]")){
        return true;
    }
    return false;
}

bool ofxLSGSanitizer::hasMinimumParts(string rule){
    auto parts = ofSplitString(rule, "->");
    if((parts.size() < 2) && (parts.size() > 3)){
        string msg ="All the rules need to be formatted as follow: 'axiom -> rule' or 'probability -> axiom -> rule'";
        ofLogError(ofToString(msg));
        return false;
    }else{
        return true;
    }
}

bool ofxLSGSanitizer::containsSeparator(string rule){
    if(rule.find("->") == std::string::npos){
        string msg = "the string " + rule + "does not contain the symbol '->'";
        ofLogError(ofToString(msg));
        return false;
    }else{
        return true;
    }
}

bool ofxLSGSanitizer::isProbabilityValid(vector<ofxLSGRuleStochastic> ruleList){
    float tot = 0.0;
    for (auto r : ruleList){
        tot += r.probability;
    }
    if (tot < 0.95 || tot > 1.0) {
        string msg = "The sum of the probability values has to be between 0.95 and 1.0";
        ofLogError(ofToString(msg));
        return false;
    }else{
        return true;
    }
}

bool ofxLSGSanitizer::roundBracketsAreClosed(string str){
    int opened = ofxLSGUtils::countSubstring(str, "(");
    int closed = ofxLSGUtils::countSubstring(str, ")");
    return opened == closed;
}

string ofxLSGSanitizer::removeSpacesAndNewlines(string str){
    //whitespace
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    if(str.length() == 0){
        return str;
    }else{
        str = str.substr(first, (last-first+1));
        //newlines
        str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
        return str;
    }
}
