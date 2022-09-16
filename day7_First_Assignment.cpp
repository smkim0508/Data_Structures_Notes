// 9/15/22 Data Structures Notes

// First Assignment!

# ifndef name
# define name 

// code

# endif
// This makes sure that each header is included just once

using std::istream; //std is like the "last name" and istream is like the "first name"

// using namespace std; // never use this anywhere besides coding competition
// This pollutes all namespaces

using VD = vector<double>; // type def vecotr<double> VD; // this used to be the past syntex

Mod(long t) // Mod x = 5, y = -1;
    // copy constructor
    // =
    // +=
    // -=
    // *=
    // /=
    // - // unary
    // pwr (long e)
    long val()

    // one of the MAIN objectives is to prevent overflowing

    static void set_modulus(long m);
    static long get_modulus();

private:
    static Mod mv(long r0); // The GCD stuff
    
    Mod operator+(long t, const Mod& a) // We need this, otherwise there are some problems relating to int/Mod conversions
    // Otherwise, a+2 -> a.operator(2) works since 2 is auto conversted from mod(2) to int(2)
    // But 2+a -> 2.operator(a) would NOT work since the compiler has no idea what to do here

    Mod operator +(const Mod&a, const Mod&b) { // These are placed outside class because of int to mod conversion constructor
        Mod t = a;
        t += b;
        return t;
    }

class Mod {
public:
    bool operator==(const Mod& a) const {
        return x== a.x;
    }
    // arbitary code
}; // semicolon only after class in c++ unlike Java

// OR

class Mod {
public:
    bool Mod::operator==(const Mod& a) const{ //here, we sepcify Mod::operator to signify which class the operator is from since we are no longer within the class
        return x==a.x;
    }
};

friend operator<<(ostream&os, const Mod& x);

// To solve large computations like 90000000^(6000001) (mod 9000000000018)
// Utilize the property of computing exponents through simplification
// Ex. x^1048576 = x^2^20 = x^(2^20) 



 

   



