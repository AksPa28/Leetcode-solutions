/*
You are given an integer array nums, and an integer k.

Start with an initial value val = 1 and process nums from left to right. 
At each index i, you must choose exactly one of the following actions:

Multiply val by nums[i].
Divide val by nums[i].
Leave val unchanged.
After processing all elements, val is considered equal to k only if its final rational value exactly equals k.

Return the count of distinct sequences of choices that result in val == k.

Note: Division is rational (exact), not integer division. For example, 2 / 4 = 1 / 2.

Example 1:
Input: nums = [2,3,2], k = 6
Output: 2
Explanation:

The following 2 distinct sequences of choices result in val == k:

Sequence	Operation on nums[0]	    Operation on nums[1]	    Operation on nums[2]	    Final val
1	        Multiply: val = 1 * 2 = 2	Multiply: val = 2 * 3 = 6	Leave val unchanged	        6
2	        Leave val unchanged	        Multiply: val = 1 * 3 = 3	Multiply: val = 3 * 2 = 6	6

Example 2:
Input: nums = [4,6,3], k = 2
Output: 2
Explanation:

The following 2 distinct sequences of choices result in val == k:

Sequence	Operation on nums[0]	    Operation on nums[1]	        Operation on nums[2]	            Final val
1	        Multiply: val = 1 * 4 = 4	Divide: val = 4 / 6 = 2 / 3	    Multiply: val = (2 / 3) * 3 = 2	    2
2	        Leave val unchanged	        Multiply: val = 1 * 6 = 6	    Divide: val = 6 / 3 = 2	            2

Example 3:
Input: nums = [1,5], k = 1
Output: 3
Explanation:

The following 3 distinct sequences of choices result in val == k:

Sequence	Operation on nums[0]	    Operation on nums[1]	Final val
1	        Multiply: val = 1 * 1 = 1	Leave val unchanged	    1
2	        Divide: val = 1 / 1 = 1	    Leave val unchanged	    1
3	        Leave val unchanged	        Leave val unchanged	    1
 

Constraints:
1 <= nums.length <= 19
1 <= nums[i] <= 6
1 <= k <= 1015
*/

#include <iostream>
#include <vector>
#include<map>

using namespace std;

#define ll long long
#define mod 1000000007

class Solution {
public:
    map<tuple<int,int,int,int>, ll> dp;

    vector<array<int,3>> factors;
    array<int,3> target;

    // DFS
    ll dfs(int i, int e2, int e3, int e5) {
        if (i == factors.size()) {
            return (e2 == target[0] && e3 == target[1] && e5 == target[2]) ? 1LL : 0LL;
        }

        auto key = make_tuple(i, e2, e3, e5);
        if (dp.count(key)) return dp[key];

        ll ans = 0;

        // 1. Skip
        ans += dfs(i + 1, e2, e3, e5);

        // 2. Multiply
        ans += dfs(i + 1, e2 + factors[i][0], e3 + factors[i][1], e5 + factors[i][2]);

        // 3. Divide
        ans += dfs(i + 1, e2 - factors[i][0], e3 - factors[i][1], e5 - factors[i][2]);

        return dp[key] = ans;
    }

    // Factorize only into 2,3,5
    array<int,3> factorize(long long x) {
        array<int,3> res = {0,0,0};

        while (x % 2 == 0) {
            res[0]++;
            x /= 2;
        }
        while (x % 3 == 0) {
            res[1]++;
            x /= 3;
        }
        while (x % 5 == 0) {
            res[2]++;
            x /= 5;
        }

        // If leftover > 1 → contains prime > 5 → impossible
        if (x != 1) return {INT_MAX,INT_MAX,INT_MAX};

        return res;
    }

    int countSequences(vector<int>& nums, long long k) {

        dp.clear();
        factors.clear();

        // Factorize k
        target = factorize(k);

        // If k has prime > 5 → impossible immediately
        if (target[0] == INT_MAX) return 0;

        // Factorize nums
        for (int x : nums)
            factors.push_back(factorize(x));

        return (int)dfs(0, 0, 0, 0);
    }
};