//
//  Circle.cpp
//  BasicGrammer
//
//  Created by 余志强 on 2020/10/11.
//  Copyright © 2020 yzq. All rights reserved.
//

#include "Circle.hpp"

Circle::Circle(double x,double y,double r):Point(x,y){
    radius = r;
}


double Circle::area(){
    return 3.14159 * radius * radius;
}
