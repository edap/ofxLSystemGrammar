#include "ofxLSGOperation.h"
// This constructor expects a string like:
// 1)"x*2", three chars, that one in the middle is + or - or * or /, the other two around the operator
// can be a letter (capital or not) or a number (1 or 0.999)
// 2) A single letter, ex A or x
// 3) A number
ofxLSGOperation::ofxLSGOperation(string str){
    key_ = str;
    determinateOperationType(str);
}

float ofxLSGOperation::compute(pair<string, map<string, float> > module){
    if (isASingleLetter) {
        // if the successor said (x), substitute the x with the current value
        for(auto keyVal:module.second){
            if (keyVal.first == firstOperand_) {
                return keyVal.second;
            }
        }
    }else if(isASingleNumber){
        // if the successor said (5), simply return 5
        return ofToFloat(firstOperand_);
    }else if (operator_.length()>0){
        // if it is an operation (x*2) or (x+y), you know the value of x and y, solve it
        for(auto keyVal:module.second){
            if (keyVal.first == firstOperand_ || keyVal.first == secondOperand_ ) {
                return resolveOperation(module.second);
            }
        }
    }
    return 0.0;
}

float ofxLSGOperation::resolveOperation(map<string,float> keysVals){
    string first = firstOperand_;
    string second = secondOperand_;
    for(auto keyVal:keysVals){
        if(keyVal.first == firstOperand_ && ofxLSGUtils::isStringInRegex(firstOperand_, "[a-z]")){
            first = ofToString(keyVal.second);
        }

        if(keyVal.first == secondOperand_ && ofxLSGUtils::isStringInRegex(secondOperand_, "[a-z]")){
            second = ofToString(keyVal.second);
        }
    }

    if(operator_ == "*"){
        return ofToFloat(first) * ofToFloat(second);
    }else if(operator_ == "-"){
        return ofToFloat(first) - ofToFloat(second);
    }else if(operator_ == "/"){
        return ofToFloat(first) / ofToFloat(second);
    }else if(operator_ == "+"){
        return ofToFloat(first) + ofToFloat(second);
    }
    return 0.0;
}

// Depending on which of the 3 supported operation is recognized, it initializes the
// values for the operation
void ofxLSGOperation::determinateOperationType(string str){
    auto operands = ofxLSGUtils::matchesGroupsInRegex(str, "([a-zA-Z0-9\\.]+)(\\/|\\*|\\+|-)([a-zA-Z0-9\\.]+)");
    if (operands.size() == 4) {
        // operation like x*3, or S/1.444
        firstOperand_ = operands.at(1);
        operator_     = operands.at(2);
        secondOperand_= operands.at(3);
    }else if(str.length() == 1){
        if (ofxLSGUtils::grepStringInRegex(str, "[A-Za-z]").length() > 0){
            firstOperand_ = str;
            isASingleLetter = true;
        }else if(ofxLSGUtils::grepStringInRegex(str, "[0-9\\.]+").length() > 0){
            firstOperand_ = str;
            isASingleNumber = true;
        }else{
            ofLogError("Single operation "+ str +" not supported");
        }
    }else{
        ofLogError("This string operation "+ str +" is not supported");
    }
}
