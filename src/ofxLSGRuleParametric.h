#pragma once
#include "ofMain.h"
#include "ofxLSGUtils.h"
#include "ofxLSGCondition.h"
#include "ofxLSGOperation.h"

class ofxLSGRuleParametric: public Rule{
public:
    ofxLSGRuleParametric( string _predecessor,  string _conditions, string _successor);
    string getPredecessor() const;
    vector<ofxLSGCondition> getConditions() const;
    vector<pair<string,vector<ofxLSGOperation>>> getSuccessor() const;
    vector<string> getPredecessorParameters() const;
private:
    string predecessor;
    vector<string> predecessorParameters;
    vector<string> predecessorLetters;
    vector<ofxLSGCondition> conditions;
    vector<string> successorModules;
    vector<pair<string,vector<ofxLSGOperation>>> successor;

    vector<string> getPredecessorLetters() const; //not used
    vector<ofxLSGCondition> setConditions(string condition) const;
    vector<string> getSuccessorModules(string successor) const;
    vector<ofxLSGOperation> getOperationsInModule(string module) const;
    vector<pair<string,vector<ofxLSGOperation>>> setSuccessor(string successor) const;
};
