//9/12/22 Data Structures Notes

// More Operator Overloading
// In general, Operator/class overloading is customizing their preset functions to meet specific needs

int ex_one() { //change to any arbitary type
    for (int i=0; i<0; ++i) {
        class X {       //++i is same as i.operator++();
        public:
        // arbitary codes
            X& operator++() {
                return *this;
            }
            X operator++(int) {
                X x = *this;
                *this = *this + 1;
                return x;
            }
        };
    }
}

// Overloading another operator that existed since back in C

int ex_two() {
    int a; // any type T can be subbed for int
    a.x; // x-field of object a

    int *pa = &a;

    pa -> x; // this is the same as (pa*).x //x-field of object pa
    *a.x // this is basically the same as *(a.x) since . has high operator precedence (2nd highest just below ::)
    // the line above finds the x field of a, which is hopefully a pointer (otherwise complier crashes), then dereferences the pointer value
}

