#include <bits/stdc++.h>
using namespace std;

struct node{
    char data;
    node*left;
    node*right;

    node(char val)
    {
        data=val;
        left=NULL;
        right=NULL;
    }
};

struct nodeCNF {
    string data;   
    nodeCNF* left;
    nodeCNF* right;

    nodeCNF(string val) 
    {
        
        data=val;
        left=NULL;
        right=NULL;
    } 
};

int heightChar(node* root) {
    if (root == NULL)
        return 0;

    int leftheight = heightChar(root->left);
    int rightheight = heightChar(root->right);

    return 1 + max(leftheight, rightheight);
}

// Height of CNF parse tree
int heightCNF(nodeCNF* root) {
    if (root == NULL)
        return 0;

    int leftheight = heightCNF(root->left);
    int rightheight = heightCNF(root->right);

    return 1 + max(leftheight, rightheight);
}