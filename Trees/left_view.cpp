/*

*/

#include <iostream>
#include<tree.h>
#include<vector>
#include<queue>

using namespace std;

vector<int> leftSideView(TreeNode *root){
    queue<TreeNode *> q;
    q.push(root);
    while(!q.empty()){
        int sz = q.size();
        for(int i = 0; i<sz; i++){
            TreeNode *cur = q.front();
        }
    }
}
