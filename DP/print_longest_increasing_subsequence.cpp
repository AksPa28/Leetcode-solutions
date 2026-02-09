/*
    Print longest increasing subsequence of a given array


            5   4   11   1   16  8
    dp      1   1    2   1    3  2
    hash    0   1    0   3    2   0 (Initially = i where i is index)
*/

#include <iostream>
#include <vector>

using namespace std;

#define ll long long
#define mod 1000000007

vector<int> populateLIS(vector<int> &ar, int n){
    vector<int> dp(n, -1), hash(n);
    int mx = -1, lastIdx = 0;
    for(int i = 0; i<n; i++){
        hash[i] = i;
        for(int prev = 0; prev<i; prev++){
            if(ar[prev] > ar[i] && 1 + dp[prev] > dp[i]){
                dp[i] = 1 + dp[prev];
                hash[i] = prev;
            }
        }
        if(dp[i] > mx){
            mx = dp[i];
            lastIdx = i;
        }
    }

    vector<int> lis;
    lis.push_back(ar[lastIdx]);
    while(hash[lastIdx] != lastIdx){
        lastIdx = hash[lastIdx];
        lis.push_back(ar[lastIdx]);
    }
    reverse(lis.begin(), lis.end());
    return lis;
}

int main() {
    vector<int> ar;
    return 0;
}
