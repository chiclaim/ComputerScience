//
//  复数操作符重载
//
//  Created by 余志强 on 2020/9/26.
//  Copyright © 2020 yzq. All rights reserved.
//

#include <math.h>
#include "headers/complex.h"

complex::complex(double r,double i){
    real = r;
    image = i;
}

double complex::getReal() const{
    return real;
}

double complex::getImage() const{
    return image;
}

complex complex::operator+(const complex& other){
    // (a+bi) + (c+di)  = (a+c) + (b+d)i
    return complex(real + other.real,image + other.image);
}
complex complex::operator-(const complex& other){
    // (a+bi) - (c+di)  = (a+c) - (b+d)i
    return complex(real - other.real, image - other.image);
}
complex complex::operator*(const complex& other){
    // (a+bi) * (c+di)  = (ac - bd)+(bc-ad)i
    return complex(real*other.real - image * other.image, image * other.real-real * other.image);
}
complex complex::operator/(const complex& other){
    // (a+bi) / (c+di)  = ((ac+bd)/c^2+d^2) + ((bc-ad)/(c^2+d^2))i
    double newReal = (real*other.real + image*other.image)/(pow(other.real, 2) + pow(other.image, 2));
    double newImage = (image*other.real - real*other.image)/(pow(other.real, 2) + pow(other.image, 2));
    return complex(newReal, newImage);
}

ostream& operator<<(ostream &stream, const complex &c){
    stream << c.real << ','<< c.image;
    return stream;
}


istream& operator>>(istream &stream, complex &c){
    stream >> c.real >> c.image;
    return stream;
}
//... 由于篇幅原因，省略其他操作符重载
