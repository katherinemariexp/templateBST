// Description: Assignment 14 - BST 
// Author: Katherine-Marie Gonzales
// COMSC200 - 5001
// May 23, 2019
// Status: Not sure if tests are correct, frac and FeetInches Included

//Frac.h

#ifndef FRAC_H
#define FRAC_H
#include <iostream>
#include <sstream>


using namespace std;

class Frac;

ostream &operator << (ostream &strm, const Frac &);
istream &operator >> (istream &strm, Frac &);

class Frac {
private:
    int num; 
    int den; 
    void lowTerms(int &num, int &den); 
    
public:
    Frac()
        { num = 0; den = 1; }
        
    Frac(int n) 
        { num = n; den = 1; }
        
    Frac(int n, int d) 
        { num = n; den = d; }
        
    Frac(string s);    
    
    Frac(const Frac& rhs)
        { num = rhs.num; den = rhs.den; }
    
    Frac operator=(const Frac& rhs)
        { num = rhs.num; den = rhs.den; }
    
    void setNum(int n) { num = n; }
    void setDen(int d) { den = d; }
    
    int getNum() const { return num; }
    int getDen() const { return den; }
    
    Frac operator + (const Frac &rhs);
    Frac operator - (const Frac &rhs);
    Frac operator * (const Frac &rhs);
    Frac operator / (const Frac &rhs);
    
    Frac operator++();
    Frac operator++(int);
    Frac operator--();
    Frac operator--(int);
    
    bool operator == (const Frac &f2);
    bool operator != (const Frac &f2);
    bool operator < (const Frac &f2);
    bool operator > (const Frac &f2);
    bool operator <= (const Frac &f2);
    bool operator >= (const Frac &f2);
    
    operator int() { return (num) / den; }
    operator float() 
    {
        float temp;
        temp = static_cast<float>(num) / static_cast<float>(den);
        return temp;
    }
    friend ostream &operator << (ostream& strm, const Frac& f);
    friend istream &operator >> (istream& strm, Frac& f);
    
};


void Frac::lowTerms(int &num, int &den)
{
    int low;
    int high;
    
    if(num > den)
    {
        low = den;
        high = num;
    }
    else
    {
        high = den;
        low = num;
    }
        
    for(int i = low; i > 0; i--)
    {
        if((low % i == 0) && (high % i ==0))
        {
            num = num / i;
            den = den / i;
        }
    }
} 

Frac::Frac(string s) 
{
    stringstream ss(s);
    ss >> num;
    char peekchar = ss.peek();
    if (ss && peekchar == '/')
    {
        ss.get();
        ss >> den;
    }
}

Frac Frac::operator + (const Frac &rhs)
{
    Frac temp;
    temp.num = (num * rhs.den) + (rhs.num * den);
    temp.den = den * rhs.den;
    temp.lowTerms(temp.num, temp.den);
    return temp;
}

Frac Frac::operator - (const Frac &rhs)
{
    Frac temp;
    temp.num = (num * rhs.den) - (rhs.num * den);
    temp.den = den * rhs.den;
    temp.lowTerms(temp.num, temp.den);
    return temp;
}

Frac Frac::operator * (const Frac &rhs)
{
    Frac temp;
    temp.num = num * rhs.num;
    temp.den = den * rhs.den;
    temp.lowTerms(temp.num, temp.den);
    return temp;
}

Frac Frac::operator / (const Frac &rhs)
{
    Frac temp;
    temp.num = num * rhs.den;
    temp.den = den * rhs.num;
    temp.lowTerms(temp.num, temp.den);
    return temp;
}

Frac Frac::operator++()
{
    num += den;
    lowTerms(num, den);
    return *this;
}

Frac Frac::operator++(int)
{
    Frac temp(num, den);
    num += den;
    lowTerms(temp.num, temp.den);
    return temp;
}


Frac Frac::operator--()
{
    num -=den;
    lowTerms(num, den);
    return *this;
}

Frac Frac::operator--(int)
{
    Frac temp(num, den);
    num -= den;
    lowTerms(temp.num, temp.den);
    return temp;
}


bool Frac::operator == (const Frac &f2)
{
    bool status;
    if(num == f2.num && den == f2.den)
    {
        status = true;
    }
    else
    {
        status = false;
    }
    return status;
}

bool Frac::operator != (const Frac &f2)
{
    bool status;
    if(num != f2.num || den != f2.den)
    {
        status = true;
    }
    else
    {
        status = false;
    }
    return status;
}

bool Frac::operator < (const Frac &f2)
{
    bool status;
    if(num < f2.num && den < f2.den)
    {
        status = true;
    }
    else
    {
        status = false;
    }
    return status;
}

bool Frac::operator > (const Frac &f2)
{
    bool status;
    if(num > f2.num && den > f2.den)
    {
        status = true;
    }
    else
    {
        status = false;
    }
    return status;
}

bool Frac::operator <= (const Frac &f2)
{
    bool status;
    if(num < f2.num && den < f2.den)
    {
        status = true;
    }
    else if (num == f2.num && den == f2.den)
    {
        status = true;
    }
    else
    {
        status = false;
    }
    return status;
}

bool Frac::operator >= (const Frac &f2)
{
    bool status;
    if(num > f2.num && den > f2.den)
    {
        status = true;
    }
    else if (num == f2.num && den == f2.den)
    {
        status = true;
    }
    else 
    {
        status = false;
    }
    return status;
}
    
ostream &operator << (ostream &strm, const Frac &rhs)
{
    strm << rhs.num << "/" << rhs.den;
    return strm;
}

istream &operator >> (istream &strm, Frac &rhs)
{
    char c;
    strm >> rhs.num;
    strm >> c;
    strm >> rhs.den;
    rhs.lowTerms(rhs.num, rhs.den);
    return strm;
}

#endif