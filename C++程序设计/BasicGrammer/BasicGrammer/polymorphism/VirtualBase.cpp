//
//  VirtualBase.cpp
//  BasicGrammer
//
//  Created by 余志强 on 2020/10/11.
//  Copyright © 2020 yzq. All rights reserved.
//

#include <iostream>
using namespace std;

class VBase {
public:
    int a;
public:
    VBase(int a){
        this -> a = a;
        cout<<"VBase constructor a = " << a <<endl;
    }
    
    ~VBase(){
        //cout<<"VBase deconstructor! "<<endl;
    }
};


//派生类1(声明 VBase 为虚基类)
class DeriveA: virtual public VBase {
public:
    DeriveA(int a):VBase(a){
        cout<<"DeriveA constructor  a = "<< a <<endl;
    }
    
    
    ~DeriveA(){
        //cout<<"DeriveA deconstructor! "<<endl;
        
    }
    
    
    int GetA(){return a;}
};


//派生类2(声明VBase为虚基类)
class DeriveB: virtual public VBase{
public:
    DeriveB(int na):VBase(na){
        cout<<"DeriveB constructor a = " <<a<<endl;
    }
    ~DeriveB(){
        //cout<<"DeriveB deconstructor! "<<endl;
        
    }
    int GetA(){return a;}
};


//多继承
class DeriveAB: public DeriveA, public DeriveB {
public:
    DeriveAB(int na1,int na2,int na3):DeriveA(na1),DeriveB(na2),VBase(na3){
        cout<<"CDeriveAB constructor! "<<endl;
    }
    ~DeriveAB(){
        //cout<<"CDeriveAB deconstructor! "<<endl;
        
    }
};
