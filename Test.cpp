
#include "doctest.h"
#include "sources/Fraction.hpp"

using namespace ariel;


TEST_CASE("Fraction class testcase"){
        
    // this test case include special inclusive cases of + operator in Fractions
    SUBCASE("add operator testcase")
    {
        SUBCASE("fractions sum of similar denomerator "){
            Fraction a(1,13);
            Fraction b(7,13);
            Fraction sum(8,13);
            CHECK(a+b == sum);
        }

        SUBCASE("fractions sum denomerator fractions"){
            Fraction a(1,2);
            Fraction b(1,3);
            Fraction sum(5,6);
            CHECK(a+b == sum);
        }
        
        SUBCASE("sum Fraction with double"){
            Fraction a(1,2);
            double half = 0.5;
            Fraction sum(1,1);
            CHECK(a+half == sum);
        }
        SUBCASE("sum double with Fraction"){
            Fraction a(1,2);
            double half = 0.5;
            Fraction sum(1,1);
            CHECK(half + a == sum);
        }
        SUBCASE("sum Fraction with negative double"){
            Fraction a(1,3);
            double neg_half = -0.5;
            Fraction sum(-1,6);
            CHECK(a+neg_half == sum);
        }
        SUBCASE("sum Fraction with negative Fraction"){
            Fraction a(1,3);
            Fraction neg_half(-1,2);
            Fraction sum(-1,6);
            CHECK(a+neg_half == sum);
        }
    }


    // this test case include special inclusive cases of - operator in Fractions
    SUBCASE("sub operator testcase")
    {
        SUBCASE("fractions diff of similar denomerator "){
            Fraction a(1,13);
            Fraction b(7,13);
            Fraction diff(6,13);
            CHECK(b-a == diff);
        }

        SUBCASE("fractions diff denomerator fractions"){
            Fraction a(1,2);
            Fraction b(1,3);
            Fraction diff(1,6);
            CHECK(a-b == diff);
        }
        
        SUBCASE("diff Fraction with double"){
            Fraction a(1,2);
            double half = 0.5;
            Fraction diff(0,1);
            CHECK(a-half == diff);
        }
        SUBCASE("diff double with Fraction"){
            Fraction a(1,2);
            double half = 0.5;
            Fraction sum(0,1);
            CHECK(half - a == sum);
        }
        SUBCASE("diff Fraction with negative double"){
            Fraction a(1,3);
            double neg_half = -0.5;
            Fraction diff(5,6);
            CHECK(a-neg_half == diff);
        }
        SUBCASE("diff Fraction with negative double"){
            Fraction a(1,3);
            Fraction neg_half(-1,2);
            Fraction diff(5,6);
            CHECK(a-neg_half == diff);
        }
    }

    // this test case include special inclusive cases of * operator in Fractions
    SUBCASE("mult operator testcase")
    {
        SUBCASE("fractions mult of similar denomerator "){
            Fraction a(1,2);
            Fraction b(2,2);
            Fraction mult(1,2);
            CHECK(b*a == mult);
        }

        SUBCASE("fractions diff denomerator fractions"){
            Fraction a(1,2);
            Fraction b(3,4);
            Fraction mult(3,8);
            CHECK(a*b == mult);
        }
        
        SUBCASE("mult Fraction with double"){
            Fraction a(1,2);
            double half = 0.5;
            Fraction mult(1,4);
            CHECK(a*half == mult);
        }
        SUBCASE("mult double with Fraction"){
            Fraction a(1,2);
            double half = 2.0;
            Fraction mult(1,1);
            CHECK(half * a == mult);
        }
        SUBCASE("mult Fraction with negative double"){
            Fraction a(1,3);
            double neg_half = -0.5;
            Fraction mult(-1,6);
            CHECK(a*neg_half == mult);
        }
        SUBCASE("mult Fraction with negative double"){
            Fraction a(1,3);
            Fraction neg_half(-1,2);
            Fraction mult(-1,6);
            CHECK(a*neg_half == mult);
        }
    }


    SUBCASE("div operator testcase")
    {
        SUBCASE("fractions div of fraction zero"){
            Fraction a(1,2);
            Fraction b(0,1);
            CHECK_THROWS(a/b);
        }
        SUBCASE("fractions div of zero"){
            Fraction a(1,2);
            CHECK_THROWS(a/0);
        }
        SUBCASE("fractions div of similar denomerator "){
            Fraction a(1,2);
            Fraction b(2,2);
            Fraction div(1,2);
            CHECK(a/b == div);
        }

        SUBCASE("fractions div denomerator fractions"){
            Fraction a(1,2);
            Fraction b(3,4);
            Fraction mult(3,2);
            CHECK(b/a == mult);
        }
        
        SUBCASE("div Fraction with double"){
            Fraction a(1,2);
            double half = 0.5;
            Fraction div(1,1);
            CHECK(a/half == div);
        }
        SUBCASE("div double with Fraction"){
            Fraction a(1,2);
            double half = 2.0;
            Fraction div(1,4);
            CHECK(half / a == div);
        }
        SUBCASE("div Fraction with negative double"){
            Fraction a(1,3);
            double neg_half = -0.5;
            Fraction div(-2,3);
            CHECK(a/neg_half == div);
        }
        SUBCASE("div Fraction with negative double"){
            Fraction a(1,3);
            Fraction neg_half(-1,2);
            Fraction div(-2,3);
            CHECK(a/neg_half == div);
        }
    }
    SUBCASE("boolean operators testcase"){
        SUBCASE("> and <"){
            Fraction a(1,3);
            float b = 0.111;
            Fraction c(1,10);
            CHECK(a>b);
            CHECK(!(b<a));
            CHECK(a>c);
            CHECK(c<b);
        }

        SUBCASE(">= and <= double with Fraction in case of equel"){
            Fraction a(1,10);
            float b = 0.1;
            Fraction c(1,10);
            CHECK(b>=a);
            CHECK(a<=b);
            CHECK(c>=a);
            CHECK(a<=c);
        }
        SUBCASE(">= and <= double with Fraction in case of not equel"){
            Fraction a(1,3);
            float b = 0.111;
            Fraction c(1,10);
            CHECK(a>b);
            CHECK(!(b<a));
            CHECK(a>c);
            CHECK(c<b);
        }
        SUBCASE("== double with Fraction in case of not equel"){
            Fraction a(1,2);
            float b = 0.5;
            Fraction c(1,2);
            CHECK(a==b);
            CHECK(a==c);
            CHECK(b==c);
        }
        SUBCASE("!= double with Fraction in case of not equel"){
            Fraction a(1,2);
            float b = 0.4;
            Fraction c(1,3);
            CHECK(a!=b);
            CHECK(a!=c);
            CHECK(b!=c);
        }
    }
}
