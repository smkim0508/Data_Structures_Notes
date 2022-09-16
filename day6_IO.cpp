// 9/13/22 Data Structures Notes

// Input Output in C++

#include <iostream>

int x = 17; 
cout <<x<< '\n'//cout is an object of type ostream

class ostream {
public:
    //arbitary code
private:
    ostream(); //idiom to prevent copying an obj
    ostream& operator<<(int)
    ostream& operator<<(double)
};

Mod x=15, y=13; // So, how do we make this work?
(cout<<x)<<' ')<<y<<'\n') 

class Mod {
    Friend ostream& operator<<(ostream& o, const Mod&m);
private:
    long x;
    // do NOT write: ostream& operator<<(const Mod& m)
    //               m.operator<<(m?)
    // these should be inside ostream
};

// Instead, close out class first and outside of class Mod, write:

ostream& operator<<(ostream& os, const Mod& m) {
    return os<<m.x; // alternatively, os<<m.to_string(); if using string to_string() const; above
}

// Another cool example!

#include<iomanip>
// iostream was already included from above

const double PI = acos(-1.0);
    #include <cstdio>
    //arbitary code
    printf("%16f", PI); //prints 16 decimals

    cout<< std::set_precision(16)<<PI //changes the state of cout that governs how many decimal places are outputted

// Integers and Mod

// int type is not really the same as a numerical sense of integers
// The acceptable values of int type variables are: -2^(31) <= x <= 2^31-1

// For class Mod: all reasonable operations return mathematically correct results if:
// 0<= x <= 2^(63) - 1

// you must NEVER overflow, which will cause the value to "loop around" back to 0

// Division

// Most test cases in assignments will be as follows:

// evaluate a^b (mod p) where a,b,p are BIG (~2^(63)) and p is prime

// solve ax = b: ax+py = b
// GCD(a,p) = 1 -> (p is prime)

// solve: ax + py = 1
// given that GCD(a,b) = d, find x,y such that ax + by = d
// we know such set x,y exists due to Bezout's theorem

//---------------------------------------------

// So, how to solve the question from before:

// Use Euclidean Algorithm 

// We first assume a,b > 0:

long gcd(long a, long b) {
    if (b==0) return a;
    return gcd(b,a%b);
}

// Extended Euclidean Algorithm
// Denote a,b by a_0, a
// a_2 = a_0%a_1,
// a_0 = q_2a_1 + a_2, and
// 0 <= a_2 < a_1 // Division Algorithm

// a_2 = a_0 - q_2 * a
// a_3 = a_1 - q_3 * a_2 = a_1 - q_3(a_0 - q_2 * a_1)

// a_3 = (1 + q_2 * q_3)a_1 - (q_3)*a_0
// a_n = GCD == q_0 * X + a_1 * y


