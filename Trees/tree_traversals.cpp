#include<iostream>
#include<queue>
#include<stack>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Traversals{
    public:
        void preorder(TreeNode *root);
        void inorder(TreeNode *root);
        void postorder(TreeNode *root);
        void iterativePreorder(TreeNode *root);
        void iterativePostorder2Stack(TreeNode *root);
        void iterativePostorder1Stack(TreeNode *root);
        void iterativeInorder(TreeNode *root);
        void levelOrder(TreeNode *root);
};

void Traversals::preorder(TreeNode *root){
    if(!root){
        return;
    }
    cout<<root->val<<" ";
    preorder(root->left);
    preorder(root->right);
}

void Traversals::postorder(TreeNode *root){
    if(!root){
        return;
    }
    postorder(root->left);
    postorder(root->right);
    cout<<root->val<<" ";
}

void Traversals::inorder(TreeNode *root){
    if(!root){
        return;
    }
    inorder(root->left);
    cout<<root->val<<" ";
    inorder(root->right);
}

void Traversals::levelOrder(TreeNode *root){
    if(!root){
        return;
    }
    queue<TreeNode *> q;
    q.push(root);
    while(!q.empty()){
        int sz = q.size();
        for(int i = 0; i<sz; i++){
            TreeNode *cur = q.front();
            cout<<cur->val<<" ";
            q.pop();
            if(cur->left){
                q.push(cur->left);
            }
            if(cur->right){
                q.push(cur->right);
            }
        }
        cout<<endl;
    }
}

void Traversals::iterativePreorder(TreeNode *root){
    if(!root){
        return;
    }
    stack<TreeNode *> st;
    st.push(root);
    while(!st.empty()){
        TreeNode* cur = st.top();
        st.pop();
        cout<<cur->val<<" ";
        if(cur->right){
            st.push(cur->right);
        }
        if(cur->left){
            st.push(cur->left);
        }
    }
}

void Traversals::iterativePostorder2Stack(TreeNode *root){
    if(!root){
        return;
    }
    stack<TreeNode *> st1, st2;
    TreeNode *cur = root;
    st1.push(cur);
    while (!st1.empty()){
        cur = st1.top();
        st1.pop();
        st2.push(cur);
        if(cur->left){
            st1.push(cur->left);
        }
        if(cur->right){
            st1.push(cur->right);
        }
    }

    while(!st2.empty()){
        cur = st2.top();
        st2.pop();
        cout<<cur->val<<" ";
    }    
}

void Traversals::iterativePostorder1Stack(TreeNode *root){
    stack<TreeNode *> st;
    TreeNode *cur = root;
    while(cur || !st.empty()){
        if(cur){
            st.push(cur);
            cur = cur->left;
        }
        else{
            TreeNode *temp = st.top()->right;
            if(!temp){
                temp = st.top();
                st.pop();
                cout<<temp->val<<" ";
                while(!st.empty() && temp == st.top()->right){
                    temp = st.top();
                    st.pop();
                    cout<<temp->val<<" ";
                }
            }
            else{
                cur = temp;
            }
        }
    }
}

void Traversals::iterativeInorder(TreeNode *root){
    if(!root){
        return;
    }
    stack<TreeNode *> st;
    TreeNode *cur = root;
    while(true){
        if(cur){
            st.push(cur);
            cur = cur->left;
        }
        else{
            if(st.empty()){
                break;
            }
            cur = st.top();
            cout<<cur->val<<" ";
            st.pop();
            cur = cur->right;
        }
    }
}