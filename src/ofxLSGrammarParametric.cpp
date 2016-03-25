#include "ofxLSGrammarParametric.h"

vector<string> ofxLSGrammarParametric::generateSentence(vector<string> ruleListString, int _numberOfSteps, string _axiom, map<string,float> _constants){
    vector<string> finalSentences;
    finalSentences.push_back(_axiom);

    auto ruleList = getRules(ruleListString, _constants);
    for(unsigned int i = 0; i< _numberOfSteps; i++){
        auto currentString = finalSentences.back();
        auto nextSentence = rewriteSentence(currentString, ruleList);
        finalSentences.push_back(nextSentence);
        cout << nextSentence << endl;
    }
    return finalSentences;
}

string ofxLSGrammarParametric::rewriteSentence(string axiom, vector<ofxLSGRuleParametric> rulesContainer){
    auto modules = getModules(axiom);
    auto currentIterationMap = ofxLSGModuleReaderParametric::initializeMap(modules, rulesContainer);
    string rewrittenSentence = axiom;
    for(auto module : currentIterationMap){
        if(!moduleNotMentionedInPredecessors(rulesContainer, module)){
            for(auto const rule:rulesContainer){
                if(conditionsForReproductionAreMet(rule, module)){
                    rewrittenSentence = injectResults(rule, module, rewrittenSentence);
                }
            }
        }
    }
    return rewrittenSentence;
}

//take the current module, execute the operation and replace it in the string
string ofxLSGrammarParametric::injectResults(ofxLSGRuleParametric rule, ModuleMapped module, string axiom){
    string replacement = "";
    for(auto successor : rule.getSuccessor()){
        map<string, string> opResults;
        for(auto op : successor.second){
            float res = op.compute(module);
            auto key = op.getKey();
            opResults.insert(make_pair(key, ofToString(res)));
        }
        string stringAfterOperation = ofxLSGUtils::mapCopyToString(opResults, successor.first);
        replacement += stringAfterOperation;
    }
    string moduleToReplace;
    moduleToReplace = getCurrentModuleKey(module);
    ofStringReplace(axiom, moduleToReplace, replacement);
    return axiom;
}

// This method is horrible, takes a module Mapped , like A: {s: 6} and returns
// a string like 'A(6)'
string ofxLSGrammarParametric::getCurrentModuleKey(ModuleMapped module){
    string res;
    res += module.first;
    if (module.second.size()>0) {
        res+="(";
    }
    int i = 0;
    for(auto number : module.second){
        res+=ofToString(number.second);
        i++;
        if(i< module.second.size()){
            res+=",";
        }
    }
    if (module.second.size()>0) {
        res+=")";
    }
    return res;
}

const bool ofxLSGrammarParametric::moduleNotMentionedInPredecessors(vector<ofxLSGRuleParametric> ruleContainer, ModuleMapped module){
    for(auto rule:ruleContainer){
        if(ofIsStringInString(rule.getPredecessor(), module.first)){
            return false;
        }
    }
    return true;
};

// This method takes vector containing a string for each rule, and for each string
// build a RuleParametric object(validating it) and put in in a container
const vector<ofxLSGRuleParametric> ofxLSGrammarParametric::getRules(vector<string> ruleList, map<string,float> _constants){
    vector<ofxLSGRuleParametric> rulesContainer;
    for(auto rule:ruleList){
        auto parts = ofSplitString(rule, "->");
        if(parts.size()==2){
            auto predecessor_and_condition = getPredecessorAndCondition(parts.at(0));
            auto predecessor = predecessor_and_condition.at(0);
            auto condition = predecessor_and_condition.at(1);
            auto successor = ofxLSGSanitizer::removeSpacesAndNewlines(parts.at(1));
            rulesContainer.push_back(ofxLSGRuleParametric(
                                                          predecessor,
                                                          condition,
                                                          successor,
                                                          _constants));
        }else{
            ofLogError("Parametric Grammar detected, but rule not in the correct format");
        }
    }
    return rulesContainer;
}



