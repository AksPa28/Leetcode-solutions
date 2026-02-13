/*
    Find out the top view of a Binary Tree

        2
       / \
      3   5
     / \
    6   4

    ans = [6, 3, 2, 5]
*/

#include<iostream>
#include<tree.h>
#include<queue>
#include<vector>
#include<map>

using namespace std;

vector<int> topView(TreeNode *root){
    queue<pair<TreeNode *, int>> q;
    map<int, int> mp;
    q.push({root, 0});
    while(!q.empty()){
        int sz = q.size();
        for(int i = 0; i<sz; i++){
            TreeNode *cur = q.front().first;
            int line = q.front().second;
            q.pop();
            if(cur->left){
                q.push({cur->left, line-1});
            }
            if(cur->right){
                q.push({cur->right, line+1});
            }
            if(mp.find(line) == mp.end()){
                mp[line] = cur->val;
            }
        }
    }
    vector<int> ans;
    for(auto it: mp){
        ans.push_back(it.second);
    }
    return ans;
}
