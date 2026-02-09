/*
    Given two strings text1 and text2, return the length of their longest common subsequence.
    If there is no common subsequence, return 0.

    A subsequence of a string is a new string generated from the original string with some
    characters (can be none) deleted without changing the relative order of the remaining characters.

    For example, "ace" is a subsequence of "abcde".
    A common subsequence of two strings is a subsequence that is common to both strings.

    Example 1:
    Input: text1 = "abcde", text2 = "ace"
    Output: 3
    Explanation: The longest common subsequence is "ace" and its length is 3.

    Example 2:
    Input: text1 = "abc", text2 = "abc"
    Output: 3
    Explanation: The longest common subsequence is "abc" and its length is 3.

    Example 3:
    Input: text1 = "abc", text2 = "def"
    Output: 0
    Explanation: There is no such common subsequence, so the result is 0.


    Constraints:
    1 <= text1.length, text2.length <= 1000
    text1 and text2 consist of only lowercase English characters.
*/

#include <iostream>
#include <vector>

using namespace std;

#define ll long long
#define mod 1000000007

int recursion(string &s1, int idx1, string &s2, int idx2)
{
    if (idx1 < 1 || idx2 < 1)
        return 0;
    if (s1[idx1 - 1] == s2[idx2 - 1])
        return 1 + recursion(s1, idx1 - 1, s2, idx2 - 1);
    return max(recursion(s1, s1[idx1 - 1], s2, s2[idx2]), recursion(s1, s1[idx1], s2, s2[idx2 - 1]));
}

int memoized(string &s1, int idx1, string &s2, int idx2, vector<vector<int>> &dp)
{
    if (idx1 < 1 || idx2 < 1)
        return 0;
    if (dp[idx1][idx2] != -1)
        return dp[idx1][idx2];
    if (s1[idx1 - 1] == s2[idx2 - 1])
        return dp[idx1][idx2] = 1 + memoized(s1, idx1 - 1, s2, idx2 - 1, dp);
    return dp[idx1][idx2] = max(memoized(s1, s1[idx1 - 1], s2, s2[idx2], dp), memoized(s1, s1[idx1], s2, s2[idx2 - 1], dp));
}

int tabulation(string &s1, string &s2)
{
    int n = s1.size(), m = s2.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));
    for (int i = 0; i <= n; i++)
        dp[i][0] = 0;
    for (int j = 0; j <= m; j++)
        dp[0][j] = 0;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            (s1[i - 1] == s2[j - 1]) ? dp[i][j] = 1 + dp[i - 1][j - 1] : dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }
    return dp[n][m];
}

int space_opt(string &s1, string &s2)
{
    int n = s1.size(), m = s2.size();
    vector<int> prev(m + 1, 0), cur(m + 1, 0);

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            (s1[i - 1] == s2[j - 1]) ? cur[j] = 1 + prev[j - 1] : max(prev[j], cur[j - 1]);
        }
        prev = cur;
    }
    return prev[m];
}

int main()
{
    string s1, s2;
    int n = s1.size(), m = s2.size();
    recursion(s1, n, s2, m);
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));
    memoized(s1, n, s2, m, dp);
    tabulation(s1, s2);
    space_opt(s1, s2);
    return 0;
}
