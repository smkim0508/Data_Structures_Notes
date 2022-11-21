#include <iostream>
unsigned long long int catalan(int n);

struct Node
{
    Node(Node *l = nullptr, Node *r = nullptr) : l(l), r(r) {
    }

    ~Node()
    {
        delete l;
        delete r;
    }

    Node *l;
    Node *r;
    static bool catalanComputed;
};

bool Node::catalanComputed = false;

// printing method to visualize tree
void printBT(const std::string &prefix, const Node *node, bool isLeft) {
    if (node != nullptr) {
        std::cout << prefix;

        std::cout << (isLeft ? "l--" : "r--");

        // print the value of the node
        std::cout << "#" << std::endl;

        // enter the next tree level - left and right branch
        printBT(prefix + (isLeft ? ".  " : "   "), node->l, true);
        printBT(prefix + (isLeft ? ".  " : "   "), node->r, false);
    }
}

void printBT(const Node *node) { printBT("", node, false); }

//C_n = for i=0;i<n;i++ {save += C_i*C_(n-1-i)}

// int sum = 0;

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
    // compute all catalan numbers if not computed yet
    if(!Node::catalanComputed) {
        catalan(36);
        Node::catalanComputed = true;
    }

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
    // compute all catalan numbers if not computed yet
    if(!Node::catalanComputed) {
        catalan(36);
        Node::catalanComputed = true;
    }
    
    unsigned long sz = size(root);
    if (sz == 0 || sz == 1) {
        // std::cout << "test 0 or 1" << std::endl;
        return 0;
    }

    unsigned long left_sz = size(root->l);
    unsigned long right_sz = size(root->r);
    
    unsigned long long counter = 0;
    // std::cout << "test 2" << std::endl;
    for (int i=0;i<left_sz;i++) {
        // std::cout << "test loop " << i << std::endl;
        counter += memo[i]*memo[sz-1-i];
    }

    return counter + (index(root->l) * memo[right_sz] + index(root->r));
    
};
