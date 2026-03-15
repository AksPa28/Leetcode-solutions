#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>

using namespace std;

class Solution {
public:
    long long countAtLeastK(vector<int>& nums, int K, int m) {
        unordered_map<int,int> freq;
        long long result = 0;
        int left = 0;
        int distinct = 0;
        int good = 0;

        for (int right = 0; right < nums.size(); right++) {

            freq[nums[right]]++;

            if (freq[nums[right]] == 1)
                distinct++;

            if (freq[nums[right]] == m)
                good++;

            while (distinct >= K && good == distinct) {

                result += (nums.size() - right);

                if (freq[nums[left]] == m)
                    good--;

                freq[nums[left]]--;

                if (freq[nums[left]] == 0)
                    distinct--;

                left++;
            }
        }

        return result;
    }

    long long countSubarrays(vector<int>& nums, int k, int m) {
        return countAtLeastK(nums, k, m) 
             - countAtLeastK(nums, k + 1, m);
    }
};