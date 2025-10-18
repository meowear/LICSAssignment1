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
        return false;

    if (current->left == nullptr && current->right == nullptr)
        return truthvalues[current->data];

    if (current->data == '~')
        return !bottomuptraversal(current->right, truthvalues);

    bool left = bottomuptraversal(current->left, truthvalues);
    bool right = bottomuptraversal(current->right, truthvalues);

    switch (current->data) {
        case '*':
            return left && right;
        case '+':
            return left || right;
        case '>':
            return (!left) || right;
        default:
            return false;
    }
}

void gettruthvalue(node *root)
{
     set<char> atomset;
     getatoms(root,atomset);
     map<char,bool> truthvalues;

     vector<char> atoms(atomset.begin(), atomset.end());
     int n = atoms.size();
     cout << "Truth table:\n";
     for(char a: atoms) cout << a << " ";
     cout << "| Result\n";
     cout << string(2*n + 9, '-') << "\n";

     for(int i=0;i<(1<<n);i++)
     {
         for(int j=0;j<n;j++)
         {
             bool val = i & (1<< (n-j-1));
             truthvalues[atoms[j]] = val;
             cout << val << " ";
         }
         bool val = bottomuptraversal(root, truthvalues);
         cout << "| " << val << "\n";
     }
}

void collectLeafNodes(nodeCNF* current, unordered_set<string>& leaves) 
{
    if (current == NULL) return;

    if (current->left == NULL && current->right == NULL) {
        leaves.insert(current->data);
        return;
    }

    collectLeafNodes(current->left, leaves);
    collectLeafNodes(current->right, leaves);
}

bool evaluateCNF(nodeCNF* current,unordered_map<string,bool> &truthMap) 
{
    if (current == NULL) return true;

    if (current->left == NULL && current->right == NULL)
        return truthMap.at(current->data);

    if (current->data == "~")
        return !evaluateCNF(current->right,truthMap);

    if (current->data == "*")
        return evaluateCNF(current->left,truthMap) && evaluateCNF(current->right,truthMap);

    if (current->data == "+")
        return evaluateCNF(current->left,truthMap) || evaluateCNF(current->right,truthMap);
    
    return false;
}

void gettruthvalue_cnf(nodeCNF* root) 
{
    unordered_set<string> leaves;
    collectLeafNodes(root, leaves);

    vector<string> atoms(leaves.begin(), leaves.end());
    int n = atoms.size();

    cout << "Truth table:\n";
    for (auto &a: atoms) cout << a << " ";
    cout << "| Result\n";
    cout << string(2*n + 9, '-') << "\n";

    for(int i=0;i<(1<<n);i++)
    {
        unordered_map<string,bool> truthMap;
        for(int j=0;j<n;j++)
        {
            bool val = i & (1 << (n-j-1));
            truthMap[atoms[j]] = val;
            cout << val << " ";
        }
        bool val = evaluateCNF(root, truthMap);
        cout << "| " << val << "\n";
    }
}

int main() {
    // Build CNF parse tree
    nodeCNF* neg34 = new nodeCNF("~");
    neg34->right = new nodeCNF("34");

    nodeCNF* clause1 = new nodeCNF("+");
    clause1->left = neg34;
    clause1->right = new nodeCNF("79");

    nodeCNF* neg166 = new nodeCNF("~");
    neg166->right = new nodeCNF("166");

    nodeCNF* clause2 = new nodeCNF("+");
    clause2->left = new nodeCNF("45");
    clause2->right = neg166;

    nodeCNF* root = new nodeCNF("*");
    root->left = clause1;
    root->right = clause2;

    gettruthvalue_cnf(root);
    
    return 0;
}
