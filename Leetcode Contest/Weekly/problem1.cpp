#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    string trimTrailingVowels(string s) {
        int last_idx = s.length();
        for(int i = s.length()-1; i>=0; i--){
            if(s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u'){
                last_idx = i;
            }
            else{
                break;
            }
        }
        return s.substr(0, last_idx + 1);
    }
};