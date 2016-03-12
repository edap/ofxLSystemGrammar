#pragma once
#include <regex>

class Utils{
public:
    static int countSubstring(const std::string& str, const std::string& sub){
        if (sub.length() == 0) return 0;
        int count = 0;
        for (size_t offset = str.find(sub); offset != std::string::npos;
             offset = str.find(sub, offset + sub.length())){
            ++count;
        }
        return count;
    }

    static bool isStringInRegex(string _line, string _reg){
        regex regEx(_reg, regex_constants::icase);
        if (regex_match(_line, regEx)) {
            return true;
        }else{
            return false;
        }
    }

    static string grepStringInRegex(string _str, string _reg){
        smatch match;
        regex regEx(_reg);
        stringstream buffer;
        while (regex_search(_str,match,regEx)) {
            for (auto x : match){
                buffer << x;
            }
            _str = match.suffix().str();
        }
        return buffer.str();
    }

//    static vector<string> matchesInRegex(string _str, string _reg){
//        auto str = _str;
//        regex regEx(_reg);
//        vector<string> results;
//        auto wordsBegin = sregex_iterator(str.begin(), str.end(), regEx);
//        auto wordsEnd = sregex_iterator();
//        for(std::sregex_iterator i = wordsBegin; i != wordsEnd; ++i){
//            smatch m = *i;
//            results.push_back(m.str());
//        }
//        return results;
//    }

    static vector<string> matchesInRegex(string subject, string reg){
        vector<string> results;
        try {
            regex re(reg);
            sregex_iterator next(subject.begin(), subject.end(), re);
            sregex_iterator end;
            while (next != end) {
                smatch match = *next;
                results.push_back(match.str());
                next++;
            }
        } catch (std::regex_error& e) {
            // Syntax error in the regular expression
            ofLogError("Error in regular expression");
        }
        return results;
    }

    static string stripFirstAndLastChar(string _str){
        _str = _str.substr(1, _str.size() - 2);
        return _str;
    }

    static vector<string> matchesGroupsInRegex(string _str, string _reg){
        smatch matches;
        regex regEx(_reg);
        vector<string> results;
        regex_search(_str, matches, regEx);
        for(auto res:matches){
            results.push_back(res);
        }
        return results;
    }


    // it takes a imap like: {"A" => "BB", "B" => "A"}, and, applied
    // to the string "ABAA" it returns "BBABBBB"
    static string mapCopyToString(const map<string,string>& m, const string& str) {
        string sout;

        map<string,string>::const_iterator i;
        for(size_t pos = 0; pos < str.size(); ++pos) {
            for(i = m.begin(); i != m.end() && str.find(i->first, pos) != pos; ++i);
            if(i != m.end()) {
                sout.append(i->second);
                pos += i->first.length() - 1;
                continue;
            }
            sout.append(1, str[pos]);
        }
        return sout;
    }

    // see documentation about the regex
    static vector<string> getModulesFromString(string successor){
        // This regex deserves an explanation. Taking a string like:
        // "A(2.232,4)B(6,9)C(x,y)D(x+y)E(x/2)FG(x*y)H(9-6)L(x*6,0)M(4*(x+6))N(*)[+A(s/R)]"
        // it returns a vector containing
        //  A(2.232,4)
        //  B(6,9)
        //  C(x,y)
        //  D(x+y)
        //  E(x/2)
        //  F
        //  G(x*y)
        //  H(9-6)
        //  L(x*6,0)
        //  M(4*(x+6))
        //  N(*)
        //  [+A(s/R)]
        // Explanation. This regex consist of 2 groups, separated by the |. The first group match everything except the
        // last part [+A(s/R)]. This part is matched by the second group. Let's see only the first group.
        // "[A-Z](big-regex)*" this means take any string that start with a capital letter, follow by zero or more
        // elements that match the big-regex
        // big-regex: "\\([\\(\\)0-9a-z,\\.\\+\\*\\/-]+\\)"
        // match any group that starts with a ( and contains one or more of those:
        // ( and ),numbers and letters, commas, ., +, *, /, - and ends with )
        auto parts = Utils::matchesInRegex(
                                           successor, "([A-Z](\\([\\(\\)0-9a-z,\\.\\+\\*\\/-]+\\))*)|(\\[[\\(\\)0-9a-zA-Z,\\.\\+\\*\\/-]+\\])"
                                           );
        return parts;
    }
};

