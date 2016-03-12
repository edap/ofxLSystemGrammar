#include "ParametricGrammar.h"

string ParametricGrammar::generateSentence(vector<string> ruleList, int _numberOfSteps, string _axiom){
    string finalSentence = _axiom;
    auto rulesContainer = getRules(ruleList);

    //for(unsigned int i = 0; i< _numberOfSteps; i++){
    for(unsigned int i = 0; i< 4; i++){
        finalSentence =  rewriteSentence(finalSentence, rulesContainer);
        cout << finalSentence << endl;
    }
    return finalSentence;
}

string ParametricGrammar::rewriteSentence(string axiom, vector<RuleParametric> rulesContainer){
    auto modules = getModules(axiom);
    //mutable vars
    auto currentIterationMap = initializeMap(modules, rulesContainer);
    string fin = "";
    for(auto module:currentIterationMap ){
        if(moduleNotMentionedInPredecessors(rulesContainer, module)){
            fin += module.first;
        }else{
            for(auto const rule:rulesContainer){
                if(conditionsForReproductionAreMet(rule, module)){
                    for(auto successor:rule.getSuccessor()){
                        map<string, string> opResults;
                        for(auto op : successor.second){
                            float res = op.compute(module);
                            auto key = op.getKey();
                            opResults.insert(make_pair(key, ofToString(res)));
                        }
                        auto stringAfterOperation = Utils::mapCopyToString(opResults, successor.first);
                        fin += stringAfterOperation;
                    }
                }
            }
        }

    }
    return fin;
}


// This method iterates through modules and rules in order to initialize a map
// where the values are assigned to the params. For example, if we have a module
// That is A(3,4) and the predecessor parameters for the module with key "A"
// are x,y we initialize a map like this (pseudocode):
// A:{
// {x: 3},
// {y: 4}
// }
// if we have a module that is simply C, and all the predecessors does not mentions
// how this moudle should or should not reproduce itself, we simply leave it as it is
// and we forward it to the next generation
vector<pair <string, map<string, float>>> ParametricGrammar::initializeMap(
    vector<pair<string,vector<float>>> modules, vector<RuleParametric> rulesContainer)
    {
    vector<pair <string, map<string, float>>> initializedMap;
    auto predContainer = getVarNamesOutOfRules(rulesContainer);

    for(auto const module:modules){
        if(moduleNotMentionedInPredecessors(predContainer, module)){
            map<string, float> emptyMap;
            initializedMap.push_back(make_pair(module.first,emptyMap));
        }else{
            for(auto const predecessor:predContainer){
                if(predecessorMatchModules(predecessor, module)){
                    auto predString = predecessor.first;
                    auto predecessorParameters = predecessor.second;
                    map<string, float> parAndVal;
                    for(unsigned int i = 0; i < predecessorParameters.size(); i++){
                        parAndVal.insert(make_pair(predecessorParameters.at(i),
                                              module.second.at(i)));
                    }
                    initializedMap.push_back(make_pair(module.first,parAndVal));
                }
            }
        }
    }
    return initializedMap;
}

const bool ParametricGrammar::moduleNotMentionedInPredecessors(map<string,vector<string>> predecessors, pair<string,vector<float>> module){
    for(auto pred:predecessors){
        if(ofIsStringInString(pred.first, module.first)){
            return false;
        }
    }
    return true;
};

const bool ParametricGrammar::moduleNotMentionedInPredecessors(vector<RuleParametric> ruleContainer, pair <string, map<string, float>> module){
    for(auto rule:ruleContainer){
        if(ofIsStringInString(rule.getPredecessor(), module.first)){
            return false;
        }
    }
    return true;
};

// This method takes vector containing a string for each rule, and for each string
// build a RuleParametric object(validating it) and put in in a container
const vector<RuleParametric> ParametricGrammar::getRules(vector<string> ruleList){
    vector<RuleParametric> rulesContainer;
    for(auto rule:ruleList){
        auto parts = ofSplitString(rule, "->");
        if(parts.size()==2){
            auto predecessor_and_condition = getPredecessorAndCondition(parts.at(0));
            auto predecessor = predecessor_and_condition.at(0);
            auto condition = predecessor_and_condition.at(1);
            auto successor = Sanitizer::removeSpacesAndNewlines(parts.at(1));
            rulesContainer.push_back(RuleParametric(predecessor, condition, successor));
        }else{
            ofLogError("Parametric Grammar detected, but rule not in the correct format");
        }
    }
    return rulesContainer;
}

