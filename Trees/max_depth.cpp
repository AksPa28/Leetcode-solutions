/*
    Find maximum depth of the binary tree.
    1
     \
      2
     /  \
    3    4
        /
       5 
       
    Max depth = 5
*/

#include <iostream>
#include <tree.h>
#include <queue>

using namespace std;

int maxDepth(TreeNode *root){
    if(!root){
        return 0;
    }
    int lHeight = maxDepth(root->left);
    int rHeight = maxDepth(root->right);
    return 1 + max(lHeight, rHeight);
}

int maxDepthIterative(TreeNode *root){
    if(!root){
        return 0;
    }
    queue<TreeNode*> q;
    int height = 0;
    q.push(root);
    while(!q.empty()){
        int sz = q.size();
        for(int i = 0; i<sz; i++){
            TreeNode *cur = q.front();
            q.pop();
            if(cur->left){
                q.push(cur->left);
            }
            if(cur->right){
                q.push(cur->right);
            }
        }
        height++;
    }
    return height;
}