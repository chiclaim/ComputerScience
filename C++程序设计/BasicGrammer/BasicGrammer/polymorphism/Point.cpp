//
//  Point.cpp
//  BasicGrammer
//
//  Created by 余志强 on 2020/10/11.
//  Copyright © 2020 yzq. All rights reserved.
//

#include "Point.hpp"
#include <iostream>

Point::Point(double i,double j){
    x = i;
    y = j;
}

double Point::area(){
    return 0;
}

Point::~Point(){
    std::cout << "Destructor in Point" <<std::endl;
}

// 初始化静态变量
int Point::bb = 10;
