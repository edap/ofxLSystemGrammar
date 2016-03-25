#include "ofxLSGModuleReaderParametric.h"

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
// and we forward it to the next generation.
// if we have a module that is F(s), and it is not mentioned in the predecessor, we search it in the successors
vector<ModuleMapped> ofxLSGModuleReaderParametric::initializeMap(
                                                           vector<Module> modules, vector<ofxLSGRuleParametric> rulesContainer)
{
    vector<ModuleMapped> initializedMap;
    vector<Module> modulesToSearchInSuccessor;
    auto predContainer = getVarNamesOutOfRules(rulesContainer);

    for(auto const module:modules){
        if(moduleNotMentionedInPredecessors(predContainer, module)){
            //map<string, float> emptyMap;
            //initializedMap.push_back(make_pair(module.first,emptyMap));
            modulesToSearchInSuccessor.push_back(module);
        }else{
            for(auto const predecessor:predContainer){
                if(matchModules(predecessor, module)){
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

    for(auto module : modulesToSearchInSuccessor){
        // we iterate through the successor too, to see if there are some parameters
        // for modules that were not present in the predecessor
        for(auto const rule:rulesContainer){
            auto successors = rule.getSuccessorWithParameters();

            for (auto succ : successors){
                if(matchModules(succ, module)){
                    auto succString = succ.first;
                    auto successorParameters = succ.second;
                    map<string, float> parAndVal;
                    for(unsigned int i = 0; i < successorParameters.size(); i++){
                        parAndVal.insert(make_pair(successorParameters.at(i),
                                                   module.second.at(i)));
                    }
                    initializedMap.push_back(make_pair(module.first,parAndVal));
                }
            }
        }
    }
    return initializedMap;
}

// This function iterates throug all the rules and for each rule it takes out the predecessor
// and its variable name. ex: If the rules are 4, and the predecessor are:
// A(x,y)
// A(x,y)
// B(x)
// B(x)
// the methods reurns a map like this:
// {"A(x,y)" => "x,y", "B(x)" => x}
// ti Deve anche ritornare F(s) => s
const map<string,vector<string>> ofxLSGModuleReaderParametric::getVarNamesOutOfRules(vector<ofxLSGRuleParametric> rulesContainer){
    map<string,vector<string>>predContainer;
    for(auto const rule:rulesContainer){
        auto predString = rule.getPredecessor();
        if (predContainer.count(predString)) continue;
        predContainer.insert(make_pair(predString, rule.getPredecessorParameters()));
    }
    return predContainer;
}

bool ofxLSGModuleReaderParametric::matchModules(pair<string,vector<string>> predecessor, Module module){
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

const bool ofxLSGModuleReaderParametric::moduleNotMentionedInPredecessors(map<string,vector<string>> predecessors, Module module){
    for(auto pred:predecessors){
        if(ofIsStringInString(pred.first, module.first)){
            return false;
        }
    }
    return true;
};
