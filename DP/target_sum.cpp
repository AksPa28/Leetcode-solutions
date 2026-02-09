/**
    You are given an integer array nums and an integer target.

    You want to build an expression out of nums by adding
    one of the symbols '+' and '-' before each integer in nums and then concatenate all the integers.

    For example, if nums = [2, 1], you can add a '+' before 2 and
    a '-' before 1 and concatenate them to build the expression "+2-1".

    Return the number of different expressions that you can build, which evaluates to target.

    Example 1:
    Input: nums = [1,1,1,1,1], target = 3
    Output: 5
    Explanation: There are 5 ways to assign symbols to make the sum of nums be target 3.
    -1 + 1 + 1 + 1 + 1 = 3
    +1 - 1 + 1 + 1 + 1 = 3
    +1 + 1 - 1 + 1 + 1 = 3
    +1 + 1 + 1 - 1 + 1 = 3
    +1 + 1 + 1 + 1 - 1 = 3

    Example 2:
    Input: nums = [1], target = 1
    Output: 1

    Constraints:
    1 <= nums.length <= 20
    0 <= nums[i] <= 1000
    0 <= sum(nums[i]) <= 1000
    -1000 <= target <= 1000


    ---------------------------------------------------------------------------------------
    Same question as finding subsequences which have s1 - s2 = D, where s1 and s2 are sum of subsequences

    Logic:
        s1-s2 = D
        s1+s2 = total_sum
        s1 = (D+total_sum)/2

        Find subsequence with sum s1
 */

#include <iostream>
#include <vector>

using namespace std;

#define ll long long
#define mod 1000000007

int findWays(int n, vector<int> &ar, int subsetSum)
{
    vector<int> prev(n + 1, 0), cur(n + 1, 0);
    prev[0] = 1;
    if (ar[0] <= subsetSum)
        prev[ar[0]] = 1;
    for (int idx = 1; idx < n; idx++)
    {
        for (int sum = 0; sum <= subsetSum; sum++)
        {
            cur[sum] = prev[sum] + (ar[idx] <= sum ? 0 : prev[sum - ar[idx]]);
        }
        prev = cur;
    }
    return prev[subsetSum];
}

int findWays_space_opt(int n, vector<int> &ar, int subsetSum)
{
    vector<int> prev(n + 1, 0);
    prev[0] = 1;
    if (ar[0] <= subsetSum)
        prev[ar[0]] = 1;
    for (int idx = 1; idx < n; idx++)
    {
        for (int sum = subsetSum; sum >= 0; sum--)
        {
            prev[sum] = prev[sum] + (ar[idx] <= sum ? prev[sum - ar[idx]] : 0);
        }
    }
    return prev[subsetSum];
}

int main()
{
    int n;
    vector<int> ar(n);
    int target;
    int total = 0;
    for (int i = 0; i < n; i++)
    {
        total += ar[i];
    }
    if (total - target < 0 || total & 1 == 0)
        return -1;
    return findWays(n, ar, (total - target) / 2);
}
