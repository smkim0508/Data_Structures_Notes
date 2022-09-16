// 9/9/22 Day 4 Data Structures

int ***pppa; //int can be replaced with any type

//1. Heap Fragmentation (Triple pointers) - refer to notes on section 1 of 9/9 notes for diagram
//Shuffles pointer assignments to create more space to fill in memory
//Nothing is changed in the user's perspective

//2. Classes & Operator Overloading

// Adding explicit disallows the conversion of type 
// ex. When do we want explicit?
// template<class7,...> 
// class vector {
// public:
//     explicit vector(size.t n=0,...)
// }

// 
class Complex {
public:
        Complex(double x = 0.0, double y = 0.0) //A 1-argument constructor is an implicit conversion operation, we do not want to add explicit here
            : x(x), y(y)
        { }
        ~Complex() {} //Destructor 
        Complex& operator=(const Complex& z) { //overiding an operator
            x = z.x;
            y = z.y;
            return *this;
        }
        Complex operator+(const Complex& z) const {
            return Complex(x + z.x, y + z.y); //a new complex
         //never overload && and II, +, or = can't overload . : ; , ?;
         // a && b;
            //     a.operator&&(b);   
        }         
            
private:
    double x,yi;
};

