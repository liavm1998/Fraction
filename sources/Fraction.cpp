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

    // binary with fraction
    Fraction Fraction::operator+(Fraction other){

        int base = lcm(this->denominator,other.denominator);

        Fraction extended_self = this->extend_to_base(base);
        Fraction extended_other = other.extend_to_base(base);
        if (!overflowCheck(extended_self.numerator,extended_other.numerator,"ADD") 
            ||!overflowCheck(extended_self.denominator,extended_other.denominator,"ADD")){
                throw overflow_error("");
            }
        return Fraction(extended_self.numerator+extended_other.numerator,base).reduced_form();
    };

    Fraction Fraction::operator-(Fraction other){
        cout << "this : " << *this <<endl;
        cout << "other : " << other <<endl;
        cout << "other.numerator * -1 : " << other.numerator *-1 <<endl;
        Fraction reduced_other = other.reduced_form();
        if(this->numerator > 0 &&
         reduced_other.numerator != 0 &&
         reduced_other.numerator *-1 == reduced_other.numerator){
            throw overflow_error("");
        }
        return *this + Fraction(-1 * other.numerator,other.denominator);
    };
    Fraction Fraction::operator/(Fraction other){
        if(other.numerator == 0){
            throw std::runtime_error("");
        }
        return *this * Fraction(other.denominator,other.numerator);
    };
    Fraction Fraction::operator*(Fraction other){
        // Fraction sw1= Fraction(other.numerator,this->denominator).reduced_form();
        // Fraction sw2= Fraction(this->numerator,other.denominator).reduced_form();
        // return Fraction(sw1.numerator*sw2.numerator, sw1.denominator*sw2.denominator).reduced_form();
        Fraction reduced_self= this->reduced_form();
        Fraction reduced_other= other.reduced_form();
        if (!overflowCheck(reduced_self.numerator,reduced_other.numerator,"MUL") ||
            !overflowCheck(reduced_self.denominator,reduced_other.denominator,"MUL")){
            throw overflow_error("");
        }
        return Fraction(reduced_self.numerator*reduced_other.numerator,
        reduced_self.denominator*reduced_other.denominator).reduced_form();
    };

    //bool fraction
    bool Fraction::operator>(Fraction other) const{
        int extended_a = 1000 * ((float)this->numerator/this->denominator);
        int extended_b = 1000 * ((float)other.numerator/other.denominator);
        return extended_a > extended_b;
    };
    bool Fraction::operator==(Fraction other) const{
        int extended_a = 1000 * ((float)this->numerator/this->denominator);
        int extended_b = 1000 * ((float)other.numerator/other.denominator);
        return extended_a == extended_b;
    };
    bool Fraction::operator!=(Fraction other) const{
        return !(*this==other);
    }
    bool Fraction::operator<(Fraction other) const{
        return other > *this;
    }
    bool Fraction::operator>=(Fraction other) const{
        return (*this > other)||(*this == other);
    };
    bool Fraction::operator<=(Fraction other) const{
        return other >= *this;
    };

    // float opertator Fraction  
    Fraction operator*(float num_a, Fraction f){return f * num_a;};
    Fraction operator+(float num_a, Fraction f){return f + num_a;};
    Fraction operator-(float num_a, Fraction f){
        cout << f <<endl;
        cout << "heyyyyyy"<<endl;
        Fraction minf = f * -1.0;
        cout << "heyyyyyy"<<endl;
        return  f*-1 + num_a;
    };
    Fraction operator/(float num_a, Fraction f){return Fraction(f.denominator,f.numerator) * num_a;};
    // bool float
    bool Fraction::operator<(float other){ return *this<Fraction(other); };
    bool Fraction::operator>(float other){ return *this>Fraction(other); };
    bool Fraction::operator<=(float other){ return *this<=Fraction(other); };
    bool Fraction::operator>=(float other){ return *this>=Fraction(other); };
    bool Fraction::operator==(float other){return *this==Fraction(other); };
    bool Fraction::operator!=(float other){return *this!=Fraction(other); };
    
    // float operator fraction

    bool operator>(float num_a,  Fraction other){ return Fraction(num_a) > other; };
    bool operator<(float num_a,  Fraction other){ return Fraction(num_a) < other; };
    bool operator>=(float num_a, Fraction other){ return Fraction(num_a) >= other  ; };
    bool operator==(float num_a, Fraction other){ return other == Fraction(num_a); };
    bool operator!=(float num_a, Fraction other){ return other != Fraction(num_a); };
    bool operator<=(float num_a, Fraction other){ return Fraction(num_a) <= other; };

    ostream& operator<<(ostream& osStream, const Fraction& frac){
        Fraction reduced_f = frac.reduced_form();
        osStream << reduced_f.numerator <<'/' << reduced_f.denominator;
        return osStream;
    };
    

    istream& operator>> (istream& inStream, Fraction &frac){
        int _num, _den;
        if(inStream.peek() == EOF)
        {
            throw std::runtime_error("nother a number error");
        }
        inStream >> _num;
        if(inStream.peek() == '.'){
            throw std::runtime_error("floating point error");
        }
        if(inStream.peek() == EOF)
        {
            throw std::runtime_error("only one number error");
        }
        inStream >> _den;
        if(_den == 0){
            throw runtime_error("div by zero");
        }
        frac = Fraction(_num,_den);
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