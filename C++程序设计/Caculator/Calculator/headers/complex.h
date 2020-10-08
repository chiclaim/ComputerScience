//
//  complex.h
//  Calculator
//
//  Created by 余志强 on 2020/9/26.
//  Copyright © 2020 yzq. All rights reserved.
//

#ifndef complex_h
#define complex_h
#include <iostream>
using namespace std;

class complex{
private:
    double real = 0;
    double image = 0;
    
public:
    complex(double r = 0 ,double i = 0);
    
    double getReal() const;
    double getImage() const;
    
    complex operator+(const complex& other);
    complex operator-(const complex& other);
    complex operator*(const complex& other);
    complex operator/(const complex& other);
    friend ostream& operator<<(ostream &os, const complex& c);
    friend istream& operator>>(istream &os, complex& c);
};

#endif /* complex_h */
