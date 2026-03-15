#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int minCost(int n) {
        return (int)(n*(n-1))/2;
    }
};