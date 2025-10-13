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

void getatoms(node *current,set<char> &atomset)
{   
   
    if(current==NULL)
        return;
    
    if(current->data != '*' && current->data != '+' && current->data != '>' && current->data != '~')
    {
        atomset.insert(current->data);
    }

    getatoms(current->left,atomset);
    getatoms(current->right,atomset);


}

bool bottomuptraversal(node* current, map<char,bool> &truthvalues) {
    if (current == nullptr)
        return false; // defensive guard

    // Base case — leaf node
    if (current->left == nullptr && current->right == nullptr)
        return truthvalues[current->data];

    // Unary operator (~)
    if (current->data == '~')
        return !bottomuptraversal(current->right, truthvalues);

    // Binary operators using switch
    bool left = bottomuptraversal(current->left, truthvalues);
    bool right = bottomuptraversal(current->right, truthvalues);

    switch (current->data) {
        case '*':
            return left && right; // AND
        case '+':
            return left || right; // OR
        case '>':
            return (!left) || right; // Implication
        default:
            return false; // fallback (invalid operator)
    }
}

void gettruthvalue(node *root)
{
     set<char> atomset;
     getatoms(root,atomset);//atomset has the actual atoms
     map<char,bool> truthvalues;
     for(char atom: atomset)
     {
        int val;
        cout << "Enter truth value for " << atom << " (0 or 1 ): ";
        cin >> val;
        truthvalues[atom]= (val==0)?false:true;//assigning the boolean values

     }//truthvalues has the truthvalues of the given atoms

     bool val=bottomuptraversal(root,truthvalues);
     cout<<"The value of the given expression is "<< val?"true":"false";
}

