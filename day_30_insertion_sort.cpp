// 10/27/22 Day 30 Data Structures Notes

// Insertion Sort

// Ex. begin with 3 1 4 1 5 9 2 6 5 (a.k.a. digits of pi)

// Move until reaching equality, then replace & stop. 
// 1 1 3 4 5 9 2 6 5

// -> 1_1 1_2 2 3 4 5_1 5_2 6 9

// This method is 'stable'
// Why is this important?
//      When performing various sorts, if any list is 'unstable,' it will often collapse (not always)

#include <vector>

template<class T>

void sort(std::vector<T> &a) {
    for (int i=1; i < a.size(); ++i) {
        j = i;
        T t = a[j];
        for (; j>0 & t<a[j-1]; --j) { // t<a[j-1] -> how many elements with j<i satisfy a[j] > a[i]? best case l_i = 0; worst case = i; average case = i/2
            a[j] = a[j-1];
        }
        a[j] = t;
    }

}

// The average running time ~ n^2/4 -> O(n^2)
// However, if inversions are local, insertion sort is O(n) no matter the number of elements

// New Topic
// Inversions

// Recall that an inversion in an array a is a pair (i, j) of indices s.t. i < j & a[i] > a[j]
// 0 <= # of inversions <= (n choose 2)
// a = [n-1, n-2, ... 2, 1, 0]

// A swap of adjacent elements changes # of inversions by +/- 1
// Any algorithm that only swaps adjacent elements has worst case O(n^2)

// Donald Shell: 
// Shellsort
// Fix d = jump size; 
// Use insertion sort on: 
// a[0], a[d], a[2d], ... 
// a[1], a[1+d], a[1+2d], ...
// a[d-1], a[2d-1], ...

// However, what if d was iterated?
// -> results in runtime of n * sqrt(n) or n(log(n))^2

// There were attempts to figure out the best, optimal jump size
// Never fully analyzed; very complicated runtime
