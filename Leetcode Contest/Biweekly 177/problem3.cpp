#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> makeParityAlternating(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) {
            return {0, 0};
        }

        long long original_min = nums[0];
        long long original_max = nums[0];

        for (int i = 1; i < n; i++) {
            original_min = min(original_min, (long long)nums[i]);
            original_max = max(original_max, (long long)nums[i]);
        }

        int totalMin = 0;
        int totalMax = 0;

        for (int i = 0; i < n; i++) {
            if (nums[i] == original_min) totalMin++;
            if (nums[i] == original_max) totalMax++;
        }

        int mismatchEvenStart = 0;
        int mismatchOddStart = 0;

        // Count mismatches
        for (int i = 0; i < n; i++) {
            int parity = (nums[i] % 2 + 2) % 2;

            int expectedEven = (i % 2 == 0) ? 0 : 1;
            if (parity != expectedEven)
                mismatchEvenStart++;

            int expectedOdd = (i % 2 == 0) ? 1 : 0;
            if (parity != expectedOdd)
                mismatchOddStart++;
        }

        int minOps = min(mismatchEvenStart, mismatchOddStart);

        // Special case: all equal
        if (original_min == original_max) {
            if (minOps == 0)
                return {0, 0};
            if (minOps == n)
                return {minOps, 2};
            return {minOps, 1};
        }

        long long bestRange = LLONG_MAX;

        for (int pattern = 0; pattern < 2; pattern++) {

            int mismatchCount = (pattern == 0) ? mismatchEvenStart : mismatchOddStart;
            if (mismatchCount != minOps)
                continue;

            int minFlip = 0;
            int maxFlip = 0;

            for (int i = 0; i < n; i++) {

                int parity = (nums[i] % 2 + 2) % 2;
                int expected;

                if (pattern == 0)
                    expected = (i % 2 == 0) ? 0 : 1;
                else
                    expected = (i % 2 == 0) ? 1 : 0;

                if (parity != expected) {
                    if (nums[i] == original_min)
                        minFlip++;
                    if (nums[i] == original_max)
                        maxFlip++;
                }
            }

            long long newMin = original_min;
            long long newMax = original_max;

            if (minFlip == totalMin)
                newMin = original_min + 1;

            if (maxFlip == totalMax)
                newMax = original_max - 1;

            bestRange = min(bestRange, newMax - newMin);
        }

        return {minOps, (int)bestRange};
    }
};