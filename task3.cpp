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

void inordertraversal(node *current)
{
    if(current==NULL)
        return;

     if(current->data == '*' || current->data == '+' || current->data == '>')
    {
        cout << "(";                       
        inordertraversal(current->left);   
        cout << current->data;             
        inordertraversal(current->right);  
        cout << ")";                       
    }

    else if(current->data == '~') 
    {
        cout << "~";
        inordertraversal(current->right); 
    }

    else
    {
        cout<< current->data;
    }
}



