/*
    You are given a string s consisting of lowercase English letters.

    A substring is almost-palindromic if it becomes a palindrome after removing exactly one character from it.

    Return an integer denoting the length of the longest almost-palindromic substring in s.

    A substring is a contiguous non-empty sequence of characters within a string.

    A palindrome is a non-empty string that reads the same forward and backward.

    Example 1:
    Input: s = "abca"
    Output: 4
    Explanation:
    Choose the substring "abca".
    Remove "abca".
    The string becomes "aba", which is a palindrome.
    Therefore, "abca" is almost-palindromic.

    Example 2:
    Input: s = "abba"
    Output: 4
    Explanation:
    Choose the substring "abba".
    Remove "abba".
    The string becomes "aba", which is a palindrome.
    Therefore, "abba" is almost-palindromic.

    Example 3:
    Input: s = "zzabba"
    Output: 5
    Explanation:
    Choose the substring "zzabba".
    Remove "zabba".
    The string becomes "abba", which is a palindrome.
    Therefore, "zabba" is almost-palindromic.
    
    Constraints:
    2 <= s.length <= 2500
    s consists of only lowercase English letters.
*/

#include <iostream>
#include <vector>

using namespace std;

#define ll long long
#define mod 1000000007

class Solution {
public:
    int almostPalindromic(string s) {
        int n = s.size();
        vector<vector<bool>> dp(n, vector<bool>(n, false));

        // Precompute palindrome table
        for (int i = 0; i < n; i++)
            dp[i][i] = true;

        for (int len = 2; len <= n; len++) {
            for (int i = 0; i + len - 1 < n; i++) {
                int j = i + len - 1;
                if (s[i] == s[j]) {
                    if (len == 2)
                        dp[i][j] = true;
                    else
                        dp[i][j] = dp[i+1][j-1];
                }
            }
        }

        int ans = 0;

        // Check all substrings
        for (int l = 0; l < n; l++) {
            for (int r = l; r < n; r++) {

                if (r - l + 1 <= ans) continue;

                int i = l, j = r;
                bool removed = false;
                bool ok = true;

                while (i < j) {
                    if (s[i] == s[j]) {
                        i++; j--;
                    } else {
                        if (removed) {
                            ok = false;
                            break;
                        }
                        removed = true;

                        if (dp[i+1][j]) {
                            break;
                        }
                        if (dp[i][j-1]) {
                            break;
                        }

                        ok = false;
                        break;
                    }
                }

                if (ok) {
                    // must remove exactly one char
                    if (r - l + 1 >= 2)
                        ans = max(ans, r - l + 1);
                }
            }
        }

        return ans;
    }
};
