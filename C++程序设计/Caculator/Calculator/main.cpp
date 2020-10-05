//
//  main.cpp
//  Caculator
//
//  Created by 余志强 on 2020/9/26.
//  Copyright © 2020 yzq. All rights reserved.
//

// 加、减、乘、除

#include <iostream>
#include "headers/complexCalculator.h"
#include "headers/numberCalculator.h"
using namespace std;

int main(int argc, const char * argv[]) {
    
    // 虚数测试
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
    
    
    // 实数测试
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
