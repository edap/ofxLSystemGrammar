#pragma once
#include "ofMain.h"
#include "ofxLSystemGrammar.h"

typedef map<string, float> Constants;

class RuleTest {
public:
    RuleTest(string _title, string _axiom, string _ruleList, int _depth, vector<string> _expectedResult, Constants _constants = Constants()){
        title = _title;
        axiom = _axiom;
        rules = _ruleList;
        depth = _depth;
        expectedResult = _expectedResult;
    };
    string getTitle() const { return title; };
    string getAxiom() const { return axiom; };
    string getRules() const { return rules; };
    Constants getConstants() const { return constants; };
    bool isPassed() const { return passed; };
    int getDepth() const { return depth; };
    vector<string> getExpectedResult() const { return expectedResult; };
    vector<string> getResult() const { return result; };
    void setResult(vector<string> _result){ result = _result;};
    void executeTest();

private:
    string axiom;
    string rules;
    string title;
    Constants constants;
    int depth;
    vector<string> expectedResult;
    vector<string> result;
    bool passed;

    bool expectToBeEqual(string first, string second){ first == second;};
    bool expectToBeEqual(vector<string> first, vector<string> second);
};
