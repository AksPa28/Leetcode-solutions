#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

#define ll long long
#define mod 1000000007

class Solution {
public:
    vector<int> minDistinctFreqPair(vector<int>& nums) {
        vector<int> freq(101, 0);
        for(int i = 0; i<nums.size(); i++){
            freq[nums[i]]++;
        }
        for (int x = 1; x <= 100; x++) {
            if (freq[x] == 0) continue;
            
            for (int y = x + 1; y <= 100; y++) {
                if (freq[y] == 0) continue;
                
                if (freq[x] != freq[y]) {
                    return {x, y};
                }
            }
        }
        
        return {-1, -1};
    }
};