// This function iterates throug all the rules and for each rule it takes out the predecessor
// and its variable name. ex: If the rules are 4, and the predecessor are:
// A(x,y)
// A(x,y)
// B(x)
// B(x)
// the methods reurns a map like this:
// {"A(x,y)" => "x,y", "B(x)" => x}
const map<string,vector<string>> ParametricGrammar::getVarNamesOutOfRules(vector<RuleParametric> rulesContainer){
    map<string,vector<string>>predContainer;
    for(auto const rule:rulesContainer){
        auto predString = rule.getPredecessor();
        if (predContainer.count(predString)) continue;
        predContainer.insert(make_pair(predString, rule.getPredecessorParameters()));
    }
    return predContainer;
}

// This method takes a string containing a rule and separate the predecessor from the condition
// putting both of them in a container
// TODO, you still have to consider the case where the condition contains two
// bool, example "t==2 && s>=3"
// TODO, you have to consider the case where there is no condition. Example page 47 The Alg. beauty of Nature
const vector<string> ParametricGrammar::getPredecessorAndCondition(string str){
    auto stringRules = Sanitizer::removeSpacesAndNewlines(str);
    vector<string> predecessor_and_condition;
    auto parts = ofSplitString(stringRules, ":");
    predecessor_and_condition.push_back(parts.at(0));
    predecessor_and_condition.push_back(parts.at(1));
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
vector<pair<string,vector<float>>> ParametricGrammar::getModules(string axiom){
    vector<pair<string,vector<float>>> modules;
    auto parts = Utils::getModulesFromString(axiom);
    for(auto part:parts){
        if (part.length() == 0) continue;
        string key;
        vector<float> values;
        for(auto letter:part){
            if(isalpha(letter)){
                key = ofToString(letter);
            }
            if(isdigit(letter)){
                values.push_back(ofToFloat(ofToString(letter)));
            }
        }
        modules.push_back(make_pair(key,values));
        //modules[key] = values;
    }
    return modules;
}

/////////////// CONDITIONS //////////////

bool ParametricGrammar::conditionsForReproductionAreMet(RuleParametric rule, pair<string, map<string,float>> module){
    // A reproduction take place if all of these 3 conditions are met:
    // 1) the letter in the module and the letter in the predecessor are the same
    // 2) The number of actual parameter in the module is eqaul to the number of formal parameter in the predecessor
    // 3) the reproduction conditionis evaluate to true
    // The first two condition are tested in the method "parametersAndLettersMatch", the last one in
    // "conditionsAreTrue"
    bool conditionsAreOk = conditionsAreTrue(rule.getConditions(), module);
    return parametersAndLettersMatch(rule, module) && conditionsAreOk;
}

bool ParametricGrammar::conditionsAreTrue(vector<Condition> conditions, pair<string, map<string,float>> module){
    unsigned int count_falses = 0;
    for(auto condition:conditions){
        if(!condition.isTrue(module.second)){
            count_falses ++;
        }
    }
    return count_falses == 0;
}

bool ParametricGrammar::predecessorMatchModules(pair<string,vector<string>> predecessor, pair<string,vector<float>> module){
    // 1) the letter in the module and the letter in the predecessor are the same
    // 2) The number of actual parameter in the module is eqaul to the number of formal parameter in the predecessor
    bool letterInModuleIsEqualToLetterInPredecessor =
    predecessor.first.find(module.first) != string::npos;
    bool numberParametersAreEqual =
    predecessor.second.size() == module.second.size();
    return (
            letterInModuleIsEqualToLetterInPredecessor &&
            numberParametersAreEqual
    );
}

bool ParametricGrammar::parametersAndLettersMatch(RuleParametric rule, pair<string, map<string,float>> module){
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