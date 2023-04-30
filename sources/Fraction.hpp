#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <functional>
#include "LogicalOperator.hpp"

using namespace std;

namespace ariel{

    class Fraction{
        private:
            int numerator;
            int denominator;

        public:
            Fraction(int numerator,int denominator);
            Fraction(float f);
            Fraction();
            // // cast to float
            // operator float() const;
            // binary with fraction
            Fraction operator+(Fraction ot);
            Fraction operator-(Fraction ot);
            Fraction operator/(Fraction ot);
            Fraction operator*(Fraction ot);
            // bool float
            bool operator<(float ot);
            bool operator>(float ot);
            bool operator==(float ot);
            bool operator!=(float ot);
            bool operator<=(float ot);
            bool operator>=(float ot);
            //bool fraction
            bool operator>(Fraction ot) const;
            bool operator<(Fraction ot) const;
            bool operator>=(Fraction ot)const;
            bool operator==(Fraction ot)const;
            bool operator!=(Fraction ot)const;
            bool operator<=(Fraction ot)const;
            // other side
            friend Fraction operator+(float a, Fraction f);
            friend Fraction operator-(float a, Fraction f);
            friend Fraction operator*(float a, Fraction f);
            friend Fraction operator/(float a, Fraction f);

            //bool fraction
            friend bool operator>(float a,  Fraction ot);
            friend bool operator<(float a,  Fraction ot);
            friend bool operator>=(float a, Fraction ot);
            friend bool operator==(float a, Fraction ot);
            friend bool operator!=(float a, Fraction ot);
            friend bool operator<=(float a, Fraction ot);
            friend ostream& operator<<(ostream& os, const Fraction& f);
            
            friend istream& operator>> (istream& is, Fraction& f);
            // prefix
            Fraction operator++ ();
            Fraction operator-- ();
            //postfix
            Fraction operator++ (int);
            Fraction operator-- (int);

            //help func
            Fraction reduced_form() const;
            Fraction extend_to_base(int base) const;
            friend bool boolean_calc(Fraction a, Fraction b, const LogicalOperator& oper);

            // for tests purpose
            int getNumerator();
            int getDenominator();
            void setNumerator(int _num);
            void setDenominator(int _den);
            bool overflowCheck(int num1, int num2, string oper);

    };
}