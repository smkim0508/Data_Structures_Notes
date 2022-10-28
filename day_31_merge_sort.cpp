// 10/28/22 Day 31 Data Structures Notes

// Merge Sort, has O(n*log(n)) runtime

// Stable Sort

// Implementation: Topdown or Bottom-up

// Topdown -> Recursive: Split array into 2 halves, then sort each half and merge results.
// Bottom-up -> Sort pairs of 2 elements each, then merge repeatedly until final merge.

// Ex. begin with 3 1 4 1 5 9 2 6
// -> [3 1] [4 1] [5 9] [2 6]
// -> [1 3] [1 4] [5 9] [2 6]
// -> [1 3 1 4] [5 9 2 6] 
// -> [1 1 3 4] [2 5 6 9]
// -> [1 1 3 4 2 5 6 9]
// -> [1 1 2 3 4 5 6 9]
// -> 1 1 2 3 4 5 6 9

// Problem: Implement Merge Sort for Linked-List

template<class T>

mergeSort(Node<T>* head) {
    int sz = 0;
    Node<T>* curr = head;
    while(curr) {
        sz++;
        curr = curr->next;
    }
    auto head1 = head;
    head2 = head;
    for (int i=0; i< sz/2; i++) {
        head2 = head2-> next;
    }
    auto next = head2 -> next;
    head2.next = nullptr;
    mergeSort(head1);
    mergeSort(head2);
    return;
}