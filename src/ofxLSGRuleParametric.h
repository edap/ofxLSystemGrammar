#pragma once
#include "ofMain.h"
#include "ofxLSGUtils.h"
#include "ofxLSGCondition.h"
#include "ofxLSGOperation.h"

typedef pair<string,vector<ofxLSGOperation>> Successor;

class ofxLSGRuleParametric{
public:
    ofxLSGRuleParametric(
                         string _predecessor,
                         string _conditions,
                         string _successor,
                         map<string, float> _constants);
    string getPredecessor() const;
    vector<ofxLSGCondition> getConditions() const;
    vector<Successor> getSuccessor() const;
    vector<string> getPredecessorParameters() const;
private:
    string predecessor;
    vector<string> predecessorParameters;
    vector<string> predecessorLetters;
    vector<ofxLSGCondition> conditions;
    vector<string> successorModules;
    vector<Successor> successor;

    vector<string> getPredecessorLetters() const; //not used
    vector<ofxLSGCondition> setConditions(string condition) const;
    vector<string> getSuccessorModules(string successor) const;
    vector<ofxLSGOperation> getOperationsInModule(string module) const;
    vector<Successor> setSuccessor(string successor,map<string,float> _constants) const;
};
