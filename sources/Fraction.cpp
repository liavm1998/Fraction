#include "Fraction.hpp"
#include <math.h>
#include <numeric>
#include <functional>
using namespace std;

namespace ariel{
    Fraction::Fraction(int _numerator,int _denominator){
        this->numerator = _numerator;
        this->denominator = _denominator;
    };
    Fraction::Fraction(float f){
        Fraction help(round(f*=1000),1000);
        *this = help.reduced_form();
    };
    //help functions
    Fraction Fraction::reduced_form(){
        if(this->numerator == 0){
            return Fraction(0,1);
        }
        int div_by = gcd(this->numerator,this->denominator);
        return Fraction(this->numerator/div_by,this->denominator/div_by);
    }
    Fraction Fraction::extend_to_base(int base){
        double mult_by = base / this->denominator;
        return Fraction(this->numerator*mult_by,base);
    }

    bool boolean_calc(Fraction a, Fraction b, const LogicalOperator& oper){
        int base = lcm(a.denominator,b.denominator);
        int extended_a = a.extend_to_base(base).numerator;
        int extended_b = b.extend_to_base(base).numerator;
        return oper(extended_a,extended_b);
    }
    // binary with fraction
    Fraction Fraction::operator+(Fraction ot){
        int base = lcm(this->denominator,ot.denominator);
        Fraction extended_self = this->extend_to_base(base);
        Fraction extended_ot = ot.extend_to_base(base);
        return Fraction(extended_self.numerator+extended_ot.numerator,base).reduced_form();
    };

    Fraction Fraction::operator-(Fraction ot){
        return *this + Fraction(-1 * ot.numerator,ot.denominator);
    };
    Fraction Fraction::operator/(Fraction ot){
        if(ot.numerator == 0){
            throw "attempt to div by zero";
        }
        return *this * Fraction(ot.denominator,ot.numerator);
    };
    Fraction Fraction::operator*(Fraction ot){
        return Fraction(this->numerator*ot.numerator,this->denominator*ot.denominator).reduced_form();
    };

    //bool fraction
    bool Fraction::operator>(Fraction ot){
        return boolean_calc(*this,ot,Bigger());
    };
    bool Fraction::operator==(Fraction ot){
        return boolean_calc(*this,ot,Equel());
    };
    bool Fraction::operator!=(Fraction ot){
        return !(*this==ot);
    }
    bool Fraction::operator<(Fraction ot){
        return ot > *this;
    }
    bool Fraction::operator>=(Fraction ot){
        return (*this > ot)||(*this == ot);
    };
    bool Fraction::operator<=(Fraction ot){
        return ot >= *this;
    };

    // float opertator Fraction  
    Fraction operator*(float a, Fraction f){return f * a;};
    Fraction operator+(float a, Fraction f){return f + a;};
    Fraction operator-(float a, Fraction f){return f - a;};
    Fraction operator/(float a, Fraction f){return f / a;};
    // bool float
    bool Fraction::operator<(float ot){ return *this<Fraction(ot); };
    bool Fraction::operator>(float ot){ return *this>Fraction(ot); };
    bool Fraction::operator<=(float ot){ return *this<=Fraction(ot); };
    bool Fraction::operator>=(float ot){ return *this>=Fraction(ot); };
    bool Fraction::operator==(float ot){return *this==Fraction(ot); };
    bool Fraction::operator!=(float ot){return *this!=Fraction(ot); };
    
    // float operator fraction

    bool operator>(float a,  Fraction ot){ return ot > a; };
    bool operator<(float a,  Fraction ot){ return ot < a; };
    bool operator>=(float a, Fraction ot){ return ot >= a  ; };
    bool operator==(float a, Fraction ot){ return ot == Fraction(a); };
    bool operator!=(float a, Fraction ot){ return ot != Fraction(a); };
    bool operator<=(float a, Fraction ot){ return ot <= Fraction(a); };

    ostream& operator<<(ostream& os, const Fraction& f){
        os <<'\t' << f.numerator <<'/' << f.denominator<<'\t';
        return os;
    };
    
    istream& operator>> (istream& in, Fraction f){
        cout << "Please enter the numerator part: ";
        in >> f.numerator;
        cout << "Please enter the denominator part: ";
        in >> f.denominator;
        return in;
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
        ++*this;
        return temp;
    };
}