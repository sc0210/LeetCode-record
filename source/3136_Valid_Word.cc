#include <string>

class Solution {
public:
    bool isVowel(char c){
        c = tolower(c);
        if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
            return true;
        return false;
    }

    bool isValid(std::string word) {

        int cntVowel=0, cntNVowel=0;
        for(auto c : word){
            if( !(isalpha(c) || isdigit(c)) )return false;
            if(isVowel(c) && !isdigit(c)) cntVowel++;
            if(!isVowel(c) && !isdigit(c)) cntNVowel++;
        }
        return (word.length()>=3) && (cntVowel>=1) && (cntNVowel>=1);
    }
};