// This method takes a string containing a rule and separate the predecessor from the condition. ex 'A(x,y): y<=3', A(x,y) is the predecessor and y<=3 is the condition
// This method also consider the case where there is no condition. In this case
// the condition will be an empty strig, that will be alsway evaluated as true

// TODO, you still have to consider the case where the condition contains two
// bool, example "t==2 && s>=3"
const vector<string> ofxLSGrammarParametric::getPredecessorAndCondition(string str){
    auto stringRules = ofxLSGSanitizer::removeSpacesAndNewlines(str);
    vector<string> predecessor_and_condition;
    auto parts = ofSplitString(stringRules, ":");
    //rule with condition
    if(parts.size() == 2){
        predecessor_and_condition.push_back(parts.at(0));
        predecessor_and_condition.push_back(parts.at(1));
    //rule without condition
    }else{
        predecessor_and_condition.push_back(parts.at(0));
        predecessor_and_condition.push_back("");
    }
    return predecessor_and_condition;
}

// This method builds the modules starting from the axiom. Example, receiving this
// as axiom "B(2)A(4,4)" it returns a map, in which A and B are keys, and the 3 integers
// are converted to float. 2.0 is pushed in the vector containg the values for the key "B",
// and the two 4.0 are pushed in the vector for the key "A". So that this is the resulting
// map (in pseudocode), containing the 2 modules:
// {
//     "A": <2.0>
//     "B": <4.0, 4.0>
// }
vector<Module> ofxLSGrammarParametric::getModules(string axiom){
    vector<Module> modules;
    auto parts = ofxLSGUtils::getModulesFromString(axiom);

    for(auto part:parts){
        string key;
        vector<float> values;
        auto letter = ofxLSGUtils::grepStringInRegex(part, "[A-Za-z]");
        auto numbers = ofxLSGUtils::matchesInRegex(part, "[0-9\\.]+");
        if (letter.length() > 0){
            key = letter;
        }
        if(numbers.size() > 0){
            for(auto number : numbers){
                values.push_back(ofToFloat(number));
            }
        }
        modules.push_back(make_pair(key,values));
    }
    return modules;
}

/////////////// CONDITIONS //////////////

bool ofxLSGrammarParametric::conditionsForReproductionAreMet(ofxLSGRuleParametric rule, ModuleMapped module){
    // A reproduction take place if all of these 3 conditions are met:
    // 1) the letter in the module and the letter in the predecessor are the same
    // 2) The number of actual parameter in the module is eqaul to the number of formal parameter in the predecessor
    // 3) the reproduction conditionis evaluate to true
    // The first two condition are tested in the method "parametersAndLettersMatch", the last one in
    // "conditionsAreTrue"
    bool conditionsAreOk = conditionsAreTrue(rule.getConditions(), module);
    return parametersAndLettersMatch(rule, module) && conditionsAreOk;
}

bool ofxLSGrammarParametric::conditionsAreTrue(vector<ofxLSGCondition> conditions, ModuleMapped module){
    unsigned int count_falses = 0;
    for(auto condition:conditions){
        if(!condition.isTrue(module.second)){
            count_falses ++;
        }
    }
    return count_falses == 0;
}

bool ofxLSGrammarParametric::parametersAndLettersMatch(ofxLSGRuleParametric rule, ModuleMapped module){
    // 1) the letter in the module and the letter in the predecessor are the same
    // 2) The number of actual parameter in the module is eqaul to the number of formal parameter in the predecessor
    bool letterInModuleIsEqualToLetterInPredecessor =
        rule.getPredecessor().find(module.first) != string::npos;
    bool numberParametersAreEqual =
        rule.getPredecessorParameters().size() == module.second.size();
    return (
            letterInModuleIsEqualToLetterInPredecessor &&
            numberParametersAreEqual
    );
}
