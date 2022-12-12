#include <iostream>

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

//that returns true with probability that is exactly a/b. Your routine can only access randomness by calling
//bool good_flip()
//whose calls are independent and return true with probability 0.5. The expected running time of your
//routine should be independent of the magnitude of a and b.
