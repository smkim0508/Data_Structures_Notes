//9/12/22 Data Structures Notes

// More Operator Overloading
// In general, Operator/class overloading is customizing their preset functions to meet specific needs

//  for (int i=0; i<0; ++i) { //++i is same as i.operator++(), ++i is an L value while i++ is not

int ex_one() { //change to any arbitary type
    class X {     
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


// Overloading another operator that existed since back in C

int ex_two() {
    int a; // any type T can be subbed for int
    a.x; // x-field of object a

    int *pa = &a;

    pa -> x; // this is the same as (pa*).x //x-field of object pa
    *a.x // this is basically the same as *(a.x) since . has high operator precedence (2nd highest just below ::)
    // the line above finds the x field of a, which is hopefully a pointer (otherwise complier crashes), then dereferences the pointer value
}

// . has the second highest precedent (order of importance/priority) in c++ only after ::

// Smart Pointers

// X* operator -> () {...}

X* f() {
    X* px = new X[10000]; //reserves x 10000 objects in memory
    // arbitary code
    return px;
}
...
delete[]px;

// You CANNOT Overload:
// ,
// ::
// .
// ?: (a?b:c)

// You SHOULDN'T Overload:
// &&
// ||

// However, it is sometimes useful to overload points!

class Pt {
public:
    bool operator <(const Pt& pt) const{ //you can't have field ordering, but you can have a useful ordering
    if (x!=pt.x) {
        return y<pt.x;
    }
    return y<pt.y
    }
    vector<Pt> pts(10000);
    get_pts(pts);
    sort(pts.begin(), pts.end());
};

// Assignment #1 preview - Class applying modular arithmatic

Mod::set_modulus(17);

Mod a=5, b=13;
cout<<a+b<<'\n'; // displays 1 //<< is a bitshift

// you can overload << as well since it is a part of library

ostream& operator <<(const Mod& m); // change types in library

