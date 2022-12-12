#include <iostream>
#include <random>
#include <cmath>

using namespace std;

double p = 0.1;

bool bad_flip() {
    random_device rd;
    mt19937 gen(rd());
    // give "true" 1/4 of the time
    // give "false" 3/4 of the time
    bernoulli_distribution d(p);

    return d(gen) == 1;
}

//(a) Write a function
bool repair() {
    bool first_save;
    bool second_save;

    while (true){
        first_save = bad_flip();
        second_save = bad_flip();

        if (first_save != second_save) {
            break;
        }
    }
    return first_save;
}

//that returns true with probability 0.5 and whose calls are independent of each other. Your routine can only access randomness by calling
//bool bad_flip()
//whose call s are also independent, but returns true with some unknown but fixed probability p.

bool good_flip() {
    random_device rd;
    mt19937 gen(rd());
    bernoulli_distribution d(0.5); // returns true 50% of the time

    return d(gen) == 1;
}

//(b) Write a function
bool flip(unsigned long long a, unsigned long long b) {
    int counter = 1;

    while (true) {
        if (good_flip()) {
            break;
        }
        counter ++;
    }

    unsigned long long numerator = a;
    int binary;

    for (int i=0; i<counter; i++) {

        if (numerator > (b+1)/2) {
            binary = 1;
        }

        else {
            binary = 0;
        }
        
        unsigned long long temp_sum = numerator;

        numerator -= binary * b;
        numerator += temp_sum;

    }

    return binary == 1;
}

bool flip_dependent(unsigned long long a, unsigned long long b) {
    int n = ceil(log2(b));

    while (true) {
        int gen = 0;

        for (int i=0; i<n; i++) {
            gen *= 2;

            int temp;
            if (good_flip()) {
                temp = 1;
            }
            else {
                temp = 0;
            }
            gen += temp;
        }

        if (gen < a) {
            return true;
        }

        else if (gen < b) {
            return false;
        }
    }

}

//that returns true with probability that is exactly a/b. Your routine can only access randomness by calling
//bool good_flip()
//whose calls are independent and return true with probability 0.5. The expected running time of your
//routine should be independent of the magnitude of a and b.

int main() {
    int counter = 0;
    
    // for (int k=1; k<10; k++) {
    //     counter = 0;
    //     p = k/(double)10;
    //     for (int i=0; i<10000; i++) {
    //         if (repair()) {
    //             counter++;
    //         }
    //     }
    //     cout << counter/(double)10000 << endl;
    // }

    for (int i=0; i<100000; i++) {
            if (flip(17, 922)) {
                counter++;
            }
    }
    cout << counter/(double)100000 << endl;
}