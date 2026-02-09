/*
    Given two strings word1 and word2, return the minimum number of operations required to convert word1 to word2.

    You have the following three operations permitted on a word:

    Insert a character
    Delete a character
    Replace a character


    Example 1:

    Input: word1 = "horse", word2 = "ros"
    Output: 3
    Explanation:
    horse -> rorse (replace 'h' with 'r')
    rorse -> rose (remove 'r')
    rose -> ros (remove 'e')
    Example 2:

    Input: word1 = "intention", word2 = "execution"
    Output: 5
    Explanation:
    intention -> inention (remove 't')
    inention -> enention (replace 'i' with 'e')
    enention -> exention (replace 'n' with 'x')
    exention -> exection (replace 'n' with 'c')
    exection -> execution (insert 'u')


    Constraints:

    0 <= word1.length, word2.length <= 500
    word1 and word2 consist of lowercase English letters.


    prev _ _ _ _ _
    cur  _ _
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define ll long long
#define mod 1000000007

static int ans;

int recursion(string &s1, int n, string &s2, int m)
{
    if (n == 0)
        return m;
    if (m == 0)
        return n;
    if (s1[n - 1] == s2[m - 1])
        return recursion(s1, n - 1, s2, m - 1);

    return min(
        1 + recursion(s1, n - 1, s2, m - 1),
        min(
            1 + recursion(s1, n, s2, m - 1),
            1 + recursion(s1, n - 1, s2, m)));
}

int memoized(string &s1, int n, string &s2, int m, vector<vector<int>> &dp)
{
    if (n == 0)
        return m;
    if (m == 0)
        return n;
    if (dp[n][m] != -1)
        return dp[n][m];
    if (s1[n - 1] == s2[m - 1])
        return dp[n][m] = memoized(s1, n - 1, s2, m - 1, dp);

    return dp[n][m] = min(
               1 + memoized(s1, n - 1, s2, m - 1, dp),
               min(
                   1 + memoized(s1, n, s2, m - 1, dp),
                   1 + memoized(s1, n - 1, s2, m, dp)));
}

int tabulation(string &s1, string &s2)
{
    int n = s1.size(), m = s2.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 1e6));
    for (int i = 0; i <= n; i++)
        dp[i][0] = i;
    for (int j = 0; j <= m; j++)
        dp[0][j] = j;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (s1[i - 1] == s2[j - 1])
                dp[i][j] = dp[i - 1][j - 1];
            else
            {
                dp[i][j] = 1 + min(dp[i - 1][j], min(dp[i - 1][j - 1], dp[i][j - 1]));
            }
        }
    }
    return dp[n][m];
}

int space_opt(string &s1, string &s2)
{
    int n = s1.size(), m = s2.size();
    vector<int> prev(m + 1, 1e6);
    for (int i = 0; i <= m; i++)
        prev[i] = i;
    for (int i = 1; i <= n; i++)
    {
        int prev_first = prev[0];
        prev[0] = i;
        for (int j = 1; j <= m; j++)
        {
            int temp = prev[j];
            if (s1[i - 1] == s2[j - 1])
                prev[j] = prev_first;
            else
            {
                prev[j] = 1 + min(
                                  prev[j],
                                  min(prev[j - 1], prev_first));
            }
            prev_first = temp;
        }
    }
    return prev[m];
}

void helper(string &word1, string &word2, int i, int j, int pi, int pj, int steps)
{
    if (steps > ans)
        return;
    if (j == word2.size() || i == word1.size())
    {
        steps += max(word2.size() - pj, word1.size() - pi);
        ans = min(ans, steps);
        return;
    }
    if (word1[i] == word2[j])
    {
        helper(word1, word2, i + 1, j + 1, i + 1, j + 1, steps + max(i - pi, j - pj));
        return;
    }
    helper(word1, word2, i + 1, j + 1, pi, pj, steps);
    int ci = i + 1;
    int cj = j + 1;
    while (ci < word1.size() && word1[ci] != word2[j])
        ci++;
    while (cj < word2.size() && word1[i] != word2[cj])
        cj++;
    helper(word1, word2, ci, j, pi, pj, steps);
    helper(word1, word2, i, cj, pi, pj, steps);
}

int main()
{
    // word1 = "intention", word2 = "execution"
    string s1 = "intention", s2 = "execution";
    int n = s1.size(), m = s2.size();
    recursion(s1, n, s2, m);
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));
    memoized(s1, n, s2, m, dp);
    tabulation(s1, s2);
    ans = max(s1.size(), s2.size());
    helper(s1, s2, 0, 0, 0, 0, 0);
    return 0;
}
