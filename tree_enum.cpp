#include <iostream>

using namespace std;

struct Node
{
    Node(Node *l = nullptr, Node *r = nullptr) : l(l), r(r) {}

    ~Node()
    {
        delete l;
        delete r;
    }

    Node *l;
    Node *r;
};

// printing method to visualize tree
void printBT(const string &prefix, const Node *node, bool isLeft) {
    if (node != nullptr) {
        cout << prefix;

        cout << (isLeft ? "l--" : "r--");

        // print the value of the node
        cout << "#" << endl;

        // enter the next tree level - left and right branch
        printBT(prefix + (isLeft ? ".  " : "   "), node->l, true);
        printBT(prefix + (isLeft ? ".  " : "   "), node->r, false);
    }
}

void printBT(const Node *node) { printBT("", node, false); }

//C_n = for i=0;i<n;i++ {save += C_i*C_(n-1-i)}

int sum = 0;

unsigned long long int memo[37]; 
// assume 0 <= n < 37
unsigned long long int catalan(int n) {
    memo[0] = 1;
    memo[1] = 1;
    // compute memo[i]
    for (int i = 2; i <= n; i++) { // loop to determine n Catalan numbers
        memo[i] = 0;
        for (int k = 0; k < i; k++) { // determines the ith Catalan number
            memo[i] += memo[k] * memo[i-1-k];
        }
    }
}

Node *tree(int sz, unsigned long long idx) {
    // base case
    if(sz == 0) {
        return nullptr;
    }
    
    Node *root = new Node();
    if(sz == 1) {
        return root;
    }

    unsigned long long int counter = 0;
    int j=0;
    for (;j<sz;j++) {
        if (counter + memo[j] * memo [sz-1-j] > idx) { // or counter + ... >= idx - 1
            break;
        }
        counter += memo[j] * memo [sz-1-j];
    }

    // finding left and right indexes through quotient and remainder
    unsigned long long int q = (idx - counter)/memo[sz-1-j]; 
    unsigned long long int r = (idx - counter) % memo[sz-1-j];

    root->l = tree(j, q);
    root->r = tree(sz-1-j , r);
    return root;
};

unsigned long size(const Node *root) {
    // base case : root == nullptr
    if (root == nullptr) { 
        return 0;
    }

    if (root->l == nullptr && root->r == nullptr) {
        return 1;
    }

    return size(root->l) + size(root->r) + 1;
}

unsigned long long index(const Node *root) {
    unsigned long sz = size(root);
    if (sz == 0 || sz == 1) {
        // cout << "test 0 or 1" << endl;
        return 0;
    }

    unsigned long left_sz = size(root->l);
    unsigned long right_sz = size(root->r);
    
    unsigned long long counter = 0;
    // cout << "test 2" << endl;
    for (int i=0;i<left_sz;i++) {
        // cout << "test loop " << i << endl;
        counter += memo[i]*memo[sz-1-i];
    }

    return counter + (index(root->l) * memo[right_sz] + index(root->r));
    
};

// test output
int main() {
    catalan(36); // compute all catalan numbers and save to memo[]
    //    #
    //  #   # 
    Node root;
    Node left_node;
    Node right_node;

    root.l = &left_node;
    root.r = &right_node;

    int sz = 36;
    cout << sizeof(long long int) << endl;  
    cout << index(tree(sz, 11959798385860453491)) << endl; // largest possible index output
    cout << memo[36] << endl;
    
    // for (int i = 0; i < memo[sz]; i++) {
    //     cout << index(tree(sz, i)) << endl;
    // }
    // printBT(&root);
}