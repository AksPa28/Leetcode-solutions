/*
    Given the root of a binary tree, imagine yourself standing on the right side of it, 
    return the values of the nodes you can see ordered from top to bottom.

    Example 1:
    Input: root = [1,2,3,null,5,null,4]
    Output: [1,3,4]

    Example 2:
    Input: root = [1,2,3,4,null,null,null,5]
    Output: [1,3,4,5]

    Example 3:
    Input: root = [1,null,3]
    Output: [1,3]

    Example 4:
    Input: root = []
    Output: []

    Constraints:
    The number of nodes in the tree is in the range [0, 100].
    -100 <= Node.val <= 100
*/

#include<tree.h>
#include<iostream>
#include<vector>
#include<queue>
#include<map>

using namespace std;

vector<int> rightSideView(TreeNode* root){
    vector<int> ans;
    if(!root){
        return ans;
    }
    queue<TreeNode *> q;
    q.push(root);
    while(!q.empty()){
        int curSize = q.size();
        while(curSize--){
            TreeNode * cur = q.front();
            q.pop();
            if(cur->left){
                q.push(cur->left);
            }
            if(cur->right){
                q.push(cur->right);
            }
            if(!curSize){
                ans.push_back(cur->val);
            }
        }
    }
    return ans;
}

