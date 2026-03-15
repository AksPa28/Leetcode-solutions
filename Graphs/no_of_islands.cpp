/*
Given an m x n 2D binary grid grid which represents a map of '1's (land) and '0's (water), return the number of islands.

An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically.
You may assume all four edges of the grid are all surrounded by water. 

Example 1:

Input: grid = [
  ["1","1","1","1","0"],
  ["1","1","0","1","0"],
  ["1","1","0","0","0"],
  ["0","0","0","0","0"]
]
Output: 1

Example 2:

Input: grid = [
  ["1","1","0","0","0"],
  ["1","1","0","0","0"],
  ["0","0","1","0","0"],
  ["0","0","0","1","1"]
]
Output: 3
 
Constraints:

m == grid.length
n == grid[i].length
1 <= m, n <= 300
grid[i][j] is '0' or '1'.
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
private:
    void dfs(vector<vector<char>>& grid, int r, int c, int m, int n){
        if(r >= m || c >= n || r < 0 || c < 0 || grid[r][c] == '0'){
            return;
        }
        grid[r][c] = '0';
        dfs(grid, r+1, c, m, n);
        dfs(grid, r-1, c, m, n);
        dfs(grid, r, c+1, m, n);
        dfs(grid, r, c-1, m, n);
    }
public:
    int numIslands(vector<vector<char>>& grid) {
        int totalIslands = 0;
        int m = grid.size(), n = grid[0].size();
        if(!m || !n){
            return totalIslands;
        }
        for(int i = 0; i<m; i++){
            for(int j = 0; j<n; j++){
                if(grid[i][j] == '1'){
                    totalIslands++;
                    dfs(grid, i, j, m, n);
                }
            }
        }
        return totalIslands;
    }
};
