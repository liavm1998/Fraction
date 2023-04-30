#include "Fraction.hpp"
#include <math.h>
#include <numeric>
#include <functional>
using namespace std;

namespace ariel{
    Fraction::Fraction(){

    }

    Fraction::Fraction(int _numerator,int _denominator){
        if(_denominator == 0){
            throw invalid_argument("");
        }
        if(_denominator<0){
            _numerator*=-1;
            _denominator*=-1;
        }
        this->numerator = _numerator;
        this->denominator = _denominator;
    };
    Fraction::Fraction(float f){
        *this = Fraction(round(f*=1000),1000);
        *this = this->reduced_form();
    };
    //help functions
    Fraction Fraction::reduced_form() const{
        if(this->numerator == 0){
            return Fraction(0,1);
        }
        int div_by = gcd(this->numerator,this->denominator);
        return Fraction(this->numerator/div_by,this->denominator/div_by);
    }
    Fraction Fraction::extend_to_base(int base) const{
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
        if (!overflowCheck(extended_self.numerator,extended_ot.numerator,"ADD") 
            ||!overflowCheck(extended_self.denominator,extended_ot.denominator,"ADD")){
                throw overflow_error("");
            }
        return Fraction(extended_self.numerator+extended_ot.numerator,base).reduced_form();
    };

    Fraction Fraction::operator-(Fraction ot){
        cout << "this : " << *this <<endl;
        cout << "ot : " << ot <<endl;
        cout << "ot.numerator * -1 : " << ot.numerator *-1 <<endl;
        Fraction reduced_ot = ot.reduced_form();
        if(this->numerator > 0 &&
         reduced_ot.numerator != 0 &&
         reduced_ot.numerator *-1 == reduced_ot.numerator){
            throw overflow_error("");
        }
        return *this + Fraction(-1 * ot.numerator,ot.denominator);
    };
    Fraction Fraction::operator/(Fraction ot){
        if(ot.numerator == 0){
            throw std::runtime_error("");
        }
        return *this * Fraction(ot.denominator,ot.numerator);
    };
    Fraction Fraction::operator*(Fraction ot){
        // Fraction sw1= Fraction(ot.numerator,this->denominator).reduced_form();
        // Fraction sw2= Fraction(this->numerator,ot.denominator).reduced_form();
        // return Fraction(sw1.numerator*sw2.numerator, sw1.denominator*sw2.denominator).reduced_form();
        Fraction reduced_self= this->reduced_form();
        Fraction reduced_ot= ot.reduced_form();
        if (!overflowCheck(reduced_self.numerator,reduced_ot.numerator,"MUL") ||
            !overflowCheck(reduced_self.denominator,reduced_ot.denominator,"MUL")){
            throw overflow_error("");
        }
        return Fraction(reduced_self.numerator*reduced_ot.numerator,
        reduced_self.denominator*reduced_ot.denominator).reduced_form();
    };

    //bool fraction
    bool Fraction::operator>(Fraction ot) const{
        return boolean_calc(*this,ot,Bigger());
    };
    bool Fraction::operator==(Fraction ot) const{
        int extended_a = 1000 * ((float)this->numerator/this->denominator);
        int extended_b = 1000 * ((float)ot.numerator/ot.denominator);
        return extended_a == extended_b;
    };
    bool Fraction::operator!=(Fraction ot) const{
        return !(*this==ot);
    }
    bool Fraction::operator<(Fraction ot) const{
        return ot > *this;
    }
    bool Fraction::operator>=(Fraction ot) const{
        return (*this > ot)||(*this == ot);
    };
    bool Fraction::operator<=(Fraction ot) const{
        return ot >= *this;
    };

    // float opertator Fraction  
    Fraction operator*(float a, Fraction f){return f * a;};
    Fraction operator+(float a, Fraction f){return f + a;};
    Fraction operator-(float a, Fraction f){
        cout << f <<endl;
        cout << "heyyyyyy"<<endl;
        Fraction minf = f * -1.0;
        cout << "heyyyyyy"<<endl;
        return  f*-1 + a;
    };
    Fraction operator/(float a, Fraction f){return Fraction(f.denominator,f.numerator) * a;};
    // bool float
    bool Fraction::operator<(float ot){ return *this<Fraction(ot); };
    bool Fraction::operator>(float ot){ return *this>Fraction(ot); };
    bool Fraction::operator<=(float ot){ return *this<=Fraction(ot); };
    bool Fraction::operator>=(float ot){ return *this>=Fraction(ot); };
    bool Fraction::operator==(float ot){return *this==Fraction(ot); };
    bool Fraction::operator!=(float ot){return *this!=Fraction(ot); };
    
    // float operator fraction

    bool operator>(float a,  Fraction ot){ return Fraction(a) > ot; };
    bool operator<(float a,  Fraction ot){ return Fraction(a) < ot; };
    bool operator>=(float a, Fraction ot){ return Fraction(a) >= ot  ; };
    bool operator==(float a, Fraction ot){ return ot == Fraction(a); };
    bool operator!=(float a, Fraction ot){ return ot != Fraction(a); };
    bool operator<=(float a, Fraction ot){ return Fraction(a) <= ot; };

    ostream& operator<<(ostream& os, const Fraction& f){
        Fraction reduced_f = f.reduced_form();
        os << reduced_f.numerator <<'/' << reduced_f.denominator;
        return os;
    };
    

    istream& operator>> (istream& in, Fraction &f){
        int _num, _den;
        if(in.peek() == EOF)
        {
            throw std::runtime_error("not a number error");
        }
        in >> _num;
        if(in.peek() == '.'){
            throw std::runtime_error("floating point error");
        }
        if(in.peek() == EOF)
        {
            throw std::runtime_error("only one number error");
        }
        in >> _den;
        if(_den == 0){
            throw runtime_error("div by zero");
        }
        f = Fraction(_num,_den);
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
    bool Fraction::overflowCheck(int num1, int num2, string oper){
        int max_int = std::numeric_limits<int>::max();
        int min_int = std::numeric_limits<int>::min();
        if(oper == "MUL"){
            int result = num1 * num2;
            if(result == 0 && (num1 == 0 || num2 == 0))
                return 1;
            return (result / num1 == num2);
        }
        if(oper == "ADD"){

            int result = num1 + num2;
            cout << endl << " /////////////////// " <<endl;
            cout << "result : " << result <<endl;
            cout << "num1 : " << num1 <<endl;
            cout << "num2 : " << num2 <<endl;
            
            if(num1>=0 && num2>0 && result<0){
                return 0;
            }
            if(num1<0 && num2<0 && result>0){
                return 0;
            }
            return 1;
        }
        return 0;

    }
    
}