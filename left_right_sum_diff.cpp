/*
    You are given a 0-indexed integer array nums of size n.

    Define two arrays leftSum and rightSum where:

    leftSum[i] is the sum of elements to the left of the index i in the array nums. 
    If there is no such element, leftSum[i] = 0.
    rightSum[i] is the sum of elements to the right of the index i in the array nums. 
    If there is no such element, rightSum[i] = 0.
    Return an integer array answer of size n where answer[i] = |leftSum[i] - rightSum[i]|.

    Example 1:
    Input: nums = [10,4,8,3]
    Output: [15,1,11,22]
    Explanation: The array leftSum is [0,10,14,22] and the array rightSum is [15,11,3,0].
    The array answer is [|0 - 15|,|10 - 11|,|14 - 3|,|22 - 0|] = [15,1,11,22].
    
    Example 2:
    Input: nums = [1]
    Output: [0]
    Explanation: The array leftSum is [0] and the array rightSum is [0].
    The array answer is [|0 - 0|] = [0].
    
    Constraints:
    1 <= nums.length <= 1000
    1 <= nums[i] <= 105
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:

    vector<int> noSpaceSoln(vector<int>& nums){
        int n = nums.size();
        vector<int> ans(n, 0);
        if(n == 1){
            return ans;
        }
        int sum = 0, leftsum = 0, rightsum = 0;
        for(int i = 0; i<n; i++){
            sum += nums[i];
        }
        for(int i = 0; i<n; i++){
            rightsum = sum - leftsum - nums[i];
            ans[i] = abs(rightsum-leftsum);
            leftsum += nums[i];
        }
        return ans;
    }

    vector<int> leftRightDifference(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(n, 0);
        if(n == 1){
            return ans;
        }
        vector<int> presum(n, 0), postsum(n, 0);
        for(int i = 1; i<n; i++){
            presum[i] = presum[i-1] + nums[i-1];
        }
        for(int i = n-2; i>=0; i--){
            postsum[i] = postsum[i+1] + nums[i+1];
        }
        for(int i = 0; i<n; i++){
            ans[i] = abs(presum[i] - postsum[i]);
        }
        return ans;
    }
};
