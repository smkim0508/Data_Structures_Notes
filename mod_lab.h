/* Due: September 29, 2022
Assignment: Implement the following class. Make sure that it handles all signed 8-byte integers correctly and without overflow.
For now, if the user attempts to divide by zero or set the modulus to something < 2, you can just "fail fast" with exit(-1). */
#ifndef ____Mod__ #define ____Mod__
#include <iostream> #include <cassert>
using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::ostream;

class Mod
{
public:
    Mod(long long t)
    {
        x = t % modulus;

        if (x < 0)
        {
            x += modulus;
        }
    };

    Mod(const Mod &m)
    {
        x = m.x;

        if (x < 0)
        {
            x += modulus;
        }
    };

    Mod &operator=(const Mod &m)
    {
        // this->x = m.x;
        x = m.x; // x = m.val();

        return *this; 
    };
    Mod &operator-=(const Mod &m)
    {
        x -= m.x; // x -= m.val();
        if (x < 0)
        {
            x += modulus;
        }
        return *this;
    };

    Mod operator-() const
    {
        Mod temp(-x);
        return temp;
    };

    Mod &operator+=(const Mod &m)
    {
        *this -= (-m);
        return *this;
    };

    Mod &operator*=(const Mod &m)
    {
        Mod res(0);
        Mod b_n(m);
        Mod a_n(*this);

        while (b_n.val() > 0)
        {
            if (b_n.val() % 2 == 1)
            {
                res += (a_n);
            }

            a_n += a_n;
            b_n = b_n.val() / 2;
        }

        *this = res;

        return *this;
    };

    Mod &operator/=(const Mod &m) {
        *this *= inv(m.val());
        return *this;
    };

    Mod pwr(long long e) const
    {
        Mod res(1);
        Mod a_n(*this);

        // if (e == 0) { // no need since while loop is bypassed if e == 0
            // return res; 
        // }

        if (e < 0) {
            return inv(a_n.val()).pwr(-e);
        }

        while (e > 0)
        {
            if (e % 2 == 1)
            {
                res *= (a_n);
                e -= 1; // not required since e/2 below drops decimal
            }

            a_n *= (a_n);
            e = e/2;
        }

        return res;
    };

    long long val() const
    {
        return x;
    };

    static void set_modulus(long long m)
    {
        modulus = m;
    };
    static long long get_modulus() { return modulus; }

private:
    long long x;
    static long long modulus;

    static long long extended_euclidean(long long a, long long b, Mod *sol, Mod *y)
    {   
        // Base Case
        if (a == 0)
        {
            *sol = 0;
            *y = 1;
            return b;
        }

        // Store results of recursive call
        long long gcd = extended_euclidean(b % a, a, sol, y);
        // Update using results of recursive call
        // *sol = y1 - (b / a) * sol1;
        Mod temp = *sol;
        *sol *= Mod(- (b / a));
        *sol += Mod(*y);

        *y = temp;

        return gcd;
        // Use euclidean algorithm if runtime matters, if not bashing is safer
    }

    static Mod inv(long long r0){
        Mod k(0);
        Mod temp(0);
        long long gcd = extended_euclidean(r0, modulus, &k, &temp);

        if (gcd == 1) {
            return Mod(k);
            
        } else {
            exit(-1);
        }
    };
};

Mod operator-(const Mod &a, const Mod &b)
{
    Mod temp(a.val() - b.val());
    return temp;
};

Mod operator-(long long t, const Mod &m)
{
    Mod temp(t);
    return temp - m; // already defined subtraction between mod objects
};

Mod operator+(const Mod &a, const Mod &b)
{
    Mod negative(-b.val());
    return a - negative;
};
Mod operator+(long long t, const Mod &m)
{
    Mod temp(t);
    return temp + m;
};

Mod operator*(const Mod &a, const Mod &b)
{
    Mod res(0);
    Mod b_n(b);
    Mod a_n(a);

    while (b_n.val() > 0)
    {
        // cout << a_n.val() << b_n.val() << endl;
        if (b_n.val() % 2 == 1)
        {
            res = (res + a_n);
        }

        a_n += a_n;
        b_n = b_n.val() / 2;
    }

    return res;
};

Mod operator*(long long t, const Mod &m)
{
    Mod temp(t);
    return temp * m;
};

Mod operator/(const Mod &a, const Mod &b)
{
    Mod temp(a.val());
    temp /= b;
    return temp;
};
Mod operator/(long long t, const Mod &m)
{
    Mod temp(t);
    return temp / m;
};
bool operator==(const Mod &a, const Mod &b)
{
    return a.val() == b.val();
};

bool operator==(long long t, const Mod &m)
{
    Mod temp(t);
    return temp == m;
};
bool operator!=(const Mod &a, const Mod &b)
{
    return a.val() != b.val();
};
bool operator!=(long long t, const Mod &m)
{
    Mod temp(t);
    return temp != m;
};

istream &operator>>(istream &is, Mod &m) {
    long long a;
    is >> a;
    m = Mod(a);
    return is;
}; 

ostream &operator<<(ostream &os, const Mod &m)
{
    os << m.val() << " (mod " << Mod::get_modulus() << ")" << endl;
    return os;
};

long long Mod::modulus = 1000000000 - 1;

#endif /* defined(____Mod__) */