/*
    You are given an integer array prices where prices[i] is the price of a stock in dollars on the ith day, 
    and an integer k.

    You are allowed to make at most k transactions, where each transaction can be either of the following:

    Normal transaction: Buy on day i, then sell on a later day j where i < j. You profit prices[j] - prices[i].

    Short selling transaction: Sell on day i, then buy back on a later day j where i < j.
    You profit prices[i] - prices[j].

    Note that you must complete each transaction before starting another. 
    Additionally, you can't buy or sell on the same day you are selling or buying back as part of a previous transaction.

    Return the maximum total profit you can earn by making at most k transactions.

    

    Example 1:

    Input: prices = [1,7,9,8,2], k = 2

    Output: 14

    Explanation:

    We can make $14 of profit through 2 transactions:
    A normal transaction: buy the stock on day 0 for $1 then sell it on day 2 for $9.
    A short selling transaction: sell the stock on day 3 for $8 then buy back on day 4 for $2.
    Example 2:

    Input: prices = [12,16,19,19,8,1,19,13,9], k = 3

    Output: 36

    Explanation:

    We can make $36 of profit through 3 transactions:
    A normal transaction: buy the stock on day 0 for $12 then sell it on day 2 for $19.
    A short selling transaction: sell the stock on day 3 for $19 then buy back on day 4 for $8.
    A normal transaction: buy the stock on day 5 for $1 then sell it on day 6 for $19.
    

    Constraints:

    2 <= prices.length <= 103
    1 <= prices[i] <= 109
    1 <= k <= prices.length / 2
*/

#include <iostream>
#include <vector>

using namespace std;

#define ll long long
#define mod 1000000007

int recursion(int idx, int buy, vector<int> &ar, int n){
    if(idx >= n){
        return 0;
    }
    if(buy){
        return max(
            -ar[idx] + recursion(idx+1, !buy, ar, n),
            recursion(idx+1, buy, ar, n)
        );
    }
    return max(
        ar[idx] + recursion(idx+1, !buy, ar, n),
        recursion(idx+1, buy, ar, n)
    );
}

int tabulation(vector<int> &ar, int n){
    vector<vector<int>> dp(n+1, vector<int> (2, 0));
    for(int i = n-1; i>=0; i++){
        for(int buy = 0; buy <= 1; buy++){
            if(buy){
                dp[i][buy] = max(
                    -ar[i] + dp[i+1][!buy],
                    dp[i+1][buy]
                );
            }
            else{
                dp[i][buy] = max(
                    ar[i] + (i < n-1) ? dp[i+2][!buy] : 0,
                    dp[i+1][buy]
                );
            }
        }
    }
    return dp[0][1];
}

int main() {
    int n;
    cin>>n;
    return 0;
}
