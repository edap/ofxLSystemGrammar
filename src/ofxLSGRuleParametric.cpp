#include <ofxLSGRuleParametric.h>
ofxLSGRuleParametric::ofxLSGRuleParametric(
                                           string _predecessor,
                                           string _conditions,
                                           string _successor,
                                           map<string,float> _constants){
    predecessor = _predecessor;
    conditions = setConditions(_conditions);
    successor = setSuccessor(_successor, _constants);
    predecessorParameters = getPredecessorParameters();
    predecessorLetters = getPredecessorLetters();
};

vector<ofxLSGCondition> ofxLSGRuleParametric::getConditions() const{
    return conditions;
}

string ofxLSGRuleParametric::getPredecessor() const{
    return predecessor;
}

vector<pair<string,vector<ofxLSGOperation>>> ofxLSGRuleParametric::getSuccessor() const{
    return successor;
}

vector<string> ofxLSGRuleParametric::getPredecessorParameters() const{
    // it puts in a vector x,y from, for example "A(x,y)"
    return ofxLSGUtils::matchesInRegex(predecessor, "[a-z]");
}

vector<string> ofxLSGRuleParametric::getPredecessorLetters() const{
    // it puts in a vector A,B from, for example "A(x)> B(Y)"
    return ofxLSGUtils::matchesInRegex(predecessor, "[A-Z]");
}

vector<ofxLSGCondition> ofxLSGRuleParametric::setConditions(string _conditions) const{
    vector<ofxLSGCondition> conditions;
    auto parts = ofSplitString(_conditions, "&&");
    for(auto part:parts){
        conditions.push_back(ofxLSGCondition(part));
    }
    return conditions;
}

vector<pair<string,vector<ofxLSGOperation>>> ofxLSGRuleParametric::setSuccessor(
                                                            string _successor,
                                                            map<string,float> _constants
                                                                                ) const{
    auto successorWithConstants = replaceConstantsInModules(_successor, _constants);
    auto successorModules = ofxLSGUtils::getModulesFromString(successorWithConstants);
    // grep operations
    // use the grepped kye as value for the operation object
    // calculate substitution if necessary. otherwise return
    vector<pair<string,vector<ofxLSGOperation>>> successors;
    for(auto part:successorModules){
        if (part.length() == 0) continue;
        auto ops = getOperationsInModule(part);
        successors.push_back(make_pair(part, ops));
    }
    return successors;
}

string ofxLSGRuleParametric::replaceConstantsInModules(string successor, Constants _constants) const{
    string result;
    result = successor;
    for(auto _constant : _constants){
        auto key  = _constant.first;
        auto val = _constant.second;
        ofStringReplace(result, key, ofToString(val));
    }
    return result;

};

//This method take a module like A(x+1), recognize that x+1 is an operation, and returns
// a vector containing the operations, (in this case only one), for that module
vector<ofxLSGOperation> ofxLSGRuleParametric::getOperationsInModule(string module) const{
    vector<ofxLSGOperation> operations;
    auto textInsideRounBrackets = ofxLSGUtils::matchesInRegex(module, "\\([A-Za-z0-9,\\.\\+\\*\\/-]+\\)");
    for(auto stringOp:textInsideRounBrackets){
        //remove the first parenthesis
        stringOp = ofxLSGUtils::stripFirstAndLastChar(stringOp);
        if(ofxLSGUtils::countSubstring(stringOp, "(") > 0){
            ofLogError("Currently nested operation are not supported, it is not \
                       possible to process the string "+stringOp);
        }
        auto operationsString = ofSplitString(stringOp, ",");
        for(auto op:operationsString){
            operations.push_back(ofxLSGOperation(op));
        }
    }
    return operations;
}
