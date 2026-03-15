/*
    Given a collection of candidate numbers (candidates) and a target number (target), 
    find all unique combinations in candidates where the candidate numbers sum to target.

    Each number in candidates may only be used once in the combination.

    Note: The solution set must not contain duplicate combinations.

    Example 1:
    Input: candidates = [10,1,2,7,6,1,5], target = 8
    Output: 
    [
    [1,1,6],
    [1,2,5],
    [1,7],
    [2,6]
    ]

    Example 2:
    Input: candidates = [2,5,2,1,2], target = 5
    Output: 
    [
    [1,2,2],
    [5]
    ]
    
    Constraints:
    1 <= candidates.length <= 100
    1 <= candidates[i] <= 50
    1 <= target <= 30
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    void backtrack(int start_idx, vector<int>& candidates, vector<int>& cur_ar, vector<vector<int>>& ans, int target, int n){
        if(target == 0){
            ans.push_back(cur_ar);
            return;
        }

        for(int i = start_idx; i<n; i++){
            if(i > start_idx && candidates[i] == candidates[i-1]){
                continue;
            }
            if(candidates[i] > target){
                break;
            }
            cur_ar.push_back(candidates[i]);
            backtrack(i+1, candidates, cur_ar, ans, target-candidates[i], n);
            cur_ar.pop_back();
        }
    }
    
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        vector<vector<int>> ans;
        vector<int> cur_ar;
        backtrack(0, candidates, cur_ar, ans, target, candidates.size());
        return ans;
    }
};
