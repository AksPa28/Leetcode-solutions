/*
    You are given an integer array coins representing coins of different denominations and
    an integer amount representing a total amount of money.

    Return the fewest number of coins that you need to make up that amount.
    If that amount of money cannot be made up by any combination of the coins, return -1.
    You may assume that you have an infinite number of each kind of coin.


    Example 1:
        Input: coins = [1,2,5], amount = 11
        Output: 3
        Explanation: 11 = 5 + 5 + 1

    Example 2:
        Input: coins = [2], amount = 3
        Output: -1

    Example 3:
        Input: coins = [1], amount = 0
        Output: 0

    Constraints:
        1 <= coins.length <= 12
        1 <= coins[i] <= 231 - 1
        0 <= amount <= 104
*/

#include <iostream>
#include <vector>

using namespace std;

#define ll long long
#define mod 1000000007

int recursion(vector<int> &coins, int idx, int amount)
{
    if (!idx)
        return (amount % coins[idx]) ? 1e9 : amount / coins[idx];
    int not_take = recursion(coins, idx - 1, amount);
    int take = 1e9;
    if (coins[idx] <= amount)
        take = 1 + (coins, idx, amount - coins[idx]);
    return min(take, not_take);
}

int memoize(vector<int> &coins, int idx, int amount, vector<vector<int>> &dp)
{
    if (!idx)
        return (amount % coins[idx]) ? 1e9 : amount / coins[idx];

    if (dp[idx][amount] != -1)
        return dp[idx][amount];

    int not_take = memoize(coins, idx - 1, amount, dp);
    int take = 1e9;
    if (coins[idx] <= amount)
        take = 1 + (coins, idx, amount - coins[idx]);
    return dp[idx][amount] = min(take, not_take);
}

int tabulation(vector<int> ar, int amount)
{
    int n = ar.size();
    vector<vector<int>> dp(n, vector<int>(amount + 1, 0));
    for (int amt = 0; amt < amount; amt++)
    {
        dp[0][amt] = (amt % ar[0]) ? 1e9 : (amt / ar[0]);
    }
    for (int idx = 1; idx < n; idx++)
    {
        for (int amt = 0; amt < amount; amt++)
        {
            int not_take = dp[idx - 1][amt];
            int take = 1e9;
            if (ar[idx] <= amt)
                take = 1 + dp[idx][amt - ar[idx]];
            dp[idx][amt] = min(take, not_take);
        }
    }
    return (dp[n - 1][amount] >= 1e9) ? dp[n - 1][amount] : -1;
}

int space_opt(vector<int> ar, int amount)
{
    int n = ar.size();
    vector<int> prev(amount + 1, 0), cur(amount + 1, 0);
    for (int amt = 0; amt < amount; amt++)
    {
        prev[amt] = (amt % ar[0]) ? 1e9 : (amt / ar[0]);
    }
    for (int idx = 1; idx < n; idx++)
    {
        for (int amt = 0; amt < amount; amt++)
        {
            int not_take = prev[amt];
            int take = 1e9;
            if (ar[idx] <= amt)
                take = 1 + cur[amt - ar[idx]];
            cur[amt] = min(take, not_take);
        }
        prev = cur;
    }
    return (prev[amount] >= 1e9) ? prev[amount] : -1;
}

int main()
{
    vector<int> coins;
    int n = coins.size();
    int amount;
    recursion(coins, n - 1, amount);
    vector<vector<int>> dp(n, vector<int>(amount + 1, -1));
    memoize(coins, n - 1, amount, dp);
    tabulation(coins, amount);
    space_opt(coins, amount);
    return 0;
}
