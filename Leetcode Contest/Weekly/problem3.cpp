#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int minimumOR(vector<vector<int>>& grid) {
        int m = grid.size();
        int answer = 0;

        for (int bit = 16; bit >= 0; bit--) {

            bool possible = true;

            for (int i = 0; i < m; i++) {

                bool row_ok = false;

                for (int val : grid[i]) {
                    int candidate =  val | answer;
                    if (((candidate >> bit) & 1) == 0) {
                        row_ok = true;
                        break;
                    }
                }

                if (!row_ok) {
                    possible = false;
                    break;
                }
            }

            if (!possible) {
                answer |= (1 << bit);
            }
        }

        return answer;
    }

    bool ok(vector<int>& nums){
        return false;
    }
};