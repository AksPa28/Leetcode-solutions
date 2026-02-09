/*
    You are given an integer array prices where prices[i] is the price of a given stock on the ith day.

    On each day, you may decide to buy and/or sell the stock.
    You can only hold at most one share of the stock at any time.
    However, you can sell and buy the stock multiple times on the same day,
    ensuring you never hold more than one share of the stock.

    Find and return the maximum profit you can achieve.

    Example 1:
    Input: prices = [7,1,5,3,6,4]
    Output: 7
    Explanation: Buy on day 2 (price = 1) and sell on day 3 (price = 5), profit = 5-1 = 4.
    Then buy on day 4 (price = 3) and sell on day 5 (price = 6), profit = 6-3 = 3.
    Total profit is 4 + 3 = 7.

    Example 2:
    Input: prices = [1,2,3,4,5]
    Output: 4
    Explanation: Buy on day 1 (price = 1) and sell on day 5 (price = 5), profit = 5-1 = 4.
    Total profit is 4.

    Example 3:
    Input: prices = [7,6,4,3,1]
    Output: 0
    Explanation: There is no way to make a positive profit, so we never buy the stock to achieve the maximum profit of 0.

    Constraints:

    1 <= prices.length <= 3 * 104
    0 <= prices[i] <= 104
*/

#include <iostream>
#include <vector>

using namespace std;

#define ll long long
#define mod 1000000007

int recursion(int idx, int buyAllow, vector<int> &ar, int n)
{
    if (idx == n)
        return 0;
    if (buyAllow)
    {
        return max(
            -ar[idx] + recursion(idx + 1, 0, ar, n),
            recursion(idx + 1, 1, ar, n));
    }
    else
    {
        return max(
            ar[idx] + recursion(idx + 1, 1, ar, n),
            recursion(idx + 1, 0, ar, n));
    }
}

int memoized(int idx, int buyAllow, vector<int> &ar, int n, vector<vector<int>> &dp)
{
    if (idx == n)
        return 0;
    if (dp[idx][buyAllow] != -1)
        return dp[idx][buyAllow];
    if (buyAllow)
    {
        return dp[idx][buyAllow] = max(-ar[idx] + memoized(idx + 1, 0, ar, n, dp), memoized(idx + 1, 1, ar, n, dp));
    }
    else
    {
        return dp[idx][buyAllow] = max(ar[idx] + memoized(idx + 1, 1, ar, n, dp), memoized(idx + 1, 0, ar, n, dp));
    }
}

int tabulation(vector<int> &ar, int n)
{
    vector<vector<int>> dp(n + 1, vector<int>(2, 0));
    for (int i = n - 1; i >= 0; i--)
    {
        for (int buy = 0; buy < 2; buy++)
        {
            if (buy)
            {
                dp[i][buy] = max(-ar[i + 1] + dp[i + 1][0], dp[i + 1][1]);
            }
            else
            {
                dp[i][buy] = max(ar[i + 1] + dp[i + 1][1], dp[i + 1][0]);
            }
        }
    }
    return dp[0][1];
}

int space_opt(vector<int> &ar, int n)
{
    vector<int> alreadyCalc(2, 0), cur(2, 0);
    for (int i = n - 1; i >= 0; i--)
    {
        for (int buy = 0; buy < 2; buy++)
        {
            if (buy)
            {
                cur[buy] = max(-ar[i] + alreadyCalc[0], alreadyCalc[1]);
            }
            else
            {
                cur[buy] = max(ar[i] + alreadyCalc[1], alreadyCalc[0]);
            }
        }
        alreadyCalc = cur;
    }
    return alreadyCalc[1];
}

int main()
{
    int n;
    cin >> n;
    return 0;
}
