/*
    You are given an integer array coins representing coins of different denominations and
    an integer amount representing a total amount of money.

    Return the number of combinations that make up that amount.
    If that amount of money cannot be made up by any combination of the coins, return 0.

    You may assume that you have an infinite number of each kind of coin.

    The answer is guaranteed to fit into a signed 32-bit integer.

    Example 1:
    Input: amount = 5, coins = [1,2,5]
    Output: 4
    Explanation: there are four ways to make up the amount:
    5=5
    5=2+2+1
    5=2+1+1+1
    5=1+1+1+1+1

    Example 2:
    Input: amount = 3, coins = [2]
    Output: 0
    Explanation: the amount of 3 cannot be made up just with coins of 2.

    Example 3:
    Input: amount = 10, coins = [10]
    Output: 1

    Constraints:
    1 <= coins.length <= 300
    1 <= coins[i] <= 5000
    All the values of coins are unique.
    0 <= amount <= 5000
*/

#include <iostream>
#include <vector>

using namespace std;

#define ll long long
#define mod 1000000007

int recursion(int idx, vector<int> &ar, int target)
{
    if (idx == 0)
        return (target % ar[0]) == 0;
    int take = 0;
    if (ar[idx] <= target)
    {
        take = recursion(idx, ar, target - ar[idx]);
    }
    int not_take = recursion(idx - 1, ar, target);
    return take + not_take;
}

int memoize(int idx, vector<int> &ar, int target, vector<vector<int>> &dp)
{
    if (idx == 0)
        return (target % ar[0]) == 0;

    if (dp[idx][target] != -1)
        return dp[idx][target];
    int take = 0;
    if (ar[idx] <= target)
    {
        take = recursion(idx, ar, target - ar[idx]);
    }
    int not_take = recursion(idx - 1, ar, target);
    return dp[idx][target] = take + not_take;
}

int tabulation(vector<int> &ar, int target)
{
    int n = ar.size();
    vector<vector<int>> dp(n, vector<int>(target + 1, 0));
    for (int sum = 0; sum <= target; sum++)
    {
        dp[0][sum] = (sum % ar[0] == 0);
    }

    for (int idx = 1; idx < n; idx++)
    {
        for (int sum = 0; sum <= target; sum++)
        {
            dp[idx][sum] = dp[idx - 1][sum];
            if (ar[idx] <= sum)
                dp[idx][sum] += dp[idx][sum - ar[idx]];
        }
    }
    return dp[n - 1][target];
}

int super_space_opt(int n, vector<int> &ar, int target)
{
    vector<int> prev(target + 1, 0);
    for (int sum = 0; sum <= target; sum++)
    {
        prev[sum] = (sum % ar[0] == 0);
    }
    for (int idx = 1; idx < n; idx++)
    {
        for (int sum = target; sum >= 0; sum--)
        {
            if (ar[idx] <= sum)
                prev[sum] += prev[sum - ar[idx]];
        }
    }
    return prev[target];
}

int main()
{
    int n;
    vector<int> coins(n);
    int target;
    vector<vector<int>> dp(n, vector<int>(target + 1, -1));
    return 0;
}
