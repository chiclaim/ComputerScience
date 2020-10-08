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

//菜单
void menu(int type=1){
    cout << "----------------MENU----------------" << endl;
    cout << endl;
    cout << " ---1.加(+)---" << endl;
    cout << endl;
    cout << " ---2.减(-)---" << endl;
    cout << endl;
    cout << " ---3.乘(*)---" << endl;
    cout << endl;
    cout << " ---4.除(/)---" << endl;
    cout << endl;
    if(type == 1){
        cout << " ---5.指数(^)---" << endl;
        cout << endl;
        cout << " ---6.平方根(#)---" << endl;
        cout << endl;
    }
    cout << " ---0.返回上一级---" << endl;
    cout << endl;
    cout << "------------------------------------" << endl;
}

void calculate(){
    
    int flag = 1;
firstLoop:while(1){
        cout << "----------------MENU----------------" << endl;
        cout << endl;
        cout << " ---1.实数---" << endl;
        cout << endl;
        cout << " ---2.虚数---" << endl;
        cout << endl;
        cout << " ---0.退出---" << endl;
        cout << endl;
        cout << "------------------------------------" << endl;
        cout << "请选择实数/虚数:" << endl;
        if(flag == 0){
            exit(0);
            return;
        }
        cin >> flag;
        menu(flag);
        int operate;
        
    secodLoop:while(1){
            if(flag == 1){
                cout << "请选择实数运算符：" << endl;
                cin >> operate;
                numberCalculator cal;
                double x;
                double y;
                
                switch (operate) {
                    case 0:
                        goto firstLoop;
                        break;
                    case 1:
                        cout << "请输入第一个数:" << endl;
                        cin >> x;
                        cout << "请输入第二个数:" << endl;
                        cin >> y;
                        cout << "计算结果：" << cal.add(x, y) << endl << endl;
                        break;
                    case 2:
                        cout << "请输入第一个数:" << endl;
                        cin >> x;
                        cout << "请输入第二个数:" << endl;
                        cin >> y;
                        cout << cal.subtract(x, y) << endl;
                        break;
                    case 3:
                        cout << "请输入第一个数:" << endl;
                        cin >> x;
                        cout << "请输入第二个数:" << endl;
                        cin >> y;
                        cout << "计算结果：" << cal.multiply(x, y) << endl << endl;
                        break;
                    case 4:
                        cout << "请输入第一个数:" << endl;
                        cin >> x;
                        cout << "请输入第二个数:" << endl;
                        cin >> y;
                        cout << "计算结果：" << cal.divide(x, y) << endl << endl;
                        break;
                    case 5:
                        cout << "请输入第一个数:" << endl;
                        cin >> x;
                        cout << "请输入第二个数:" << endl;
                        cin >> y;
                        cout << "计算结果："  << cal.mypow(x, y) << endl << endl;
                        break;
                    case 6:
                        cout << "请输入第一个数:" << endl;
                        cin >> x;
                        cout << "计算结果：" << cal.mysqrt(x) << endl << endl;
                        break;
                    default:
                        cout << "不支持的运算符" << endl;
                        menu(operate);
                        goto secodLoop;
                        break;
                }
            } else if(flag == 2){
                cout << "请选择虚数运算符：" << endl;
                cin >> operate;
                //complexCalculator cal;
                calculator<complex> cal;
                complex c1, c2;
                switch (operate) {
                    case 0:
                        goto firstLoop;
                        break;
                    case 1:
                        cout << "请输入第第一个虚数:" << endl;
                        cin >> c1;
                        cout << "请输入第第二个虚数:" << endl;
                        cin >> c2;
                        cout << "计算结果：" << cal.add(c1,c2) << endl << endl;
                        break;
                    case 2:
                        cout << "请输入第第一个虚数:" << endl;
                        cin >> c1;
                        cout << "请输入第第二个虚数:" << endl;
                        cin >> c2;
                        cout << "计算结果：" << cal.subtract(c1,c2) << endl << endl;
                        break;
                    case 3:
                        cout << "请输入第第一个虚数:" << endl;
                        cin >> c1;
                        cout << "请输入第第二个虚数:" << endl;
                        cin >> c2;
                        cout << "计算结果：" << cal.multiply(c1,c2) << endl << endl;
                        break;
                    case 4:
                        cout << "请输入第第一个虚数:" << endl;
                        cin >> c1;
                        cout << "请输入第第二个虚数:" << endl;
                        cin >> c2;
                        cout << "计算结果：" << cal.divide(c1,c2) << endl << endl;
                        break;
                    default:
                        cout << "不支持的运算符" << endl;
                        menu(operate);
                        goto secodLoop;
                        break;
                }
            } else{
                cout << "只支持实数和虚数运算" << endl;
                break;
            }
        }
    }
}

void hardCodeTest(){
    // 虚数测试
    complexCalculator cal;
    //calculator<complex> cal;
    complex c1(2,4);
    complex c2(2,8);
    cout<< cal.add(c1, c2)<<endl;
    cout<< cal.subtract(c1, c2)<<endl;
    cout<< cal.multiply(c1, c2)<<endl;
    cout<< cal.divide(c1, c2)<<endl;
    
    
    
    
    // 测试重载 >> 操作符
    //complex c3;
    //cin >> c3;
    //cout << c3 << endl;
    
    
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
}


int main(int argc, const char * argv[]) {
    calculate();
    return 0;
}
