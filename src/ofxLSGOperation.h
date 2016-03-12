#pragma once
#include "ofMain.h"
#include "ofxLSGUtils.h"

class ofxLSGOperation {
public:
    ofxLSGOperation(string str);
    float compute(pair<string, map<string,float>> module);
    string getKey(){return key_ ;};
private:
    string key_;
    string firstOperand_;
    string operator_;
    string secondOperand_;
    bool isASingleLetter = false;
    bool isASingleNumber= false;
    float resolveOperation(map<string,float> keysVals);
    float value_;

    void determinateOperationType(string str);
};
