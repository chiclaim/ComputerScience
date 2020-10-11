//
//  main.cpp
//  BasicGrammer
//
//  Created by 余志强 on 2020/10/11.
//  Copyright © 2020 yzq. All rights reserved.
//

#include <iostream>
#include "polymorphism/Circle.hpp"
#include "polymorphism/Point.hpp"
#include "const_kw/ConstTest.cpp"

using namespace std;
void testConst();
void testVirtualFunc();
void testDestructor();
void testDestructor2();

int main(int argc, const char * argv[]) {
    testDestructor();
    //testDestructor2();
    return 0;
}

void testConst(){
    int i = 19;
    One o1(i);
    o1.show(); // 调用 void show()
    
    const One o2(10);
    o2.show(); // 调用 void show() const
    
}

void testVirtualFunc(){
    Point a(2,4);
    Circle c(2,4, 3);
    cout<<"point:"<<a.area()<<endl;
    cout<<"circle:"<<c.area()<<endl;
    
    // 如果 area 不是虚函数，那么下面两个输出依然是0
    // 动态联编
    Point *p = &c;
    cout<<"circle:"<<p->area()<<endl;
    Point &p2 = c;
    cout<<"circle:"<<p2.area()<<endl;
    
}

void testDestructor(){
    // 如果 Point 基类中没有使用 virtual 修饰析构函数，下面的代码则不会调用 Circle 的析构函数
    Base*p = new Circle(2,2,2);
    delete p;
    
    // 如果再让 Point 派生自 Base 类（Point 或 Base 里存在虚析构函数），上面的代码也会输出，如下：
    /*
     Destructor in Circle
     Destructor in Point
     Destructor in Base
     */
}

void testDestructor2(){
    // 这种情况不管Point有没有虚析构函数，都会调用 Circle 的析构函数
    Point *p ;
    Circle c(2,2,2);
    p = &c;
}
