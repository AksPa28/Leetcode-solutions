/*
    You have a bag which can bear upto weight W, you have an array of elements which have a value and a weight
    Collect the maximum value the bag can bear, cannot exceed weight W.

    ar[i][0] -> value of the element
    ar[i][1] -> weight of the element

    Ex: W = 4
    ar = [[20, 2], [20, 2], [18, 1], [5, 2], [23, 3]]
    Ans: 41 = ar[1] + ar[4]

*/

#include <iostream>
#include <vector>

using namespace std;

#define ll long long
#define mod 1000000007

int recursive(vector<vector<int>> &ar, int W, int index)
{
    if (index == 0)
        return ar[index][1] <= W ? ar[index][0] : 0;

    return max(
        recursive(ar, index - 1, W),
        (ar[index][1] <= W) ? (ar[index][0] + recursive(ar, index - 1, W - ar[index][1])) : INT_MIN);
}

int memoize(vector<vector<int>> &ar, int W, int index, vector<vector<int>> &dp)
{
    if (index == 0)
        return ar[index][1] <= W ? ar[index][0] : 0;
    if (dp[index][W] != -1)
        return dp[index][-1];

    return dp[index][W] = max(
               memoize(ar, index - 1, W, dp),
               (ar[index][1] <= W) ? (ar[index][0] + memoize(ar, index - 1, W - ar[index][1], dp)) : INT_MIN);
}

int tabulation(vector<vector<int>> &ar, int W, vector<vector<int>> &dp)
{
    int n = ar.size();
    for (int wt = ar[0][0]; wt <= W; wt++)
    {
        dp[0][wt] = ar[0][0];
    }
    for (int idx = 1; idx < n; idx++)
    {
        for (int wt = 0; wt <= W; wt++)
        {
            dp[idx][wt] = max(
                dp[idx - 1][wt],
                ((ar[idx][1] <= wt) ? ar[idx][0] + dp[idx - 1][wt - ar[idx][1]] : INT_MIN));
        }
    }
    return dp[n - 1][W];
}

int space_opt(vector<vector<int>> &ar, int W)
{
    int n = ar.size();
    vector<int> prev(W + 1), cur(W + 1);

    for (int wt = ar[0][0]; wt <= W; wt++)
    {
        prev[wt] = ar[0][0];
    }

    for (int idx = 1; idx < n; idx++)
    {
        for (int wt = 0; wt <= W; wt++)
        {
            cur[wt] = max(
                prev[wt],
                ((ar[idx][1] <= wt) ? ar[idx][0] + prev[wt - ar[idx][1]] : INT_MIN));
        }
        prev = cur;
    }

    return prev[W];
}

int more_space_opt(vector<vector<int>> &ar, int W)
{
    int n = ar.size();
    vector<int> prev(W + 1);

    for (int wt = ar[0][0]; wt <= W; wt++)
    {
        prev[wt] = ar[0][0];
    }

    for (int idx = 1; idx < n; idx++)
    {
        for (int wt = W; wt >= 0; wt--)
        {
            prev[wt] = max(
                prev[wt],
                ((ar[idx][1] <= wt) ? ar[idx][0] + prev[wt - ar[idx][1]] : INT_MIN));
        }
    }
    return prev[W];
}

int main()
{
    int n;
    cin >> n;
    vector<vector<int>> ar(n, vector<int>(2));
    for (int i = 0; i < n; i++)
    {
        cin >> ar[i][0] >> ar[i][1];
    }
    return 0;
}
