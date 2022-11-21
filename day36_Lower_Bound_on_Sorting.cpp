// 11/8/22 Data Structure Notes

// Lower Bound on Sorting

// if items can only be compared with a yes or no response (ex. is x < y?),
// then n items cannot be sorted in O(n*log(n)) time.
// Any sorting algorithm is a sequence of comparisons

// is a_i < a_j?
// yielding a sequence of yes/no responses.

// Construct a tree of possible paths. 

// Then, 2^(# of comps) = (# of leaf nodes) >= # of sequences = n!
// # of comps >= log(n!) = O(n*log(n))