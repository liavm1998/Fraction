#include "Fraction.hpp"
#include <math.h>
#include <numeric>
#include <functional>
using namespace std;

namespace ariel{


    //constructors
    Fraction::Fraction():numerator(0),denominator(1){}
    Fraction::Fraction(int _numerator,int _denominator):numerator(_numerator),denominator(_denominator){
        if(this->denominator == 0){
            throw invalid_argument("");
        }
        this->reduced_form();
    };
    Fraction::Fraction(float f):numerator(round(f*=1000)),denominator(1000){
        this->reduced_form();
    };

    // help functions 
    void check_overflow(const Fraction& frac1, const Fraction& frac2, char operation) {
    if (operation == '+') {
        if ((frac1.numerator > 0 && frac2.numerator > 0 && frac1.numerator > std::numeric_limits<int>::max() - frac2.numerator) ||
            (frac1.numerator < 0 && frac2.numerator < 0 && frac1.numerator < std::numeric_limits<int>::min() - frac2.numerator)) {
            throw std::overflow_error("Integer overflow in addition.");
        }
    }
    else if (operation == '-') {
        if ((frac1.numerator < 0 && frac2.numerator > 0 && frac1.numerator < std::numeric_limits<int>::min() + frac2.numerator) ||
            (frac1.numerator > 0 && frac2.numerator < 0 && frac1.numerator > std::numeric_limits<int>::max() + frac2.numerator)) {
            throw std::overflow_error("Integer overflow in subtraction.");
        }
    }
    else if (operation == '*') {
        long long product = static_cast<long long>(frac1.numerator) * static_cast<long long>(frac2.numerator);
        if (product > std::numeric_limits<int>::max() || product < std::numeric_limits<int>::min()) {
            throw std::overflow_error("Integer overflow in multiplication.");
        }
        product = static_cast<long long>(frac1.denominator) * static_cast<long long>(frac2.denominator);
        if (product > std::numeric_limits<int>::max() || product < std::numeric_limits<int>::min()) {
            throw std::overflow_error("Integer overflow in multiplication.");
        }
    }
    else if (operation == '/') {
        if (frac2.numerator == 0) {
            throw std::runtime_error("Division by zero.");
        }
        else if (frac1.numerator == std::numeric_limits<int>::min() && frac2.numerator == -1) {
            throw std::overflow_error("Integer overflow in division.");
        }
    }
}
    
    void Fraction::reduced_form() {
        int gcd = std::gcd(this->numerator,this->denominator);
        this->numerator/= gcd;
        this->denominator/= gcd;
        if(this->denominator<0){
            this->numerator *= -1;
            this->denominator *= -1;
        }
    }

    Fraction operator+ (const Fraction& frac1, const Fraction& frac2) {
    int lcm = std::lcm(frac1.denominator, frac2.denominator);
    int sum_num = frac1.numerator * (lcm / frac1.denominator) + frac2.numerator * (lcm / frac2.denominator);
    check_overflow(frac1, frac2, '+');
    return Fraction(sum_num, lcm);
}
    Fraction operator- (const Fraction& frac1, const Fraction& frac2){
        check_overflow(frac1, frac2, '-');
        return frac1 + Fraction(-1 * frac2.numerator,frac2.denominator);
    }
    Fraction operator* (const Fraction& frac1, const Fraction& frac2){
        check_overflow(frac1,frac2,'*');
        return Fraction(frac1.numerator*frac2.numerator,
        frac1.denominator*frac2.denominator);
    }
    Fraction operator/ (const Fraction& frac1, const Fraction& frac2){
        if(frac2.numerator == 0){
            throw std::runtime_error("");
        }
        return frac1 * Fraction(frac2.denominator,frac2.numerator);
    }
    
    //bool fraction
    bool operator> (const Fraction& frac1, const Fraction& frac2){
        int extended_a = 1000 * ((float)frac1.numerator/frac1.denominator);
        int extended_b = 1000 * ((float)frac2.numerator/frac2.denominator);
        return extended_a > extended_b;
    }
    bool operator< (const Fraction& fraction1, const Fraction& fraction2){
        return fraction2 > fraction1;
    }
    bool operator== (const Fraction& fraction1, const Fraction& fraction2){
        return !((fraction1>fraction2)||(fraction1<fraction2));
    }
    bool operator!= (const Fraction& fraction1, const Fraction& fraction2){
        return ((fraction1>fraction2)||(fraction1<fraction2));
    }
    bool operator>= (const Fraction& fraction1, const Fraction& fraction2){
        return (fraction1>fraction2||fraction1==fraction2);
    }
    bool operator<= (const Fraction& fraction1, const Fraction& fraction2){
        return (fraction1<fraction2||fraction1==fraction2);
    }


    //input output
    ostream& operator<<(ostream& osStream, const Fraction& frac){
        osStream << frac.numerator <<'/' << frac.denominator;
        return osStream;
    };
    

    istream& operator>> (istream& inStream, Fraction &frac){
        int numerator, denominator;
        if (inStream >> numerator >> denominator) {
            if (denominator == 0) {
                throw std::runtime_error("Cannot divide by zero.");
            }
            frac = Fraction(numerator, denominator);
        }
        else {
            throw std::runtime_error("Failed to read Fraction from input.");
        }
        return inStream;
    };
    // prefix
    Fraction Fraction::operator++ (){
        *this= *this + Fraction(1);
        return *this;
    };
    Fraction Fraction::operator--(){
        *this= *this - Fraction(1);
        return *this;
    };
    //postfix
    Fraction Fraction::operator++ (int){
        Fraction temp = *this;
        ++*this;
        return temp;
    };
    Fraction Fraction::operator-- (int){
        Fraction temp = *this;
        --*this;
        return temp;
    };


    // for test purpose
    int Fraction::getNumerator(){
        return this->numerator;
    }
    
    int Fraction::getDenominator(){
        return this->denominator;
    }

    void Fraction::setNumerator(int _num){
        this->numerator = _num;
    }
    void Fraction::setDenominator(int _den){
        this->denominator = _den;
    }
    
    
}