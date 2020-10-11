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

using namespace std;
int main(int argc, const char * argv[]) {
    
    return 0;
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
