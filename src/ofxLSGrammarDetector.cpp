#include "GrammarDetector.h"

const bool GrammarDetector::isStochastic(vector<string> ruleList){
    // An expected stochastic rule looks like this:
    // 0.50 -> B -> F[-B]+B;
    if(ruleList.size() == 1){
        return false;
    }
    auto parts = ofSplitString(ruleList[0], "->");
    bool two_rockets = Utils::countSubstring(ruleList[0], "->");
    if(parts.size() ==3 && two_rockets){
        return true;
    }
    return false;
}

const bool GrammarDetector::isStandard(vector<string> ruleList){
    // An expected standard rule looks like this:
    // B -> F[-B]+B
    auto parts = ofSplitString(ruleList[0], "->");
    bool no_column = Utils::countSubstring(ruleList[0], ":") == 0;
    bool no_round_brackets = Utils::countSubstring(ruleList[0], "(") == 0;
    if(parts.size() == 2 && no_column && no_round_brackets){
        return true;
    }
    return false;
}

const bool GrammarDetector::isParametric(vector<string> ruleList){
    // An expected paramteric rule looks like this:
    // A(x,y): y>3 -> B(x)A(x/y,0);
    auto parts = ofSplitString(ruleList[0], "->");
    bool two_parts = parts.size() == 2;
    //It is parametric if it contains an integer enclosed in ()
    bool is_there_a_one_column = Utils::countSubstring(ruleList[0], ":") == 1;
    int n_round_brackets = Utils::countSubstring(ruleList[0], "(");
    bool round_brackets_present = n_round_brackets > 0;
    if(two_parts && is_there_a_one_column && round_brackets_present){
        return true;
    }
    return false;
}
