/*
    Given an input string (s) and a pattern (p), implement wildcard pattern matching with support for '?' and '*' where:

    '?' Matches any single character.
    '*' Matches any sequence of characters (including the empty sequence).
    The matching should cover the entire input string (not partial).

    Example 1:
    Input: s = "aa", p = "a"
    Output: false
    Explanation: "a" does not match the entire string "aa".

    Example 2:
    Input: s = "aa", p = "*"
    Output: true
    Explanation: '*' matches any sequence.

    Example 3:
    Input: s = "cb", p = "?a"
    Output: false
    Explanation: '?' matches 'c', but the second letter is 'a', which does not match 'b'.

    Constraints:
    0 <= s.length, p.length <= 2000
    s contains only lowercase English letters.
    p contains only lowercase English letters, '?' or '*'.
*/

#include <iostream>
#include <vector>

using namespace std;

#define ll long long
#define mod 1000000007

bool recursion(string &s1, int idx1, string &s2, int idx2)
{
    if (idx1 < 0)
        return idx2 < 0;
    if (idx2 < 0)
    {
        for (int i = 0; i < idx1; i++)
        {
            if (s1[i] != '*')
                return false;
        }
        return true;
    }
    if (s1[idx1] == s2[idx2] || s1[idx1] == '?')
        return recursion(s1, idx1 - 1, s2, idx2 - 1);
    if (s1[idx1] == '*')
    {
        return recursion(s1, idx1, s2, idx2 - 1) | recursion(s1, idx1 - 1, s2, idx2);
    }
    return false;
}

bool memoized(string &s1, int idx1, string &s2, int idx2, vector<vector<int>> &dp)
{
    if (idx1 < 0)
        return idx2 < 0;
    if (idx2 < 0)
    {
        for (int i = 0; i < idx1; i++)
        {
            if (s1[i] != '*')
                return false;
        }
        return true;
    }
    if (dp[idx1][idx2] != -1)
        return dp[idx1][idx2];
    if (s1[idx1] == s2[idx2] || s1[idx1] == '?')
        return dp[idx1][idx2] = memoized(s1, idx1 - 1, s2, idx2 - 1, dp);
    if (s1[idx1] == '*')
    {
        return dp[idx1][idx2] = memoized(s1, idx1, s2, idx2 - 1, dp) | memoized(s1, idx1 - 1, s2, idx2, dp);
    }
    return dp[idx1][idx2] = false;
}

bool tabulation(string &s1, string &s2)
{
    int n = s1.size(), m = s2.size();
    vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));
    dp[0][0] = true;
    for (int i = 1; i <= n; i++)
    {
        bool flag = true;
        for (int j = 1; j <= i; j++)
        {
            if (s1[j - 1] != '*')
            {
                flag = false;
                break;
            }
        }
        dp[i][0] = flag;
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (s1[i - 1] == s2[j - 1] || s1[i - 1] == '?')
                dp[i][j] = dp[i - 1][j - 1];
            else if (s1[i - 1] == '*')
            {
                dp[i][j] = dp[i - 1][j] | dp[i][j - 1];
            }
            else
                dp[i][j] = false;
        }
    }
    return dp[n][m];
}

bool space_opt(string &p, string &t)
{
    int m = t.size(), n = p.size();
    vector<bool> prev(m + 1), cur(m + 1);
    prev[0] = true;
    for (int i = 1; i <= n; i++)
    {
        bool flag = true;
        for (int k = 1; k <= i; k++)
        {
            if (p[k - 1] != '*')
            {
                flag = false;
                break;
            }
        }
        cur[0] = flag;

        for (int j = 1; j <= m; j++)
        {
            if (p[i - 1] == t[j - 1] || p[i - 1] == '?')
                cur[j] = prev[j - 1];
            else if (p[i - 1] == '*')
            {
                cur[j] = cur[j - 1] | prev[j];
            }
            else
                cur[j] = false;
        }
        prev = cur;
    }
    return prev[m];
}

int main()
{
    int n;
    return 0;
}
