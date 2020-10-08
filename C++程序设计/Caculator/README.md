#  C++计算器程序

主要包含 `实数` 的运算以及 `复数` 的四则运算。

## 代码设计

实现简单计算器程序的时候，
- 将4则运算运算封装在 calculator 基类中，因为实数和虚数都有4则运算，将共性放在基类中，将个性放在派生类中。
- 在 calculator 中不能将参与的计算的数据类型硬编码 ，因为参与计算的可能是 double 类型，也可能是 complex，通过 C++ 类模板技术达到尽可能的复用代码，减少重复代码，提高程序的可维护性，将来为新的数据类型提供四则运算更加方便灵活，扩展性更好。

另一方面，我也将参与计算的数据设计为函数的参数，而不是类成员属性，
- 在并发程序中更容易发生线程安全问题，通过将数据作为函数参数（局部变量）则不会出现该问题；
- 在参与计算的数据的个数也是不确定的，有的计算只需要一个数据， 比如开方，所以为类成员属性可能会存在成员冗余；
- 每次计算用户关心的是计算结果，计算也是一次性的，参与计算的数据，无需保存在对象中，应该随计算结束而消亡，当然在我们这个小程序中，内存占用可以忽略不计。


将四则运算抽象到  `calculator.h`  头文件中，里面定义了一个抽象类（接口）：

```
template <typename T>
class calculator{

  public :
    T add(T x,T y){ //加
        return x + y;
    }
    T subtract(T x,T y){ //减
        return x - y;
    }
    T multiply(T x,T y){ //乘
        return x * y;
    }
    T divide(T x,T y){ //除
        return x / y;
    }
};
```

不用将被操作的数设计为对象的成员，可以将其作为函数的参数即可，因为对象不需要持有该数据，用户关心的是计算的结果。

如果作为成员变量，还有可能被并发修改的问题。有的时候还有可能只需要一个操作数，例如做幂、开平方等操作。所以不太适合做为成员变量。

## 实数运算

实数除了可以进行  `+、 -、 *、 /` 运算，还可以有其他运算，如幂、平方根等操作，我们将个性的功能放在子类中，所以我们可以y定义一个用于实数运算的头文件 `numberCalculator.h` :

```

class numberCalculator : public calculator<double> {

public :
    double mypow(double x,double y);
    double mysqrt(double x);
};

```

由于 C++ 已经实现了实数的加减乘除运算，所以我们可以很简单对  `numberCalculator.h`  进行实现，然后使用 `math.h` 函数库对数据进行其他运算：

```
#include <math.h>
#include "headers/numberCalculator.h"

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
    // (a+bi) * (c+di)  = (ac - bd)+(bc+ad)i
    return complex(real*other.real - image * other.image, image * other.real+real * other.image);
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
    calculator<complex> cal;
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

