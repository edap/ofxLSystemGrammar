#pragma once
#include "ofMain.h"
#include "ofxLSGRuleParametric.h"
#include "ofxLSGUtils.h"
#include "ofxLSGSanitizer.h"

typedef pair<string,vector<float>> Module; // like A[1.0,2.0]
typedef pair<string, map<string, float>> ModuleMapped; // like A{x:1.0, y: 2.0}

class ofxLSGModuleReaderParametric{
public:
    static vector<ModuleMapped> initializeMap(vector<Module> modules, vector<ofxLSGRuleParametric> ruleContainer);
    static const map<string,vector<string>> getVarNamesOutOfRules(vector<ofxLSGRuleParametric> rulesContainer);
    static bool matchModules(pair<string,vector<string>>, Module module);
    static const bool moduleNotMentionedInPredecessors(map<string,vector<string>> predecessors, Module module);
};
