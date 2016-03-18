#include <RuleTest.h>

void RuleTest::executeTest(){
    auto result = ofxLSystemGrammar::buildSentences(
                                                    this->getRules(),
                                                    this->getDepth(),
                                                    this->getAxiom());
    this->setResult(result);
    passed = expectToBeEqual(this->getResult(), this->getExpectedResult());
}


bool RuleTest::expectToBeEqual(vector<string> v1, vector<string> v2){
    if(v2.size() != v1.size()){
        return false;
    }
    std::set<string> s1(v1.begin(), v1.end());
    std::set<string> s2(v2.begin(), v2.end());
    return s1 == s2;
};