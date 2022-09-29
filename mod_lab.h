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
    Mod(long t)
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
        x = m.x;

        return *this; 
    };
    Mod &operator-=(const Mod &m)
    {
        x -= m.x;
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
        // Mod temp(m);
        // x -= -m.x
        // overflow occurs when x = m.x = 2^31 - 1,
        *this -= (-m);
        return *this;
    };

    Mod &operator*=(const Mod &m)
    {
        Mod res(0);
        Mod b_n(m);
        Mod a_n(*this);
        // unsigned long b_n = b.val();
        // unsigned long a_n = a.val();

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
        if (m.val() == 0) {
            exit(-1);
        }
        x /= m.x;
        Mod temp(x);
        *this = temp;
        return *this;
    };

    Mod pwr(long e) const
    {
        Mod res(1);
        Mod exp(e);
        Mod a_n(*this);

        while (exp.val() > 0)
        {
            if (exp.val() % 2 == 1)
            {
                res *= (a_n);
            }

            a_n *= (a_n);
            exp = exp.val() / 2;
        }

        return res;
    };

    long val() const
    {
        return x;
    };

    static void set_modulus(long m)
    {
        if (m < 2) {
            exit(-1);
        }
        modulus = m;
    };
    static long get_modulus() { return modulus; }

private:
    long x;
    static long modulus;
    static long extended_euclidean(long a, long b, Mod *sol, Mod *y)
    {   
        // Base Case
        if (a == 0)
        {
            *sol = 0;
            *y = 1;
            return b;
        }

        // Store results of recursive call
        long gcd = extended_euclidean(b % a, a, sol, y);
        // Update x and y using results of
        // recursive call
        // *sol = y1 - (b / a) * sol1;
        Mod temp = *sol;
        *sol *= Mod(- (b / a));
        *sol += Mod(*y);

        *y = temp;

        return gcd;
        // **Use euclidean algorithm if runtime matters, if not bashing is safer
    }

    // find k such that k * r0 = 1 (mod modulus)
    static Mod inv(long r0){
        if (r0 == 0) {
            exit(-1);
        }
        Mod k(0);
        Mod temp(0);
        long gcd = extended_euclidean(r0, modulus, &k, &temp);

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

Mod operator-(long t, const Mod &m)
{
    Mod temp(t);
    return temp - m; // subtraction between mod objects alr defined
};

Mod operator+(const Mod &a, const Mod &b)
{
    Mod negative(-b.val());
    return a - negative;
};
Mod operator+(long t, const Mod &m)
{
    Mod temp(t);
    return temp + m;
};

Mod operator*(const Mod &a, const Mod &b)
{
    Mod res(0);
    Mod b_n(b);
    Mod a_n(a);
    // unsigned long b_n = b.val();
    // unsigned long a_n = a.val();

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
    // Mod temp(a.val() * b.val());
    // return temp;
};

Mod operator*(long t, const Mod &m)
{
    Mod temp(t);
    return temp * m;
};

Mod operator/(const Mod &a, const Mod &b)
{
    if (b.val() == 0) {
            exit(-1);
    }
    Mod temp(a.val() / b.val());
    return temp;
};
Mod operator/(long t, const Mod &m)
{
    if (m.val() == 0) {
        exit(-1);
    }
    Mod temp(t);
    return temp / m;
};
bool operator==(const Mod &a, const Mod &b)
{
    return a.val() == b.val();
};

bool operator==(long t, const Mod &m)
{
    Mod temp(t);
    return temp == m;
};
bool operator!=(const Mod &a, const Mod &b)
{
    return a.val() != b.val();
};
bool operator!=(long t, const Mod &m)
{
    Mod temp(t);
    return temp != m;
};

istream &operator>>(istream &is, Mod &m) {
    long a;
    is >> a;
    m = a;
    return is;
}; 

ostream &operator<<(ostream &os, const Mod &m)
{
    os << m.val() << " (mod " << Mod::get_modulus() << ")";
    return os;
};

// long Mod::modulus = 1000000000 - 1; // for test

#endif /* defined(____Mod__) */