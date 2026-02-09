/**
    You are given an integer array prices where prices[i] is the price of a given stock on the ith day, and an integer k.
    Find the maximum profit you can achieve.
    You may complete at most k transactions: i.e. you may buy at most k times and sell at most k times.

    Note: You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).

    Example 1:
    Input: k = 2, prices = [2,4,1]
    Output: 2
    Explanation: Buy on day 1 (price = 2) and sell on day 2 (price = 4), profit = 4-2 = 2.

    Example 2:
    Input: k = 2, prices = [3,2,6,5,0,3]
    Output: 7
    Explanation: Buy on day 2 (price = 2) and sell on day 3 (price = 6), profit = 6-2 = 4.
    Then buy on day 5 (price = 0) and sell on day 6 (price = 3), profit = 3-0 = 3.

    Constraints:
    1 <= k <= 100
    1 <= prices.length <= 1000
    0 <= prices[i] <= 1000


    Same as buy sell stocks III, there were 2 here there are k transactions at max
*/

#include <iostream>
#include <vector>

using namespace std;

#define ll long long
#define mod 1000000007

int recursion(int idx, int buy, int n, vector<int> &ar)
{
    return 0;
}

int space_opt(vector<int> &ar, int n, int maxTransactions)
{
    vector<vector<int>> calculated(2, vector<int>(maxTransactions + 1, 0)), cur(2, vector<int>(maxTransactions + 1, 0));
    for (int i = n - 1; i >= 0; i--)
    {
        for (int buy = 0; buy < 2; buy++)
        {
            for (int transactions = 1; transactions <= maxTransactions; transactions++)
            {
                if (buy)
                {
                    cur[buy][transactions] = max(
                        -ar[i] + calculated[!buy][transactions],
                        calculated[buy][transactions]);
                }
                else
                {
                    cur[buy][transactions] = max(
                        ar[i] + calculated[!buy][transactions - 1],
                        calculated[buy][transactions]);
                }
            }
        }
        calculated = cur;
    }
    return calculated[1][maxTransactions];
}

// Different Approach using transaction numbers
int diff_recursion(int idx, int tranNo, vector<int> &ar, int n, int k)
{
    if (idx == n || tranNo == 2 * k)
        return 0;
    if (tranNo & 1)
    {
        // Buy Allowed
        return max(
            -ar[idx] + diff_recursion(idx + 1, tranNo + 1, ar, n, k),
            diff_recursion(idx + 1, tranNo, ar, n, k));
    }
    return max(
        ar[idx] + diff_recursion(idx + 1, tranNo + 1, ar, n, k),
        diff_recursion(idx + 1, tranNo, ar, n, k));
}

int diff_memoized(int idx, int tranNo, vector<int> &ar, int n, int k, vector<vector<int>> &dp)
{
    if (idx == n || tranNo == 2 * k)
        return 0;
    if (dp[idx][tranNo] != -1)
    {
        return dp[idx][tranNo];
    }
    if (!(tranNo & 1))
    {
        // Buy Allowed
        return dp[idx][tranNo] = max(
                   -ar[idx] + diff_memoized(idx + 1, tranNo + 1, ar, n, k, dp),
                   diff_memoized(idx + 1, tranNo, ar, n, k, dp));
    }
    return dp[idx][tranNo] = max(
               ar[idx] + diff_memoized(idx + 1, tranNo + 1, ar, n, k, dp),
               diff_memoized(idx + 1, tranNo, ar, n, k, dp));
}

int diff_tabulation(vector<int> &ar, int n, int k)
{
    vector<vector<int>> dp(n + 1, vector<int>(2 * k + 1, 0));
    for (int i = n - 1; i >= 0; i--)
    {
        for (int tranNo = 2 * k - 1; tranNo >= 0; tranNo--)
        {
            if (!(tranNo & 1))
            {
                dp[i][tranNo] = max(
                    -ar[i] + dp[i + 1][tranNo + 1],
                    dp[i + 1][tranNo]);
            }
            else
            {
                dp[i][tranNo] = max(
                    ar[i] + dp[i + 1][tranNo + 1],
                    dp[i + 1][tranNo]);
            }
        }
    }
}

int diff_space_opt(vector<int> &ar, int n, int k)
{
    vector<int> calculated(2 * k + 1, 0), cur(2 * k + 1, 0);
    for (int i = n - 1; i >= 0; i--)
    {
        for (int tranNo = 2 * k - 1; tranNo >= 0; tranNo--)
        {
            if (!(tranNo & 1))
            {
                cur[tranNo] = max(
                    -ar[i] + calculated[tranNo + 1],
                    calculated[tranNo]);
            }
            else
            {
                cur[tranNo] = max(
                    ar[i] + calculated[tranNo + 1],
                    calculated[tranNo]);
            }
        }
        calculated = cur;
    }
    return calculated[0];
}

int main()
{
    int n;
    cin >> n;
    return 0;
}
