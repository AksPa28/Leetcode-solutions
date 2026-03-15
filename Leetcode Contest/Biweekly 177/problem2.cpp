#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    string mergeCharacters(string s, int k) {
        vector<vector<int>> freq_pos(26, vector<int> ());
        string ans;
        int subtract = 0;
        for(int i = 0; i<s.size(); i++){
            int idx = s[i] - 'a';
            int sz = freq_pos[idx].size();
            if(sz > 0){
                int last_idx = freq_pos[idx][sz-1];
                if(i-last_idx-subtract <= k){
                    subtract++;
                    continue;
                }
            }
            ans.push_back(s[i]);
            freq_pos[idx].push_back(i-subtract);
        }
        return ans;
    }
};
