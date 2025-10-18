#include <bits/stdc++.h>
using namespace std;

struct node {
    char data;
    node* left;
    node* right;

    node(char val) {
        data = val;
        left = NULL;
        right = NULL;
    }
};

void deleteTree(node* root) {
    if (root == NULL) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

node* copyTree(node* root) {
    if (root == NULL) return NULL;
    node* n = new node(root->data);
    n->left = copyTree(root->left);
    n->right = copyTree(root->right);
    return n;
}

node* impl_free(node* root) {
    if (root == NULL) return NULL;
    root->left = impl_free(root->left);
    root->right = impl_free(root->right);

    if (root->data == '>') {
        node* a = root->left;
        node* b = root->right;
        delete root; // The old '>' node is now deleted.

        node* notA = new node('~');
        notA->right = a;
        node* orNode = new node('+');
        orNode->left = notA;
        orNode->right = b;
        return orNode;
    }
    return root;
}

node* nnf(node* root) {
    if (root == NULL) return NULL;

    if (root->data == '~') {
        node* c = root->right;

        // Rule: ~~A -> A
        if (c->data == '~') {
            node* grandChild = c->right;
            delete root; // delete outer ~
            delete c;    // delete inner ~
            return nnf(grandChild);
        }
        // Rule: ~(A + B) -> (~A * ~B)
        else if (c->data == '+') {
            node* a = c->left;
            node* b = c->right;
            delete root; // delete ~
            delete c;    // delete +

            node* andNode = new node('*');
            node* na = new node('~'); na->right = a;
            node* nb = new node('~'); nb->right = b;
            andNode->left = nnf(na);
            andNode->right = nnf(nb);
            return andNode;
        }
        // Rule: ~(A * B) -> (~A + ~B)
        else if (c->data == '*') {
            node* orNode = new node('+');
            node* a = c->left;
            node* b = c->right;
            delete root; // delete ~
            delete c;    // delete *
            
            node* na = new node('~'); na->right = a;
            node* nb = new node('~'); nb->right = b;
            orNode->left = nnf(na);
            orNode->right = nnf(nb);
            return orNode;
        } else return root;
    }

    root->left = nnf(root->left);
    root->right = nnf(root->right);
    return root;
}

node* cnf(node* root);


node* distr(node* A, node* B) {
    // Rule: (A1 * A2) + B -> (A1 + B) * (A2 + B)
    if (A->data == '*') {
        node* a1 = A->left;
        node* a2 = A->right;
        delete A; 

        node* new_left_or = new node('+');
        new_left_or->left = a1;
        new_left_or->right = copyTree(B); // B is used twice, so copy for the first use

        node* new_right_or = new node('+');
        new_right_or->left = a2;
        new_right_or->right = B;

        node* andNode = new node('*');
        andNode->left = cnf(new_left_or);
        andNode->right = cnf(new_right_or);
        return andNode;
    }
    // A + (B1 * B2) -> (A + B1) * (A + B2)
    if (B->data == '*') {
        node* b1 = B->left;
        node* b2 = B->right;
        delete B; 

        node* new_left_or = new node('+');
        new_left_or->left = copyTree(A); 
        new_left_or->right = b1;

        node* new_right_or = new node('+');
        new_right_or->left = A; 
        new_right_or->right = b2;
        
        node* andNode = new node('*');
        andNode->left = cnf(new_left_or);
        andNode->right = cnf(new_right_or);
        return andNode;
    }

    //  A + B (no distribution needed)
    node* orNode = new node('+');
    orNode->left = A;
    orNode->right = B;
    return orNode;
}

node* cnf(node* root) {
    if (root == NULL) return NULL;
    root->left = cnf(root->left);
    root->right = cnf(root->right);

    if (root->data == '+') {
        node* new_tree = distr(root->left, root->right);
        delete root; 
        return new_tree;
    }
    return root;
}

void collectClauses(node* root, vector<vector<string>>& clauses) {
    if (root == NULL) return;

    if (root->data == '*') {
        collectClauses(root->left, clauses);
        collectClauses(root->right, clauses);
    } else {
        vector<string> clause;
        queue<node*> q;
        q.push(root);

        while (!q.empty()) {
            node* cur = q.front(); q.pop();
            if (cur == NULL) continue;

            if (cur->data == '+') {
                q.push(cur->left);
                q.push(cur->right);
            } else if (cur->data == '~') {
                if (cur->right)
                    clause.push_back("~" + string(1, cur->right->data));
            } else {
                clause.push_back(string(1, cur->data));
            }
        }
        clauses.push_back(clause);
    }
}

vector<vector<string>> convertToCNF(node* root) {
    node* cnf_tree = copyTree(root);

    cnf_tree = impl_free(cnf_tree);
    cnf_tree = nnf(cnf_tree);
    cnf_tree = cnf(cnf_tree);

    vector<vector<string>> result;
    collectClauses(cnf_tree, result);

    deleteTree(cnf_tree);
    return result;
}