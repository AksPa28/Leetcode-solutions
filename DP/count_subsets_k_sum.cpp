/*
    Given an array, find subsets/subsequences with sum k
*/ 


#include <iostream>
#include<vector>

using namespace std;

#define ll long long
#define mod 1000000007

int recursion(vector<int>& ar, int index, int target, vector<vector<int>>& dp){
    // if(target == 0) return 0;
    // if(index == ar.size()-1)    return (ar[index] == target);
    // int take = ar[index] <= target ? recursion(ar, index+1, target-ar[index]) : 0;
    // int leave = recursion(ar, index+1, target);
    // return take + leave;

    if(target == 0) return 0;
    if(index == ar.size()-1)    return (ar[index] == target);
    if(dp[index][target] != -1) return dp[index][target];
    int take = ar[index] <= target ? recursion(ar, index+1, target-ar[index], dp) : 0;
    int leave = recursion(ar, index+1, target, dp);
    return dp[index][target] = take + leave;
}   

int tabulation(vector<int>& ar, int target, vector<vector<int>>& dp){
    for(int r = 0; r<dp.size(); r++){
        dp[r][0] = 1;
    }
    if(ar[0] <= target)   dp[0][ar[0]] = 1;
    for(int idx = 1; idx<ar.size(); idx++){
        for(int sum = 0; sum<=target; sum++){
            dp[idx][sum] = dp[idx-1][sum] + ((ar[idx] <= sum) ? dp[idx-1][sum - ar[idx]] : 0);
        }
    }
    return dp[ar.size()-1][target];
}

int space_optimization(vector<int>& ar, int target){
    int n = ar.size();
    vector<int> prev(target+1), cur(target+1);
    prev[0] = cur[0] = 1;

    for(int idx = 1; idx<n; idx++){
        for(int sum = 0; sum<=target; sum++){
            cur[sum] = prev[sum] + ((ar[idx] <= sum)? prev[sum-ar[idx]] : 0);
        }
        prev = cur;
    }
    return prev[target];
}


int main() {
    int k;
    vector<int> ar;
    vector<vector<int>> dp(ar.size(), vector<int> (k + 1, -1));
    cout << tabulation(ar, k, dp);
    return 0;
}
