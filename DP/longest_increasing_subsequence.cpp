/**
    Given an integer array nums, return the length of the longest strictly increasing subsequence.

    Example 1:
    Input: nums = [10,9,2,5,3,7,101,18]
    Output: 4
    Explanation: The longest increasing subsequence is [2,3,7,101], therefore the length is 4.

    Example 2:
    Input: nums = [0,1,0,3,2,3]
    Output: 4

    Example 3:
    Input: nums = [7,7,7,7,7,7,7]
    Output: 1
    
    Constraints:
    1 <= nums.length <= 2500
    -104 <= nums[i] <= 104
    
    Follow up: Can you come up with an algorithm that runs in O(n log(n)) time complexity?
*/

#include <iostream>
#include <vector>

using namespace std;

#define ll long long
#define mod 1000000007

int recursion(int idx, int prev_idx, vector<int> &ar, int n){
    if(idx == n){
        return 0;
    }
    int len = 0;
    if(prev_idx == -1 || ar[idx] > ar[prev_idx]){
        len = 1 + recursion(idx+1, idx, ar, n);
    }
    return len = max(len, recursion(idx+1, prev_idx, ar, n));
}

int memoized(int idx, int prev_idx, vector<int> &ar, int n, vector<vector<int>> &dp){
    if(idx == n){
        return 0;
    }
    if(dp[idx][prev_idx+1] != -1){
        return dp[idx][prev_idx+1];
    }

    int len = 0;
    if(prev_idx == -1 || ar[idx] > ar[prev_idx]){
        len = 1 + memoized(idx+1, idx, ar, n, dp);
    }
    return dp[idx][prev_idx+1] = max(len, memoized(idx+1, prev_idx, ar, n, dp));
}

int tabulation(vector<int> &ar, int n){
    vector<vector<int>> dp(n+1, vector<int> (n+1, 0));
    int prev_index = 0;
    for(int i = n-1; i>=0; i--){
        for(int prev_idx = i-1; prev_idx>=-1; prev_idx--){
            int len = dp[i + 1][prev_idx + 1];
            if(prev_idx == -1 || ar[i] > ar[prev_idx]){
                len = max(len, 1 + dp[i+1][i+1]);
            }
            dp[i][prev_idx+1] = len;
        }
    }
    return dp[0][0];
}

int space_opt(vector<int> &ar, int n){
    vector<int> calculated(n+1, 0), cur(n+1, 0);
    for(int i = n-1; i>=0; i--){
        for(int prev_idx = i-1; prev_idx>=-1; prev_idx--){
            int len = calculated[prev_idx+1];
            if(prev_idx==-1 || ar[i] > ar[prev_idx]){
                len = max(len, 1 + calculated[i+1]);
            }
            cur[prev_idx+1] = len;
        }
        calculated = cur;
    }
    return calculated[0];
}

int not_using_recursion(vector<int> &ar, int n){
    vector<int> dp(n+1, 0);
    int mx = -1;
    for(int i = 0; i<n; i++){
        for(int prev = 0; prev<i; prev++){
            if(ar[prev] < ar[i]){
                dp[i] = max(dp[i], 1 + dp[prev]);
            }
        }
        mx = max(mx, dp[i]);
    }
    return mx;
}

int find_lower_bound(vector<int> &ar, int num, int high){
    int low = 0, ans = 0;
    while(high >= low){
        int mid = low + (high - low)/2;
        if(ar[mid] >= num){
            ans = mid;
            high = mid - 1;
        }
        else{
            low = mid + 1;
        }
    }
    return ans;
}

int binary_search_sol(vector<int> &ar, int n){
    vector<int> lis_temp;
    lis_temp.push_back(ar[0]);
    int len = 1;
    for(int i = 1; i<n; i++){
        if(ar[i] > lis_temp[len-1]){
            len++;
            lis_temp.push_back(ar[i]);
        }
        else{
            int pos = find_lower_bound(lis_temp, ar[i], len-1);
            lis_temp[pos] = ar[i];
        }
    }
    return len;
}


int main() {
    int n;
    vector<vector<int>> dp(n, vector<int> (n+1, -1));
    return 0;
}
