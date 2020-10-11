//
//  ConstTest.cpp
//  BasicGrammer
//
//  Created by 余志强 on 2020/10/11.
//  Copyright © 2020 yzq. All rights reserved.
//

#include <iostream>
using namespace std;

class Two{
    public :
    int x = 10;
};

class One{
    
private :
    int x;
    
    // 常量数据成员
    const int a = 22;
    
    // 常量引用
    const int & r;
    
    // 静态常量数据成员
    static const int b = 11;
    
    
public:
    // 初始化列表
    One(int i):x(i),a(i),r(a){
        
    }
    void setA(int _a){
        // 常量数据成员只能在初始化列表中设置值
        //a = _a;
        
        // 静态常量数据成员只能在类外初始化
        //b = 11;
        
        // 只能在初始化列表中设置值
        //r = &_a;
    }
    
    void show() const{
        // 在常量函数中不能修改对象的成员数据
        //x = 111;
        cout << "in const function : x = " << x << endl;
    }
    void show(){
        x = 111;
        cout << "x = " << x << endl;
    }
    
    void show(const double &d){
        // 不能改变常量引用的值
        //d = 10;
        cout<<d<<endl;
    }
    
    void show(const Two &t){
        // 不能改变常量引用对象的值
        //t.x = 10;
        cout<<t.x<<endl;
    }
};



