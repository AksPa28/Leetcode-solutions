/*
    Return the bottom view of Binary Tree, if two elements are at the same place use the rightmost one
*/
#include<tree.h>
#include<iostream>
#include<queue>
#include<map>

using namespace std;

vector<int> bottomView(TreeNode *root){
    queue<pair<int, TreeNode *>> q;
    map<int, int> lastSeenVerticalElement;
    vector<int> ans;
    q.push(make_pair(0, root));
    if(!root){
        return ans;
    }
    while(!q.empty()){
        TreeNode *cur = q.front().second;
        int verticalPos = q.front().first;
        lastSeenVerticalElement[verticalPos] = cur->val;
        q.pop();
        if(cur->left){
            q.push({verticalPos - 1, root->left});
        }
        if(cur->right){
            q.push({verticalPos + 1, root->right});
        }
    }
    for(auto &it: lastSeenVerticalElement){
        ans.push_back(it.second);
    }
    return ans;
}