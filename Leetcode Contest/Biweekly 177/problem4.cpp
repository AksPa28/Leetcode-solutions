#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    static const long long MOD = 1e9 + 7;

    long long modPow(long long base, long long exp) {
        long long result = 1;
        base %= MOD;

        while (exp > 0) {
            if (exp & 1)
                result = (result * base) % MOD;
            base = (base * base) % MOD;
            exp >>= 1;
        }

        return result;
    }

    int sumOfNumbers(int l, int r, int k) {
        long long m = r - l + 1;
        long long S = (1LL * (l + r) * m / 2) % MOD;

        long long part1 = modPow(m, k - 1);
        long long part2 = modPow(10, k);

        long long geometric = (part2 - 1 + MOD) % MOD;
        geometric = (geometric * 111111112) % MOD;  // inverse of 9

        long long ans = part1;
        ans = (ans * S) % MOD;
        ans = (ans * geometric) % MOD;

        return (int)ans;
    }
};