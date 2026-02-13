/*
    Check if a tree is height balanced or Balanced Binary tree, where left height and right height's
    absolute difference is less than 1
    Example 1:
    Input: root = [3,9,20,null,null,15,7]
    Output: true

    Example 2:
    Input: root = [1,2,2,3,3,null,null,4,4]
    Output: false

    Example 3:
    Input: root = []
    Output: true
*/

#include<tree.h>
#include<iostream>

using namespace std;

int findHeight(TreeNode *root){
    if(!root){
        return 0;
    }
    int leftHt = findHeight(root->left);
    if(leftHt == -1){
        return -1;
    }
    int rightHt = findHeight(root->right);
    if(rightHt == -1){
        return -1;
    }
    if(abs(leftHt-rightHt) > 1){
        return -1;
    }
    return 1 + max(leftHt, rightHt);
}

bool checkBalanced(TreeNode *root){
    return findHeight(root) != -1;
}