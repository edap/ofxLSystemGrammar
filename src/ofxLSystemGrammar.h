#pragma once
#include "ofMain.h"

#include "ofxLSGRuleStandard.h"
#include "ofxLSGRuleParametric.h"
#include "ofxLSGRuleStochastic.h"
#include "ofxLSGSanitizer.h"
#include "ofxLSGrammarDetector.h"
#include "ofxLSGrammarStochastic.h"
#include "ofxLSGrammarStandard.h"
#include "ofxLSGrammarParametric.h"

typedef map<string,float> Constants;

class ofxLSystemGrammar {
  public:
    static const vector<string> buildSentences(vector<string> _rules, const unsigned int _n_steps, string _axiom, map<string,float> _constants = Constants());
    static const string detectGrammarType(vector<string> _rules);
  private:
    static const vector<string> sanitizeRules(vector<string> _str);
};
