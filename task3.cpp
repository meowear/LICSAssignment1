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

void printInfix(nodeCNF* current) 
{
    if (current == nullptr) return;

    if (current->data == "*" || current->data == "+") 
    {
        cout << "(";
        printInfix(current->left);
        cout << current->data;
        printInfix(current->right);
        cout << ")";
    }

    else if (current->data == "~") 
    {
        cout << "~";
        printInfix(current->right);
    }

    else 
    {
        cout << current->data;
    }
}




