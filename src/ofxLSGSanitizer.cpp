#include "Sanitizer.h"

bool Sanitizer::isRuleValid(string rule){
    return hasMinimumParts(rule) && containsSeparator(rule);
}

bool Sanitizer::hasMinimumParts(string rule){
    auto parts = ofSplitString(rule, "->");
    if((parts.size() < 2) && (parts.size() > 3)){
        string msg ="All the rules need to be formatted as follow: 'axiom -> rule' or 'probability -> axiom -> rule'";
        ofLogError(ofToString(msg));
        return false;
    }else{
        return true;
    }
}

bool Sanitizer::containsSeparator(string rule){
    if(rule.find("->") == std::string::npos){
        string msg = "the string " + rule + "does not contain the symbol '->'";
        ofLogError(ofToString(msg));
        return false;
    }else{
        return true;
    }
}

bool Sanitizer::isProbabilityValid(vector<RuleStochastic> ruleList){
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

bool Sanitizer::roundBracketsAreClosed(string str){
    int opened = Utils::countSubstring(str, "(");
    int closed = Utils::countSubstring(str, ")");
    return opened == closed;
}

string Sanitizer::removeSpacesAndNewlines(string str){
    //whitespace
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    str = str.substr(first, (last-first+1));
    //newlines
    str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
    return str;
}
