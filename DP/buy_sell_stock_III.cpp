/*
    You are given an array prices where prices[i] is the price of a given stock on the ith day.

    Find the maximum profit you can achieve. You may complete at most two transactions.

    Note: You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).

    Example 1:
    Input: prices = [3,3,5,0,0,3,1,4]
    Output: 6
    Explanation: Buy on day 4 (price = 0) and sell on day 6 (price = 3), profit = 3-0 = 3.
    Then buy on day 7 (price = 1) and sell on day 8 (price = 4), profit = 4-1 = 3.

    Example 2:
    Input: prices = [1,2,3,4,5]
    Output: 4
    Explanation: Buy on day 1 (price = 1) and sell on day 5 (price = 5), profit = 5-1 = 4.
    Note that you cannot buy on day 1, buy on day 2 and sell them later,
    as you are engaging multiple transactions at the same time. You must sell before buying again.

    Example 3:
    Input: prices = [7,6,4,3,1]
    Output: 0
    Explanation: In this case, no transaction is done, i.e. max profit = 0.


    Constraints:

    1 <= prices.length <= 105
    0 <= prices[i] <= 105
*/

#include <iostream>
#include <vector>

using namespace std;

#define ll long long
#define mod 1000000007

int recursion(int i, int buy, int maxTransactions, int n, vector<int> &ar)
{
    if (i == n || maxTransactions == 0)
    {
        return 0;
    }
    if (buy)
    {
        return max(-ar[i] + recursion(i + 1, 0, maxTransactions, n, ar), recursion(i + 1, 1, maxTransactions, n, ar));
    }
    return max(ar[i] + recursion(i + 1, 1, maxTransactions - 1, n, ar), recursion(i + 1, 0, maxTransactions, n, ar));
}

int memoized(int i, int buy, int maxTransactions, int n, vector<int> &ar, vector<vector<vector<int>>> &dp)
{
    if (i == n || maxTransactions == 0)
    {
        return 0;
    }
    if (dp[i][buy][maxTransactions] != -1)
    {
        return dp[i][buy][maxTransactions];
    }
    if (buy)
    {
        return dp[i][buy][maxTransactions] = max(
                   -ar[i] + memoized(i + 1, 0, maxTransactions, n, ar, dp),
                   memoized(i + 1, 1, maxTransactions, n, ar, dp));
    }
    return dp[i][buy][maxTransactions] = max(
               ar[i] + memoized(i + 1, 1, maxTransactions - 1, n, ar, dp),
               memoized(i + 1, 0, maxTransactions, n, ar, dp));
}

int tabulation(vector<int> &ar, int n)
{
    vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(2, vector<int>(3, 0)));
    for (int i = n - 1; i >= 0; i++)
    {
        for (int buy = 0; buy < 2; buy++)
        {
            for (int maxTransaction = 1; maxTransaction <= 2; maxTransaction++)
            {
                if (buy)
                {
                    dp[i][buy][maxTransaction] = max(
                        -ar[i] + dp[i + 1][!buy][maxTransaction],
                        dp[i + 1][buy][maxTransaction]);
                }
                else
                {
                    dp[i][buy][maxTransaction] = max(
                        ar[i] + dp[i + 1][!buy][maxTransaction - 1],
                        dp[i + 1][buy][maxTransaction]);
                }
            }
        }
    }
    return dp[0][1][2];
}

int space_opt(vector<int> &ar, int n)
{
    vector<vector<int>> calculated(2, vector<int>(3, 0)), cur(2, vector<int>(3, 0));
    for (int i = n - 1; i >= 0; i--)
    {
        for (int buy = 0; buy < 2; buy++)
        {
            for (int maxTransaction = 1; maxTransaction <= 2; maxTransaction++)
            {
                if (buy)
                {
                    cur[buy][maxTransaction] = max(
                        -ar[i] + calculated[!buy][maxTransaction],
                        calculated[buy][maxTransaction]);
                }
                else
                {
                    cur[buy][maxTransaction] = max(
                        ar[i] + calculated[!buy][maxTransaction - 1],
                        calculated[buy][maxTransaction]);
                }
            }
        }
        calculated = cur;
    }
    return calculated[1][2];
}

int faster(vector<int> &ar)
{
    // SELL BEFORE BUY AGAIN
    //  BUY ON ith day with profit
    int buy1 = INT_MIN, buy2 = INT_MIN;
    int sell1 = 0, sell2 = 0;

    for (int p : ar)
    {
        buy1 = max(buy1, -p);
        sell1 = max(sell1, buy1 + p);
        buy2 = max(buy2, sell1 - p);
        sell2 = max(sell2, buy2 + p);
    }
    return sell2;
}

void solve()
{
}

int main()
{
    int n;
    cin >> n;
    solve();
    return 0;
}
