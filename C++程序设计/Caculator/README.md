#  C++计算器程序

主要包含 `实数` 的运算以及 `复数` 的四则运算。

## 代码设计

在进行代码实现之前，对功能需求做一个简单的分析：

- 不管是实数的运算还是复数的四则运算，都有  `+、 -、 *、 /` ，我们可以将共性的东西进行抽象
- 我们可以使用 C++ 中的模板类（泛型编程）实现上面的抽象，做到数据的无关性，后面可以方便的扩展更多的数据可以进行 `+、 -、 *、 /` 
- 实数的四则运算 C++ 编译器已经帮我们实现了，需要对复数进行操作符重载，才能使用上面的抽象


将四则运算抽象到  `calculator.h`  头文件中，里面定义了一个抽象类（接口）：

```
template <typename T>
class calculator {

public :
    virtual T add(T x,T y) = 0; //加
    virtual T subtract(T x,T y) = 0; //减
    virtual T multiply(T x,T y)= 0; //乘
    virtual T divide(T x,T y)= 0; //除
};
```

不用将被操作的数设计为对象的成员，可以将其作为函数的参数即可，因为对象不需要持有该数据，用户关心的是计算的结果。

如果作为成员变量，还有可能被并发修改的问题。有的时候还有可能只需要一个操作数，例如做幂、开平方等操作。所以不太适合做为成员变量。

## 实数运算

实数除了可以进行  `+、 -、 *、 /` 运算，还可以有其他运算，如幂、平方根等操作，我们将个性的功能放在子类中，所以我们可以y定义一个用于实数运算的头文件 `numberCalculator.h` :

```

class numberCalculator : public calculator<double> {

public :
    double add(double x,double y);
    double subtract(double x,double y);
    double multiply(double x,double y);
    double divide(double x,double y);
    double mypow(double x,double y);
    double mysqrt(double x);
};

```

由于 C++ 已经实现了实数的加减乘除运算，所以我们可以很简单对  `numberCalculator.h`  进行实现，然后使用 `math.h` 函数库对数据进行其他运算：

```
#include <math.h>
#include <iostream>
#include "headers/numberCalculator.h"

double numberCalculator::add(double x,double y){
    return x+y;
}

double numberCalculator::subtract(double x, double y){
    return x-y;
}

double numberCalculator::multiply(double x, double y){
    return x*y;
}

double numberCalculator::divide(double x, double y){
    if(y == 0) {
        throw std::runtime_error("division is zero");
    }
    return x/y;
}

double numberCalculator::mypow(double x, double y){
    return pow(x, y);
}

double numberCalculator::mysqrt(double x){
    return sqrt(x);
}
```

## 复数运算

因为在 C++ 编译中不能直接对复数进行运算，所以需要我们对复数进行操作符重载。

**complex.h**
```
class complex{
    private:
        double real = 0; // 实部
        double image = 0;// 虚部

    public:
        complex(double r,double i = 0);

        double getReal();
        double getImage();

        complex operator+(complex& other);
        complex operator-(complex& other);
        complex operator*(complex& other);
        complex operator/(complex& other);
        friend ostream& operator<<(ostream &os, const complex& c);
        friend istream& operator>>(istream &os, complex& c);
};
```

根据序数的运算规则，对  `complex.h`  进行实现:

```
complex::complex(double r,double i){
    real = r;
    image = i;
}

double complex::getReal(){
    return real;
}

double complex::getImage(){
    return image;
}

complex complex::operator+(complex& other){
    // (a+bi) + (c+di)  = (a+c) + (b+d)i
    return complex(real + other.real,image + other.image);
}
complex complex::operator-(complex& other){
    // (a+bi) - (c+di)  = (a+c) - (b+d)i
    return complex(real - other.real, image - other.image);
}
complex complex::operator*(complex& other){
    // (a+bi) * (c+di)  = (ac - bd)+(bc-ad)i
    return complex(real*other.real - image * other.image, image * other.real-real * other.image);
}
complex complex::operator/(complex& other){
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
```

测试程序：

```
int main(int argc, const char * argv[]) {
    complexCalculator cal;
    complex c1(2,4);
    complex c2(2,8);
    cout<< cal.add(c1, c2)<<endl;
    cout<< cal.subtract(c1, c2)<<endl;
    cout<< cal.multiply(c1, c2)<<endl;
    cout<< cal.divide(c1, c2)<<endl;


    // 测试重载 >> 操作符
    complex c3;
    cin >> c3;
    cout << c3 << endl;


    numberCalculator cal2;
    double x = 10;
    double y = 2;
    cout<< cal2.add(x, y)<<endl;
    cout<< cal2.subtract(x, y)<<endl;
    cout<< cal2.multiply(x, y)<<endl;
    cout<< cal2.divide(x, y)<<endl;
    cout<< cal2.mypow(x, y)<<endl;
    cout<< cal2.mysqrt(x)<<endl;

    return 0;
}
```

