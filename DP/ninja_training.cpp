/*
    There is a n * 3 array where each row represents different activities'
    (Activities: Running, Fighting, Learning new moves) merit points 
    Person can't do same activity consecutively. 
    Find maximum merits he can earn.

        Ex: [[1, 2, 5],
            [3, 1, 1],
            [3, 3, 3]]
        
        Max points = 3(2nd) + 3(3rd) + 5(1st) = 11
 */


#include<iostream>
#include<vector>

using namespace std;

// Tabulation approach
int solve2(vector<vector<int>>& ar, int n){
    vector<vector<int>> dp(n, vector<int> (4, 0));
    dp[0][0] = max(ar[0][1], ar[0][2]);
    dp[0][1] = max(ar[0][0], ar[0][2]);
    dp[0][2] = max(ar[0][0], ar[0][1]);
    dp[0][3] = max(dp[0][0], dp[0][1]);

    for(int day = 1; day<n; day++){
        for(int last_task_idx = 0; last_task_idx<4; last_task_idx++){
            dp[day][last_task_idx] = 0;
            for(int task = 0; task<3; task++){
                if(task != last_task_idx){
                    dp[day][last_task_idx] = max(dp[day][last_task_idx], ar[day][task] + dp[day-1][task]);
                }   
            }
        }
    }
    return dp[n-1][3];
}

// Space Optimization
int solve3(vector<vector<int>>& ar, int n){
    vector<int> prev(4, -1);
    prev[0] = max(ar[0][1], ar[0][2]);
    prev[1] = max(ar[0][0], ar[0][2]);
    prev[2] = max(ar[0][0], ar[0][1]);
    prev[3] = max(prev[0], prev[1]);
    for(int day = 1; day<n; day++){
        vector<int> temp(4, 0);

        for(int last_task_idx = 0; last_task_idx<4; last_task_idx++){
            temp[last_task_idx] = 0;

            for(int task = 0; task<3; task++){
                if(task != last_task_idx){
                    temp[last_task_idx] = max(temp[last_task_idx], ar[day][task] + prev[task]);
                }   
            }
        }
        prev = temp;
    }
    return prev[3];
}

// Recursion method wit memoization
int recur(vector<vector<int>> &ar, int idx, int last_task_index, vector<vector<int>>& dp){
    if(idx < 0) return 0;

    if(dp[idx][last_task_index] != -1)  return dp[idx][last_task_index];

    int mx = 0;
    for(int i = 0; i<3; i++){
        if(i != last_task_index){ 
            mx = max(ar[idx][i] + recur(ar, idx-1, i, dp), mx);
        }
    }
    return dp[idx][last_task_index] = mx;
}

int solve(vector<vector<int>>& ar, int n){
    vector<vector<int>> dp(n, vector<int> (4, -1));
    return recur(ar, n-1, 3, dp);
}

int main(){
    int n;
    cin >> n;
    vector<vector<int>> ar(n, vector<int>(3));
    for(int i = 0; i<n; i++){
        for(int j = 0; j<3; j++){
            cin >> ar[i][j];
        }
    }
    solve(ar, n);
    return 0;
}
