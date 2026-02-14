/*
    Given the root of a binary tree, return the leftmost value in the last row of the tree.

    Example 1:
    Input: root = [2,1,3]
    Output: 1

    Example 2:
    Input: root = [1,2,3,4,null,5,6,null,null,7]
    Output: 7
    
    Constraints:

    The number of nodes in the tree is in the range [1, 104].
    -231 <= Node.val <= 231 - 1
*/

#include<iostream>
#include<tree.h>
#include<queue>

using namespace std;

void dfs(TreeNode* node, int depth, int& maxDepth, int& res) {
    if (!node) return;
    dfs(node->left, depth + 1, maxDepth, res);
    if (depth > maxDepth) {
        maxDepth = depth;
        res = node->val;
    }
    dfs(node->right, depth + 1, maxDepth, res);
}

int findBottomLeftValue(TreeNode* root) {
    int res = 0;
    int maxDepth = 0;

    dfs(root, 1, maxDepth, res);

    return res;
}

int findBottomLeftValueLevelOrder(TreeNode *root){
    queue<TreeNode *> q;
    TreeNode *leftmost;
    q.push(root);
    int a = 1;
    while(!q.empty()){
        int sz = q.size();
        for(int i = 0; i<sz; i++){
            TreeNode *cur = q.front();
            q.pop();
            if(i == 0){
                leftmost = cur;
            }
            if(cur->left){
                q.push(cur->left);
            }
            if(cur->right){
                q.push(cur->right);
            }
        }
    }
    return leftmost->val;
}