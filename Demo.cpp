/**
 * Demo file for the exercise on binary tree
 *
 * @author Evgeny Hershkovitch Neiterman
 * @since 2023-03
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
using namespace std;

#include "sources/Fraction.hpp"

using namespace ariel;


// int main() {
    // Fraction a(5,3), b(14,21);
    // cout << "a: " << a << "b: " << b << endl;
    // cout << "a+b" << a+b << endl; 
    // cout << "a-b" << a-b << endl; 
    // cout << "a/b" << a/b << endl; 
    // cout << "a*b" << a*b << endl; 
    // cout << "2.3*b" << 2.3*b << endl; 
    // cout << "a+2.421" << a+2.421 << endl; 
    // Fraction c = a+b-1;
    // cout << c++ << endl;
    // cout << --c << endl;
    // cout << "c >=b ? : " << (c >= b) << endl;
    // if (a > 1.1) cout << " a is bigger than 1.1" << endl;
    // else cout << " a is smaller than 1.1" << endl;
    // int max_int = std::numeric_limits<int>::max();
    // int min_int = std::numeric_limits<int>::min();
    // Fraction f1(max_int, 1);
    // Fraction f4(max_int - 100, max_int);
    // cout << f1 * f4<<endl;
    // Fraction f1{2, 5};

    //     // Adding zero as a fraction
    // cout << (f1 + Fraction{0, 5}== f1)<<endl;

// }

int main(int argc, char const *argv[])
{
    int max_int = std::numeric_limits<int>::max();
    int min_int = std::numeric_limits<int>::min();
    Fraction f1(max_int, 1);
    Fraction f6(min_int, 1);
    cout << f1 - f6 << endl;
}
