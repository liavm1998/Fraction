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
            // // cast to float
            // operator float() const;
            // binary with fraction
            Fraction operator+(Fraction other);
            Fraction operator-(Fraction other);
            Fraction operator/(Fraction other);
            Fraction operator*(Fraction other);
            // bool float
            bool operator<(float other);
            bool operator>(float other);
            bool operator==(float other);
            bool operator!=(float other);
            bool operator<=(float other);
            bool operator>=(float other);
            //bool fraction
            bool operator>(Fraction other) const;
            bool operator<(Fraction other) const;
            bool operator>=(Fraction other)const;
            bool operator==(Fraction other)const;
            bool operator!=(Fraction other)const;
            bool operator<=(Fraction other)const;
            // otherher side
            friend Fraction operator+(float num_a, Fraction frac);
            friend Fraction operator-(float num_a, Fraction frac);
            friend Fraction operator*(float num_a, Fraction frac);
            friend Fraction operator/(float num_a, Fraction frac);

            //bool fraction
            friend bool operator>(float num_a,  Fraction other);
            friend bool operator<(float num_a,  Fraction other);
            friend bool operator>=(float num_a, Fraction other);
            friend bool operator==(float num_a, Fraction other);
            friend bool operator!=(float num_a, Fraction other);
            friend bool operator<=(float num_a, Fraction other);
            friend ostream& operator<<(ostream& osStream, const Fraction& frac);
            
            friend istream& operator>> (istream& isStream, Fraction& frac);
            // prefix
            Fraction operator++ ();
            Fraction operator-- ();
            //postfix
            Fraction operator++ (int);
            Fraction operator-- (int);

            //help func
            Fraction reduced_form() const;
            Fraction extend_to_base(int base) const;

            // for tests purpose
            int getNumerator();
            int getDenominator();
            void setNumerator(int _num);
            void setDenominator(int _den);
            bool overflowCheck(int num1, int num2, string oper);

    };
}