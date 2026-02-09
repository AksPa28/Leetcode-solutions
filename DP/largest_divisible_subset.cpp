/*
    Given a set of distinct positive integers nums, return the largest subset answer such that every pair
    (answer[i], answer[j]) of elements in this subset satisfies:
        answer[i] % answer[j] == 0, or
        answer[j] % answer[i] == 0

    If there are multiple solutions, return any of them.

    Example 1:
    Input: nums = [1,2,3]
    Output: [1,2]
    Explanation: [1,3] is also accepted.
    
    Example 2:
    Input: nums = [1,2,4,8]
    Output: [1,2,4,8]
    
    Constraints:
    1 <= nums.length <= 1000
    1 <= nums[i] <= 2 * 10^9
    All the integers in nums are unique.




    We can sort the array and treat it as to find the longest divisible subsequence using the LIS method
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define ll long long
#define mod 1000000007

vector<int> populateLDS(vector<int> &ar, int n){
    vector<int> temp(n), dp(n, -1);
    int mx = -1, lastIdx = 0;
    sort(ar.begin(), ar.end());
    for(int i = 0; i<n; i++){
        temp[i] = i;
        for(int j = 0; j<i; j++){
            if(ar[j] % ar[i] == 0 && 1 + dp[j] > dp[i]){
                dp[i] = 1 + dp[j];
                temp[i] = j;
            }
        }
        if(dp[i] > mx){
            mx = dp[i];
            lastIdx = i;
        }
    }

    vector<int> ans;
    ans.push_back(ar[lastIdx]);
    while(temp[lastIdx] != lastIdx){
        lastIdx = temp[lastIdx];
        ans.push_back(ar[lastIdx]);
    }
    return ans;
}

int binary_search_sol(vector<int> &ar, int n){

    return 0;
}

int main() {
    int n;
    return 0;
}
