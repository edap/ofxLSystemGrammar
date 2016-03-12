#pragma once
#include "ofMain.h"
#include "ofxLSGUtils.h"

class ofxLSGCondition {
public:
    ofxLSGCondition(string str);
    string getLetter() const{ return letter; };
    string getComparisonOperator() const{ return comparisonOperator; };
    float getValue() const{ return value; };
    bool isTrue(map<string, float> parameters);
private:
    string letter;
    string comparisonOperator;
    float value;
};
