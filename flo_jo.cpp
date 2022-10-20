#include <vector>
// using namespace std;

template <class T>
struct Link {
    explicit Link(const T &info, Link *next = 0) : info(info), next(next) {}
    // This avoids stack overflow
    ~Link() {
        Link *p = next;
        while (p) {
            Link *q = p->next;
            p->next = 0;
            delete p;
            p = q;
        }
    }
    T info;
    Link *next;
};

template <typename T>
std::vector<int> loopTail(Link<T> *head) {
    
    // (1) determine existence of loop
    std::vector<int> res;
    if (head == nullptr) {
        res.push_back(0);
        res.push_back(0);
        return res;
    }
    Link<T>* slow = head;
    Link<T>* fast = head;
    int loop = 0;
    int loop_length = 0;
    if (fast->next != nullptr) {
        fast = fast->next;
        while (fast != nullptr && fast->next != nullptr) {
            if (slow == fast) {
                loop = 1;
                break;
            }
            fast = fast->next;
            fast = fast->next;
            slow = slow->next;
        }
    } else {
        loop = 0;
    }
    
    // (2) get length of loop
    if (loop == 0) {
        res.push_back(0);
    } else {
        fast = fast->next;
        loop_length++;
        while (fast != slow) {
            fast = fast->next;
            loop_length++;
        }
        res.push_back(loop_length);
    } 

    // (3) find length of tail
    Link<T>* first = head;
    Link<T>* second = head;
    int tail_length = 0;
    for (int i=0; i<loop_length; i++) {
        first = first->next;
    }
    if (loop_length == 0) { // case where there is no loop
        while (first != nullptr) {
            tail_length++;
            first = first->next;
        }
    }
    else { // if there is a loop
        while (first != second) {
        first = first->next;
        second = second->next;
        tail_length++;
        }
    }
    cout << "test 4" << endl;
    res.push_back(tail_length);
    return res;
};

// n = # of nodes
// k = step size
std::vector<int> josephus(int n, int k) {
    std::vector<int> v; 

    Link<int> **nodes = new Link<int>*[n];
    for (int i=n-1; i>=0; i--) {
        if (i == n - 1) {   
            nodes[i] = new Link<int>(i + 1, nullptr); 
        } 
        else {
            nodes[i] = new Link<int>(i + 1, nodes[i+1]);
        }
    }
    nodes[n-1]->next = nodes[0];
    
    int length = n;
    int counter = 1;
    int del = 0;
    Link<int> *prev = nodes[n-2];
    Link<int> *curr = nodes[n-1];
    Link<int> *nex = nodes[0];

    while(length > 0) {
        curr = nex;
        nex = nex->next;
        if (del == 0) {
            prev = prev->next;
        }
        del = 0;
        if ((counter)%k == 0) {
            prev->next = nex;
            v.push_back(curr->info);
            curr->next = nullptr;
            delete curr;
            length--;
            del = 1;
        }
        counter++;
    }
    return v;
};