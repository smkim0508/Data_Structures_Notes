// Do now for 10/20/22

// A sailor begins from the top most parent of a binary tree and jumps from node to node until returning to the starting point.

struct Node {
    string name;
    Node *l, *n
};

string itinerary(Node * home);

// Goal is to print the order of all the nodes that you visit

// skeleton code
struct Node {
    private: string itinerary(Node*n, string s) {
        St = n -> name;
        if (n-> l) {
            s = itinerary(n->l,s);
            s+= n-> name;
        }
        if (n-> r) {
            s = itinerary(n->r,s);
            s+= n-> name;
        }
        return s;
    }
}

