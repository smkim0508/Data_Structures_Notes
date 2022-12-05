#include <iostream>
#include <vector>
#include <climits>

typedef std::vector<int> VI;
typedef std::vector<long long> VL;

std::vector<VL> n_hanoi; // 1st index = twr, 2nd = disks
std::vector<VI> k_hanoi;

// Initialize n_hanoi and k_hanoi
// f(k, n) = min 2 * f(k, i) + f(k-1, n-i)
// where k = # of pegs, n = # of disks
void hanoi_init() {
    
    for (int k = 0; k <= 10; k ++) {
        n_hanoi.push_back(VL(10001, -1));
        k_hanoi.push_back(VI(10001, -1));
    }
    
    // handling base case where k = 3
    long long a = 1;
    int i = 1;

    while (true) {
        n_hanoi[3][i] = a;
        k_hanoi[3][i] = i - 1;
        if(a >= 2 * a + 1) break;
        a = 2 * a + 1;
        i++;
    }

    // recursive case
    for (int k = 4; k <= 10; k++) {
        n_hanoi[k][1] = 1;
        for (int n = 2; n <= 10000; n++) {
            // temp.push_back(f(k, n))
            if (n_hanoi[k][n-1] == -1) break; // break when illegal case arises
            
            long long min_save = LONG_LONG_MAX;
            long long min_index = 0;

            // find minimum number of moves
            for (int i = 1; i < n; i++) {
                // case where n_hanoi[k-1][n-i] == -1
                if(n_hanoi[k-1][n-i] == -1) continue;

                // case where overflow occurs while computing 2 * n_hanoi[k][i] + n_hanoi[k-1][n-i] 
                if (n_hanoi[k][i] > 2 * n_hanoi[k][i] + n_hanoi[k-1][n-i] || n_hanoi[k-1][n-i] > 2 * n_hanoi[k][i] + n_hanoi[k-1][n-i]) {
                    continue;
                }
                
                if (min_save > 2 * n_hanoi[k][i] + n_hanoi[k-1][n-i]) {
                    min_save = 2 * n_hanoi[k][i] + n_hanoi[k-1][n-i];
                    min_index = i;
                }
            }

            n_hanoi[k][n] = min_save;
            k_hanoi[k][n] = min_index; 
        }
    }
};

// Fill moves so that each element is a two-integer VI describing the move
// You may assume that, initially, aux[] = {0, 1, 2, ..., n_twrs - 1}
void hanoi(std::vector<VI>& moves, int n_twrs, int n_dsks, VI& aux) {
    
    // base case
    // case i) n_dsks = 1
    if(n_dsks == 1) {
        moves.push_back({aux[0], aux[1]});
        // cout << "move from peg " << aux[0] + 1 << " to peg " << aux[1] + 1 << endl;
        return;
    }
    
    // case ii) n_twrs = 2
    // moves.push_back({aux[0], aux[1]});

    // recursive case
  
    // desired: aux = [0, n_twrs - 1, ..., n_twrs - 2]
    int temp = aux[n_twrs - 1];
    aux.pop_back(); // erase the last element aux = [0, 1, 2, ..., n_twr - 2]
    aux.insert(aux.begin() + 1, temp);
    int i = k_hanoi[n_twrs][n_dsks];
    hanoi(moves, n_twrs, i, aux);
    
    // desired: aux = [0, 1, 2..., n_twrs - 2] (n_twrs - 1 is removed)
    aux.erase(aux.begin() + 1);
    hanoi(moves, n_twrs - 1, n_dsks - i, aux);

    // desired: aux = [n_twrs - 1, 1, 0, 2,...., n_twrs-2]
    aux.insert(aux.begin(), temp); // result = [n_twrs-1, 0, 1, 2, .... n_twrs-2]
    temp = aux[1];
    aux[1] = aux[2];
    aux[2] = temp; // result = [n_twrs-1, 1, 0, 2,..., n_twrs-2]
    hanoi(moves, n_twrs, i, aux);

    temp = aux[0];
    aux.erase(aux.begin());
    aux.push_back(temp);
    temp = aux[0];
    aux[0] = aux[1];
    aux[1] = temp;

};
