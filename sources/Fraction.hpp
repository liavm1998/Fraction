#ifndef FRACTION
#define FRACTION
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <functional>


using namespace std;

namespace ariel{

    class Fraction{
        private:
            int numerator;
            int denominator;

        public:
            Fraction(int numerator,int denominator);
            Fraction(float float_fraction);
            Fraction();
            friend void check_overflow(const Fraction& frac1, const Fraction& frac2, char operation);
            /// arithmetic
            friend Fraction operator+ (const Fraction& fraction1, const Fraction& fraction2);
            friend Fraction operator- (const Fraction& fraction1, const Fraction& fraction2);
            friend Fraction operator* (const Fraction& fraction1, const Fraction& fraction2);
            friend Fraction operator/ (const Fraction& fraction1, const Fraction& fraction2);
            // boolean
            friend bool operator> (const Fraction& fraction1, const Fraction& fraction2);
            friend bool operator< (const Fraction& fraction1, const Fraction& fraction2);
            friend bool operator== (const Fraction& fraction1, const Fraction& fraction2);
            friend bool operator!= (const Fraction& fraction1, const Fraction& fraction2);
            friend bool operator>= (const Fraction& fraction1, const Fraction& fraction2);
            friend bool operator<= (const Fraction& fraction1, const Fraction& fraction2);
            
            friend ostream& operator<<(ostream& osStream, const Fraction& frac);
            
            friend istream& operator>> (istream& isStream, Fraction& frac);
            // prefix
            Fraction operator++ ();
            Fraction operator-- ();
            //postfix
            Fraction operator++ (int);
            Fraction operator-- (int);

            //help func
            void reduced_form();
            Fraction extend_to_base(int base) const;

            // for tests purpose
            int getNumerator();
            int getDenominator();
            void setNumerator(int _num);
            void setDenominator(int _den);

    };
}

#endif