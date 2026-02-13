/*
    Given the root of a binary tree, return the length of the diameter of the tree.

    The diameter of a binary tree is the length of the longest path between any two nodes in a tree. 
    This path may or may not pass through the root.

    The length of a path between two nodes is represented by the number of edges between them.

    Example 1:
    Input: root = [1,2,3,4,5]
    Output: 3
    Explanation: 3 is the length of the path [4,2,1,3] or [5,2,1,3].

    Example 2:
    Input: root = [1,2]
    Output: 1

    Constraints:
    The number of nodes in the tree is in the range [1, 104].
    -100 <= Node.val <= 100



    Approach:
    For a given node, find it's left and right height and then sum it and add 1 to it, now find the max value of this 
    across all tree nodes
*/

#include<tree.h>
#include<iostream>

using namespace std;

int findMaxHeight(TreeNode *root, int& diameter){
    if(!root){
        return 0;
    }
    int lh = findMaxHeight(root->left, diameter);
    int rh = findMaxHeight(root->right, diameter);
    diameter = max(diameter, lh+rh);
    return 1 + max(lh, rh);
}

int diameterOfBinaryTree(TreeNode *root){
    int diameter = 0;
    if(!root){
        return 0;
    }
    findMaxHeight(root, diameter);
    return diameter;
}