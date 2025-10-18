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

node * buildParseTreeChar(string prefix, int &index) {
    if (index >= prefix.size())
        return NULL;

    char c = prefix[index];
    index++;

    node* current = new node(c);

    if (c == '~') {               // unary operator
        current->right = buildParseTreeChar(prefix, index);
    } else if (c == '*' || c == '+' || c == '>') { // binary operators
        current->left = buildParseTreeChar(prefix, index);
        current->right = buildParseTreeChar(prefix, index);
    }

    return current;
}

nodeCNF* buildCNFParseTree(vector<vector<int>>& v, int index) 
{
    if (v.empty() || index < 0)
         return NULL;

    vector<int> &clause = v[index];
    nodeCNF* clauseNode = NULL;

    if (!clause.empty()) {
        // first literal
        int lit = clause[0];
        nodeCNF* litNode = NULL;

        if (lit < 0) {                    // ~ node
            litNode = new nodeCNF(to_string(-lit));
            nodeCNF* neg = new nodeCNF("~");
            neg->right = litNode;
            litNode = neg;
        } else {
            litNode = new nodeCNF(to_string(lit));
        }

        nodeCNF* current = litNode;

        // rest of clause ORed
        for (int j = 1; j < clause.size(); j++) {
            int lit2 = clause[j];
            nodeCNF* nextLit = NULL;
            if (lit2 < 0) {
                nextLit = new nodeCNF(to_string(-lit2));
                nodeCNF* neg = new nodeCNF("~");
                neg->right = nextLit;
                nextLit = neg;
            } else {
                nextLit = new nodeCNF(to_string(lit2));
            }

            nodeCNF* or_node = new nodeCNF("+");
            or_node->left = current;
            or_node->right = nextLit;
            current = or_node;
        }

        clauseNode = current;
    }

    if (index - 1 >= 0) {   // recurse backwards
        nodeCNF* restTree = buildCNFParseTree(v, index - 1);
        nodeCNF* andNode = new nodeCNF("*");
        andNode->left = restTree;       
        andNode->right = clauseNode;    
        return andNode;
    } else {
        return clauseNode;              // first clause becomes leaf
    }
}

int main() {

    vector<vector<int>> v= {{1, -2}, {3}, {-4,5}};
    nodeCNF* cnfRoot = buildCNFParseTree(v, v.size() - 1);

    string prefix = "*+a~bc";
    int i=0;
    node* strRoot = buildParseTreeChar(prefix, i);
    
    return 0;
}