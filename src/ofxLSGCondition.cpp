#include "ofxLSGCondition.h"

// This constructor expect a string like "x>4"
 ofxLSGCondition::ofxLSGCondition(string str){
    letter = ofxLSGUtils::grepStringInRegex(str, "[a-z]");
    comparisonOperator = ofxLSGUtils::grepStringInRegex(str, "[<>=]+");
    value = ofToFloat(ofxLSGUtils::grepStringInRegex(str, "[0-9]+"));
}

bool ofxLSGCondition::isTrue(map<string, float> parameters){
    if(isAnEmptyCondition()){
        return true;
    }
    for(auto pair:parameters){
        // if we pass {{x: 3},{y:4}}, and the condition is y > 3
        // we just ignore the first pair {x:3}
        if(letter == pair.first){
            //cout << "checking" + pair.first +ofToString(pair.second) << endl;
            //cout << "for condition " + pair.first +" "+comparisonOperator+" "+ ofToString(value)<< endl;
            if(comparisonOperator == ">"){
                return pair.second > value;
            }else if(comparisonOperator == ">="){
                return pair.second >= value;
            }else if(comparisonOperator == "=="){
                return pair.second == value;
            }else if(comparisonOperator == "<"){
                return pair.second < value;
            }else if(comparisonOperator == "<="){
                return pair.second <= value;
            }else{
                return false;
            }
        }
    }
    return false;
}


bool ofxLSGCondition::isAnEmptyCondition() const{
    return (letter.size() == 0 ? true : false);
}
