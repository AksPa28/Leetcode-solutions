/*
    Given weights of material and their value, find the maximum value which can be obtained.
    Here there is a limit in the max weight the person can carry.

    wt = [] -> Weight of materials
    val = [] -> Value of materials
    W -> max weight user can carry

    Also assume every type of item is in infinite supply.
*/

#include <iostream>
#include <vector>

using namespace std;

#define ll long long
#define mod 1000000007

int recursion(int idx, int W, vector<int> &wt, vector<int> &val)
{
    if (idx == 0)
        return (W / wt[0]) * val[0];
    int take = INT_MIN;
    if (wt[idx] <= W)
    {
        take = recursion(idx, W - wt[idx], wt, val);
    }
    int not_take = recursion(idx - 1, W, wt, val);
    return max(take, not_take);
}

int memoize(int idx, int W, vector<int> &wt, vector<int> &val, vector<vector<int>> &dp)
{
    if (idx == 0)
        return (W / wt[0]) * val[0];
    if (dp[idx][W] != -1)
        return dp[idx][W];
    int take = INT_MIN;
    if (wt[idx] <= W)
    {
        take = recursion(idx, W - wt[idx], wt, val);
    }
    int not_take = recursion(idx - 1, W, wt, val);
    return dp[idx][W] = max(take, not_take);
}

int tabulation(int W, vector<int> &wt, vector<int> &val)
{
    int n = wt.size();
    vector<vector<int>> dp(n, vector<int>(W + 1, 0));
    for (int w = 0; w <= W; w++)
    {
        dp[0][w] = (w / wt[0]) * val[0];
    }
    for (int idx = 1; idx < n; idx++)
    {
        for (int w = 0; w <= W; w++)
        {
            dp[idx][w] = dp[idx - 1][w];

            if (wt[idx] <= w)
                dp[idx][w] = max(dp[idx - 1][w], val[idx] + dp[idx][w - wt[idx]]);
        }
    }
    return dp[n - 1][W];
}

int space_opt(int W, vector<int> &wt, vector<int> &val)
{
    int n = wt.size();
    vector<int> prev(W + 1, 0), cur(W + 1, 0);
    for (int w = 0; w <= W; w++)
    {
        prev[w] = (w / wt[0]) * val[0];
    }
    for (int idx = 1; idx < n; idx++)
    {
        for (int w = 0; w <= W; w++)
        {
            cur[w] = prev[w];

            if (wt[idx] <= w)
                cur[w] = max(prev[w], val[idx] + cur[w - wt[idx]]);
        }
        prev = cur;
    }
    return prev[W];
}

int super_space_opt(int W, vector<int> &wt, vector<int> &val)
{
    int n = wt.size();
    vector<int> prev(W + 1, 0);
    for (int w = 0; w <= W; w++)
    {
        prev[w] = (w / wt[0]) * val[0];
    }
    for (int idx = 1; idx < n; idx++)
    {
        for (int w = 0; w <= W; w++)
        {
            if (wt[idx] <= w)
                prev[w] = max(prev[w], val[idx] + prev[w - wt[idx]]);
        }
    }
    return prev[W];
}

int main()
{
    int n;
    vector<int> wt(n), val(n);
    int W;
    return 0;
}
